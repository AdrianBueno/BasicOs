#include <OperatingSystem.h>
#include <MainMemory.h>
#include <MMU.h>
#include <Processor.h>
#include <Buses.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <Heap.h>
#include <Clock.h>
PCB processTable[PROCESSTABLEMAXSIZE];									//Tabla de procesos.
PARTITIONDATA partitionsTable[PROCESSTABLEMAXSIZE];
int arrivalTimeQueue[USERPROGRAMSMAXNUMBER]; 							//Cola de procesos con llegada diferida.
int readyToRunQueue [NUMBEROFQUEUES][PROCESSTABLEMAXSIZE]; 				//Colas de procesos en estado READY.
int sleepingProcessesQueue[PROCESSTABLEMAXSIZE]; 						//Cola de procesos en estado BLOCKED.
int numberOfProgramsInArrivalTimeQueue; 								//Numero de procesos en la cola de llegada.
int numberOfReadyToRunProcesses[NUMBEROFQUEUES]; 						//Numero de procesos en la cola de READY.
int numberOfSleepingProcesses;		
int numberOfPartitions;									//Numero de procesos en la cola de BLOCKED.
int numberOfNotTerminatedProcesses=0;									//Numero de procesos no terminados aún (Nose cuenta el Idle).
int numberOfYIELDchange=0;
int numberOfYIELDnoChange = 0;
int executingProcessID;													//Proceso actual en ejecución.
int sipID;																//Proceso Daemon del sistema Idle.
int ClockInterruption = 0;												//Contador de interrupciones.
int end = 0;
int maxPartitionSize = 0;
int statePrintMem = 0;													//Particion de tamaño máximo
char * statesNames [5]={"NEW","READY","EXECUTING","BLOCKED","EXIT"}; 	//Estados de un proceso.
void OperatingSystem_Initialize() {
	OperatingSystem_InitializePartitionTable(); 										//Inicializamos la tabla de particiones según el fichero definido en la cabecera
	OperatingSystem_InicilizateProcessTable();											//Inicializamos la tabla de procesos para que estén todos desocupados
	OperatingSystem_CreateDaemons();													//Creamos el proceso Daemon con PID = 0
	Processor_InitializeInterruptVectorTable();
	(OperatingSystem_LongTermScheduler() < 0 && OperatingSystem_GetNewProgram() == -1) ? OperatingSystem_End() : OperatingSystem_Dispatch(OperatingSystem_ShortTermScheduler());	
}
void OperatingSystem_InicilizateProcessTable(){
	int i;
	for (i=0; i<PROCESSTABLEMAXSIZE;i++)
		processTable[i].busy=0;
}
void OperatingSystem_CreateDaemons() {
	USER_PROGRAMS_DATA systemIdleProcess;
	systemIdleProcess.executableName="SystemIdleProcess";
	sipID=OperatingSystem_CreateProcess(systemIdleProcess,DAEMONSQUEUE);				//Añadimos a la cola de demons
	if(sipID < 0){
		printf("Error en la creación del DAEMON del sistema\n");
		OperatingSystem_LongTermSchedulerERROR(sipID);									//Si por alguna razón no se crea el demonio mandamos el código de erro al despachador de errores.
	}
}
int OperatingSystem_LongTermScheduler() {
	int i= 0;
	while (OperatingSystem_GetNewProgram() == 1) {
		int PID=OperatingSystem_CreateProcess(*userProgramsList[Heap_poll(arrivalTimeQueue,QUEUE_ARRIVAL,numberOfProgramsInArrivalTimeQueue--)], USERPROCESSQUEUE);//Añadimos a cola de procesos de usuario
		if(PID >= 0){
		    numberOfNotTerminatedProcesses++;
		    ComputerSystem_DebugMessage(INIT,"CkGsGdGsGsGs","Process [",PID,"] created from program [",userProgramsList[i]->executableName,"]\n");
			i++;
		}else
			OperatingSystem_LongTermSchedulerERROR(PID);
	}
	if(i > 0)
		OperatingSystem_PrintStatus();
	return i-1;
}
void OperatingSystem_LongTermSchedulerERROR(int ERRORCODE){
	char * error;
	switch(ERRORCODE){
		case NOFREEENTRY: error = "There are not entries in the processes table";
		break;
		case PROGRAMNOTVALID: error = "A process has not been created because it is not valid";
		break;
		case PROGRAMDOESNOTEXIST: error = "A process has not been created because not exists";
		break;
		case TOOBIGPROCESS: error = "A process has not been created because the main memory has no room for it";
		break;
		case MEMORYFULL: error = "There are not free space in the partition table";
		break;
		default: error = "One error has been ocurred, but i don't know is";
		break;
	}
	ComputerSystem_DebugMessage(SYSPROC,"CksRss","ERROR: ",error,"\n");
}
int OperatingSystem_CreateProcess(USER_PROGRAMS_DATA executableProgram, int queueID) {//Añadimos el ID de cola
	FILE *programFile; 
	int PID=OperatingSystem_ObtainAnEntryInTheProcessTable();												// Obtain a process ID
	if(PID == NOFREEENTRY)
		return NOFREEENTRY;
	int processSize=OperatingSystem_ObtainProgramSize(&programFile, executableProgram.executableName);		// Obtain the memory requirements of the program
	if(processSize == PROGRAMNOTVALID || processSize == PROGRAMDOESNOTEXIST)
		return processSize;
	int priority=OperatingSystem_ObtainPriority(programFile);												// Obtain the priority for the process
	if(priority == PROGRAMNOTVALID || priority == PROGRAMDOESNOTEXIST)
		return priority;
	OperatingSystem_ShowPartitionTable();
	int partition = OperatingSystem_ObtainMainMemory(processSize, PID);										// Obtain enough memory space
	OperatingSystem_ShowPartitionTable();
	if(partition == TOOBIGPROCESS || partition == MEMORYFULL)
		return partition;
	OperatingSystem_LoadProgram(programFile, partitionsTable[partition].initAddress);						// Load program in the allocated memory
	OperatingSystem_PCBInitialization(PID, partition, processSize, priority,queueID);
	return PID;
}
void OperatingSystem_PCBInitialization(int PID, int partition, int processSize, int priority, int queueID ) {//Modifico encabezado para pasar la posicion de la particion en vez de la direccion base.
	processTable[PID].busy=1;
	processTable[PID].initialPhysicalAddress = partitionsTable[partition].initAddress;
	processTable[PID].processSize=processSize;
	processTable[PID].copyOfPCRegister=0;
	processTable[PID].priority=priority;
	processTable[PID].state=NEW;
	processTable[PID].queueID = queueID;
	processTable[PID].partition = partition; //Asigno la partición
	OperatingSystem_MoveToTheREADYState(PID);
}
void OperatingSystem_MoveToTheREADYState(int PID) {
	int queue=processTable[PID].queueID;
	if (Heap_add(PID, readyToRunQueue[queue],QUEUE_PRIORITY ,numberOfReadyToRunProcesses[queue]++ ,PROCESSTABLEMAXSIZE)>=0) {							//Incremento la cola en la llamada a la función.
		ComputerSystem_DebugMessage(SYSPROC,"CkOsGdsGss","Proceso [",PID,"] pasando del estado [",statesNames[processTable[PID].state],"] al estado [");
		processTable[PID].state=READY;
		ComputerSystem_DebugMessage(SYSPROC,"Gss",statesNames[processTable[PID].state],"]\n");
	} 
	else 
	  ComputerSystem_DebugMessage(SYSPROC,"CksdssGdsGss","[",Clock_GetTime(),"] ","Proceso [",PID,"] en estado [",statesNames[processTable[PID].state],"] NO puede pasar a cola de LISTOS\n");
}
int OperatingSystem_ExtractFromReadyToRun(int queueID) {
	int selectedProcess=NOPROCESS;
	selectedProcess=Heap_poll(readyToRunQueue[queueID],QUEUE_PRIORITY ,numberOfReadyToRunProcesses[queueID]);
	if (selectedProcess>=0) 
	  numberOfReadyToRunProcesses[queueID]--;
	return selectedProcess; 
}
int OperatingSystem_ShortTermScheduler() {
	int selectedProcess = OperatingSystem_ExtractFromReadyToRun(USERPROCESSQUEUE);
	return (selectedProcess != NOPROCESS ? selectedProcess : OperatingSystem_ExtractFromReadyToRun(DAEMONSQUEUE));
}
void OperatingSystem_Dispatch(int PID) {
	OperatingSystem_RestoreContext(PID);
	executingProcessID=PID;
	int oldState =processTable[PID].state;
	processTable[PID].state=EXECUTING;
	ComputerSystem_DebugMessage(SYSPROC,"CkOsGdsGssGss","Proceso [",PID,"], pasando del estado [",statesNames[oldState],"] al estado [",statesNames[processTable[PID].state],"].\n");
}
void OperatingSystem_RestoreContext(int PID) {
	registerPC_CPU=processTable[PID].copyOfPCRegister;
	registerAccumulator_CPU = processTable[PID].copyOfAccumulatorRegister;
	registerBase_MMU=processTable[PID].initialPhysicalAddress;
	registerLimit_MMU=processTable[PID].processSize;
}
void OperatingSystem_PreemptRunningProcess() {
	OperatingSystem_SaveContext(executingProcessID);
	OperatingSystem_MoveToTheREADYState(executingProcessID);
	executingProcessID=NOPROCESS;
}
void OperatingSystem_SaveContext(int PID) {
	registerMAR_CPU=MAINMEMORYSIZE-1;
	Buses_write_AddressBus_From_To(registerMAR_CPU, &registerMAR_MainMemory);
	MainMemory_readMemory();
	processTable[PID].copyOfPCRegister= registerMBR_CPU.operationCode;
	processTable[PID].copyOfAccumulatorRegister= registerAccumulator_CPU;
}
void OperatingSystem_TerminateProcess() {
	ComputerSystem_DebugMessage(SYSPROC,"CkOsGdsGssGss","Proceso [",executingProcessID,"], pasando del estado [",statesNames[processTable[executingProcessID].state],"] al estado [",statesNames[EXIT],"].\n");
	processTable[executingProcessID].state=EXIT;
	processTable[executingProcessID].busy = 0;
	OperatingSystem_ShowPartitionTable();
	OperatingSystem_ReleaseMainMemory(); //Añado V4 Liberar memoria al terminar proceso.
	OperatingSystem_ShowPartitionTable();
	numberOfNotTerminatedProcesses--;
	(numberOfNotTerminatedProcesses >0 || OperatingSystem_GetNewProgram() != -1) ? OperatingSystem_Dispatch(OperatingSystem_ShortTermScheduler()) : OperatingSystem_End();
}
void OperatingSystem_ReleaseMainMemory(){
	partitionsTable[processTable[executingProcessID].partition].occupied = 0;
	partitionsTable[processTable[executingProcessID].partition].PID = NOPROCESS;
}
void OperatingSystem_HandleException() {
	switch (registerB_CPU) {
		case DIVISIONBYZERO:ComputerSystem_DebugMessage(INTERRUPT,"CkOsdsRss","El Proceso [ ",executingProcessID," ] ha generado [","DIVISIONBYZERO","]\n");
		break;	  
		case INVALIDADDRESS: ComputerSystem_DebugMessage(INTERRUPT,"CkOsdsRss","El Proceso [ ",executingProcessID," ] ha generado [","INVALIDADDRESS","]\n");
		break;	  
		case INVALIDINSTRUCTION: ComputerSystem_DebugMessage(INTERRUPT,"CkOsdsRss","El Proceso [ ",executingProcessID," ] ha generado [","INVALIDINSTRUCTION","]\n");
		break;
	}
	OperatingSystem_TerminateProcess();
}
void OperatingSystem_HandleClockInterrupt(){
	ClockInterruption++;
	ComputerSystem_DebugMessage(INTERRUPT,"CkCsCdCs","Clock interrupt number [", ClockInterruption, "] has occurred\n");
	if(!end){
		if(OperatingSystem_LongTermScheduler() < 0 && OperatingSystem_GetNewProgram() == -1 && numberOfNotTerminatedProcesses == 0 && !end)
			OperatingSystem_End();
		else{
			while(numberOfSleepingProcesses > 0 && ClockInterruption == processTable[sleepingProcessesQueue[0]].whenToWakeUp)
				OperatingSystem_MoveToTheREADYState(Heap_poll(sleepingProcessesQueue,QUEUE_WAKEUP,numberOfSleepingProcesses--));
			if(numberOfReadyToRunProcesses[USERPROCESSQUEUE] > 0 && (processTable[executingProcessID].priority > processTable[readyToRunQueue[USERPROCESSQUEUE][0]].priority || executingProcessID == sipID)){
				int oldprocess = executingProcessID, selectedProcess = OperatingSystem_ShortTermScheduler();
				OperatingSystem_PreemptRunningProcess();
				ComputerSystem_DebugMessage(SYSPROC, "CkRsRdRsRdRs", "Proceso [",oldprocess,"] is thrown out of the processor by process [",selectedProcess,"]\n");
				OperatingSystem_Dispatch(selectedProcess);
			}
		}
	  OperatingSystem_PrintStatus();
	}
}
void OperatingSystem_HandleSystemCall() {
	int sytemCallID=registerA_CPU;
	switch (sytemCallID) {
	    case SYSCALL_PRINTEXECPID: printf("Process [%d] has the processor assigned\n",executingProcessID);
		break;
	    case SYSCALL_END: ComputerSystem_DebugMessage(SYSPROC,"CkRsRdRs","Process [",executingProcessID,"] has requested to terminate\n");
		      OperatingSystem_TerminateProcess();
		break;
	    case SYSCALL_YIELD: if(numberOfReadyToRunProcesses[processTable[executingProcessID].queueID] > 0 && processTable[readyToRunQueue[processTable[executingProcessID].queueID][0]].priority == processTable[executingProcessID].priority){
				int newprocess = OperatingSystem_ShortTermScheduler();
				ComputerSystem_DebugMessage('s',"CkOsGdsGds","Process [",executingProcessID,"] transfers control of the processor to process [",newprocess,"]\n");
				OperatingSystem_PreemptRunningProcess();
				OperatingSystem_Dispatch(newprocess);
				numberOfYIELDchange++;
				OperatingSystem_PrintStatus();
			}else
				numberOfYIELDnoChange++;
	    break;
	    case SYSCALL_SLEEP: processTable[executingProcessID].whenToWakeUp = abs(registerAccumulator_CPU) + ClockInterruption + 1;
			if(Heap_add(executingProcessID,sleepingProcessesQueue,QUEUE_WAKEUP,numberOfSleepingProcesses++,PROCESSTABLEMAXSIZE) >= 0){ //Incremento el numero de elementos de bloqueados al añadir :D
				ComputerSystem_DebugMessage(SYSPROC,"CkOsGdsGssGss","Proceso [",executingProcessID,"] pasando del estado [",statesNames[processTable[executingProcessID].state],"] al estado [",statesNames[BLOCKED],"]\n");
				processTable[executingProcessID].state = BLOCKED;
				OperatingSystem_SaveContext(executingProcessID);
				OperatingSystem_Dispatch(OperatingSystem_ShortTermScheduler());								//aquí no hay preemt asi que no corrompo la cola haciendo esto.
				OperatingSystem_PrintStatus();
			}		
		break;
		default:
			ComputerSystem_DebugMessage(INTERRUPT,"CkRsRdRsRdRs","ERROR: el proceso [", executingProcessID,"] ha realizado una llamada al sistema invalida (",sytemCallID,") y finalizara.\n");
			OperatingSystem_TerminateProcess();
		break;
	}
}
void OperatingSystem_InitializePartitionTable() {
	char lineRead[MAXLINELENGTH];
	FILE *fileMemConfig;
	fileMemConfig= fopen(MEMCONFIG, "r");
	int number = 0, initAddress = 0, currentPartition = 0;													// The initial physical address of the first partition is 0
	numberOfPartitions  = 0;
	while (fgets(lineRead, MAXLINELENGTH, fileMemConfig) != NULL) {	// The file is processed line by line
		number=atoi(lineRead);										// "number" is the size of a just read partition
		partitionsTable[currentPartition].initAddress=initAddress;
		partitionsTable[currentPartition].size=number;
		partitionsTable[currentPartition].occupied=0;				// Next partition will begin at the updated "initAdress"
		partitionsTable[currentPartition].count = 0;				//AÑADO EN EL EXAMEN 2 !!!
		initAddress+=number;										// There is now one more partition
		currentPartition++;
		numberOfPartitions++;
		maxPartitionSize = (maxPartitionSize < number) ? number : maxPartitionSize; //Busco la particion mayor
	}
}
int OperatingSystem_GetNewProgram() {
        int currentTime, programArrivalTime;
		if (numberOfProgramsInArrivalTimeQueue <= 0)			
		  return -1;  																// No new programs in command line list of programs
        currentTime = Clock_GetTime();												// Get the current simulation time
		programArrivalTime = userProgramsList[arrivalTimeQueue[0]]->arrivalTime;  	// Get arrivalTime of next program
		if(programArrivalTime < 0){
			programArrivalTime = 0;//Controlo los tiempos negativos
			ComputerSystem_DebugMessage(ALL,"CkRs","ERROR: A ver desgraciado, que es eso de andar metiendo valores negativos cuando ni el simulador del profesor los controla\n");
		}
		return (programArrivalTime > (currentTime-INTERVALBETWEENINTERRUPTS) &&  programArrivalTime <= currentTime) ? 1 : 0;
}
int OperatingSystem_ObtainAnEntryInTheProcessTable() {
	int entry=0;
	while (entry<PROCESSTABLEMAXSIZE)
		if (processTable[entry].busy==0)
			return entry;
		else
			entry++;
	return NOFREEENTRY;
}
int OperatingSystem_ObtainMainMemory(int processSize, int PID) {
	ComputerSystem_DebugMessage(SYSMEM, "CkOsGdsGds", "Se solicitan [",processSize,"]  posiciones de memoria para el proceso [",PID,"]\n");
	int i = 0, pos = -1, diff = maxPartitionSize;
	for(i = 0; i < numberOfPartitions; i++){
		if(partitionsTable[i].size >= processSize && !partitionsTable[i].occupied && diff > partitionsTable[i].size - processSize){
			diff = partitionsTable[i].size - processSize;
			pos = i;
		}
	}
	if(pos < 0){
		ComputerSystem_DebugMessage(SYSMEM, "ksGds", "ERROR: no se ha podido crear un proceso para el programa [",PID,"] porque no hay partición disponible\n");
		return (processSize > maxPartitionSize) ? TOOBIGPROCESS : MEMORYFULL;
	}
	ComputerSystem_DebugMessage(SYSMEM, "CkOsGdsGdsGdsGds", "Se asigna la particion [",pos,": ",partitionsTable[pos].initAddress," -> ", partitionsTable[pos].size,"] al proceso [", PID,"]\n");
	partitionsTable[pos].PID = PID;
	partitionsTable[pos].occupied = 1;
	partitionsTable[pos].count++;	//Añadido del examen 2 aumento el numero de usos de la partición
	return pos;
	
}
int OperatingSystem_ObtainProgramSize(FILE **programFile, char *program) {
	char lineRead[MAXLINELENGTH];
	int isComment=1;
	int programSize;
	*programFile= fopen(program, "r");
	if (*programFile==NULL)			// Check if programFile exists
		return PROGRAMDOESNOTEXIST;
	while (isComment==1) {			// Read the first number as the size of the program. Skip all comments.
		if (fgets(lineRead, MAXLINELENGTH, *programFile) == NULL)
		      return PROGRAMNOTVALID;
		else
		    if (lineRead[0]!='/') { // Line IS NOT a comment
			    isComment=0;
			    if (OperatingSystem_lineBeginsWithANumber(lineRead))
					programSize=atoi(strtok(lineRead," "));
			    else
					return PROGRAMNOTVALID;
		      }
	}
	return (programSize <= 0) ? PROGRAMNOTVALID : programSize; // Only sizes above 0 are allowed
}
int OperatingSystem_ObtainPriority(FILE *programFile) {
	char lineRead[MAXLINELENGTH];
	int isComment=1;
	int processPriority;
	while (isComment==1) {// Read the second number as the priority of the program. Skip all comments.
		if (fgets(lineRead, MAXLINELENGTH, programFile) == NULL)
		     return PROGRAMNOTVALID;
		else
		    if (lineRead[0]!='/') { // Line IS NOT a comment
			    isComment=0;
			    if (OperatingSystem_lineBeginsWithANumber(lineRead))
					processPriority=atoi(strtok(lineRead," "));
			    else
					return PROGRAMNOTVALID;
		    }
	}
	return processPriority;
}
int OperatingSystem_LoadProgram(FILE *programFile, int initialAddress) {
	char lineRead[MAXLINELENGTH];
	char *token0, *token1, *token2;	
	registerMAR_CPU=initialAddress;
	while (fgets(lineRead, MAXLINELENGTH, programFile) != NULL) {// OJO: if lineRead is greater than MAXLINELENGTH in number of characters, the program loading does not work
		registerMBR_CPU.operationCode=' ';registerMBR_CPU.operand1=registerMBR_CPU.operand2=0;
		token0=strtok(lineRead," ");
		if ((token0!=NULL) && (token0[0]!='/')) {// I have an instruction with, at least, an operation code
		      registerMBR_CPU.operationCode=tolower(token0[0]);
		      token1=strtok(NULL," ");
		    if ((token1!=NULL) && (token1[0]!='/')) {// I have an instruction with, at least, an operand
				registerMBR_CPU.operand1=atoi(token1);
			    token2=strtok(NULL," ");
			    if ((token2!=NULL) && (token2[0]!='/'))// The read line is similar to 'sum 2 3 //coment I have an instruction with two operands
					registerMBR_CPU.operand2=atoi(token2);
		    }
		    Buses_write_DataBus_From_To(registerMBR_CPU, &registerMBR_MainMemory);// Send data to main memory using the system buses
		    Buses_write_AddressBus_From_To(registerMAR_CPU, &registerMAR_MainMemory);// Tell the main memory controller to write
		    MainMemory_writeMemory();
		    registerMAR_CPU++;
		}
	}
	return SUCCESS;
}	
int OperatingSystem_lineBeginsWithANumber(char * line) {
	int i;
	for (i=0; i<strlen(line) && line[i]==' '; i++); // Don't consider blank spaces// If is there a digit number, return true
	return (i<strlen(line) && isdigit(line[i])) ? 1 : 0; // It is a positive number
}
void OperatingSystem_PrintStatus(){
	int i;
	OperatingSystem_PrintReadyToRunQueue();
	ComputerSystem_DebugMessage(SHORTTERMSCHEDULE,"s","\tCola de SLEEPING: ");
	for (i=0; i< numberOfSleepingProcesses; i++) {
		ComputerSystem_DebugMessage(SHORTTERMSCHEDULE,"sGdsdsRds","[",sleepingProcessesQueue[i],", ",processTable[sleepingProcessesQueue[i]].priority,", ",processTable[sleepingProcessesQueue[i]].whenToWakeUp,"]");
		if (i<numberOfSleepingProcesses-1)
			ComputerSystem_DebugMessage(SHORTTERMSCHEDULE,"s",", ");
	}
	ComputerSystem_DebugMessage(SHORTTERMSCHEDULE,"s","\n");
	ComputerSystem_DebugMessage(SHORTTERMSCHEDULE,"sGdsdsRdsss","\tRunning Process: [PID:",executingProcessID,", Priority: ",processTable[executingProcessID].priority,", WakeUp: ",processTable[executingProcessID].whenToWakeUp,", Queue: ",processTable[executingProcessID].queueID?"DAEMONS":"USER","]\n");
	OperatingSystem_PrintArrivalTimeQueue();
}
void OperatingSystem_PrintArrivalTimeQueue(){
  int i;
  if (numberOfProgramsInArrivalTimeQueue>0) {
	ComputerSystem_DebugMessage(LONGTERMSCHEDULE,"s","\tCola de LLEGADA de programas: ");
	for (i=0; i< numberOfProgramsInArrivalTimeQueue; i++) {
	  ComputerSystem_DebugMessage(LONGTERMSCHEDULE,"sGssRds","[",userProgramsList[arrivalTimeQueue[i]]->executableName,", ",userProgramsList[arrivalTimeQueue[i]]->arrivalTime,"]");
	  if (i<numberOfProgramsInArrivalTimeQueue-1)
		ComputerSystem_DebugMessage(LONGTERMSCHEDULE,"s",", ");
	}
	ComputerSystem_DebugMessage(LONGTERMSCHEDULE,"s","\n");
  }
}
void OperatingSystem_PrintReadyToRunQueue() {
  int i;
  ComputerSystem_DebugMessage(SHORTTERMSCHEDULE,"CkOs","Ready-to-run processes queue:\n");
   printf("	User: ");
   for(i = 0; i < numberOfReadyToRunProcesses[USERPROCESSQUEUE];i++)
     ComputerSystem_DebugMessage(SHORTTERMSCHEDULE,"sGdsGds"," [",readyToRunQueue[USERPROCESSQUEUE][i],", ",processTable[readyToRunQueue[USERPROCESSQUEUE][i]].priority,"] ");
   printf("\n");
   printf("	Daemon: ");
   for(i = 0; i < numberOfReadyToRunProcesses[DAEMONSQUEUE];i++)
     ComputerSystem_DebugMessage(SHORTTERMSCHEDULE,"sGdsGds"," [",readyToRunQueue[DAEMONSQUEUE][i],", ",processTable[readyToRunQueue[DAEMONSQUEUE][i]].priority,"] ");
   printf("\n");
}
void OperatingSystem_ShowPartitionTable(){
	ComputerSystem_DebugMessage(SYSMEM,"CkOs","[Gestion de Memoria]");
	char * type;
	type = (statePrintMem == 0) ? "BEFORE" : "AFTER";
	statePrintMem = (statePrintMem == 0) ? 1 : 0;
	ComputerSystem_DebugMessage(SYSMEM,"Osss"," ",type,"\n");
	int i;
	for(i=0;i<numberOfPartitions;i++){
		ComputerSystem_DebugMessage(SYSMEM,"sGdsGdsGds","		[",i,"] [ ",partitionsTable[i].initAddress," -> ",partitionsTable[i].size ,"]");
		(partitionsTable[i].occupied == 0) ? ComputerSystem_DebugMessage(SYSMEM,"sGss","[", "LIBRE"	,"]  \n") : ComputerSystem_DebugMessage(SYSMEM,"sGds","[ ",partitionsTable[i].PID,"] \n");
	}
}

void OperatingSystem_End(){
	end = 1;
	processTable[sipID].copyOfPCRegister=processTable[sipID].processSize-1;
	OperatingSystem_Dispatch(sipID);
}
