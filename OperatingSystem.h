#ifndef OPERATINGSYSTEM_H
#define OPERATINGSYSTEM_H

#include <ComputerSystem.h>
#include <stdio.h>
#include <Clock.h>


#define SUCCESS 1


#define MAXLINELENGTH 150
#define PROCESSTABLEMAXSIZE 4

// Every process occupies a 60 positions main memory chunk 
// so we can use 16 positions for the system stack
#define MAINMEMORYSECTIONSIZE 60

//ERROR CREATE PROGRAM
#define PROGRAMDOESNOTEXIST -1
#define PROGRAMNOTVALID -2
#define NOFREEENTRY -3
#define TOOBIGPROCESS -4
#define MEMORYFULL -5


#define NOPROCESS -1
#define NUMBEROFQUEUES 2 // in OperatingSystem.h 
#define USERPROCESSQUEUE 0 // in OperatingSystem.h 
#define DAEMONSQUEUE 1 // in OperatingSystem.h 

#define MEMCONFIG "MemConfig"

extern int arrivalTimeQueue[USERPROGRAMSMAXNUMBER]; 
extern int numberOfProgramsInArrivalTimeQueue; 
extern int executingProcessID;
extern int numberOfYIELDchange;
extern int numberOfYIELDnoChange;
extern int numberOfPartitions;
// Enumerated type containing all the possible process states
enum ProcessStates { NEW, READY, EXECUTING, BLOCKED, EXIT};

// Enumerated type containing the list of system calls and their numeric identifiers
enum SystemCallIdentifiers { SYSCALL_PRINTPID=2, SYSCALL_END=3, SYSCALL_YIELD=4, SYSCALL_PRINTEXECPID=5, SYSCALL_SLEEP=7};

// A PCB contains all of the information about a process that is needed by the OS
//No modificar las 5 primeras posiciones, por alguna desconocida razón.
typedef struct {
	int busy;
	int initialPhysicalAddress;
	int processSize;
	int state;
	int priority;
	int copyOfPCRegister;
	int copyOfAccumulatorRegister;
	int copyOfPSWRegister;
	int queueID;
	int whenToWakeUp;
	int partition;
} PCB;

typedef struct { 
 int occupied; 
 int initAddress; // Lowest physical address of the partition 
 int size; // Size of the partition in memory positions 
 int PID; // PID of the process using the partition, if occupied
 int count; //Añado del examen :D
} PARTITIONDATA ;

extern PARTITIONDATA partitionsTable[PROCESSTABLEMAXSIZE];
extern PCB processTable[PROCESSTABLEMAXSIZE];
// Functions prototypes
void OperatingSystem_Initialize();
void OperatingSystem_InicilizateProcessTable();
void OperatingSystem_CreateDaemons();
void OperatingSystem_PCBInitialization(int, int, int, int,int);
void OperatingSystem_MoveToTheREADYState(int);
void OperatingSystem_PrintReadyToRunQueue();
void OperatingSystem_Dispatch(int);
void OperatingSystem_RestoreContext(int);
void OperatingSystem_SaveContext(int);
void OperatingSystem_HandleException();
void OperatingSystem_TerminateProcess();
void OperatingSystem_HandleSystemCall();
void OperatingSystem_PrintStatus();
void OperatingSystem_HandleClockInterrupt();
void OperatingSystem_PrintArrivalTimeQueue();
void OperatingSystem_ShowPartitionTable();
void OperatingSystem_ReleaseMainMemory();
void OperatingSystem_End();								//Es mia.
void OperatingSystem_LongTermSchedulerERROR(int);		//Es mia.
void OperatingSystem_InitializePartitionTable();		//V4
int OperatingSystem_LongTermScheduler();
void OperatingSystem_PreemptRunningProcess();
int OperatingSystem_CreateProcess(USER_PROGRAMS_DATA,int);
int OperatingSystem_ObtainAnEntryInTheProcessTable();
int OperatingSystem_ObtainMainMemory(int, int);
int OperatingSystem_ShortTermScheduler();
int OperatingSystem_ExtractFromReadyToRun(int);
int OperatingSystem_LoadProgram(FILE *, int);
int OperatingSystem_ObtainProgramSize(FILE **, char *);
int OperatingSystem_ObtainPriority(FILE *);
int OperatingSystem_lineBeginsWithANumber(char *);
int OperatingSystem_ExtractFromReadyToRun(int queueID);
int OperatingSystem_GetNewProgram();
#endif
