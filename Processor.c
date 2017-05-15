#include <Processor.h>
#include <ComputerSystem.h>
#include <OperatingSystem.h>
#include <Buses.h>
#include <MMU.h>
#include <stdio.h>
#include <string.h>

// Processor registers
int registerPC_CPU; // Program counter
int registerAccumulator_CPU; // Accumulator
MEMORYCELL registerIR_CPU; // Instruction register
int registerPSW_CPU; // Processor state word
int registerMAR_CPU; // Memory Address Register
int registerB_CPU;
MEMORYCELL registerMBR_CPU; // Memory Buffer Register
int registerA_CPU; // General purpose register

// Interrupt vector table: an array of function pointers
void (* interruptVectorTable[INTERRUPTTYPES])();


// Initialization of the interrupt vector table. Call by Operating System.
void Processor_InitializeInterruptVectorTable() {
  	interruptVectorTable[EXCEPTION_BIT]=OperatingSystem_HandleException;
  	interruptVectorTable[SYSCALL_BIT]=OperatingSystem_HandleSystemCall;
	interruptVectorTable[CLOCKINT_BIT]=OperatingSystem_HandleClockInterrupt;
}


// This is the instruction cycle loop (fetch, decoding, execution, etc.).
// The processor stops working when an POWEROFF signal is stored in its
// PSW register
void Processor_InstructionCycleLoop() {

	while (!Processor_BitState(POWEROFF_BIT)) {
		Processor_FetchInstruction();
		if(Processor_BitState(EXCEPTION_BIT)!=1)
			Processor_DecodeAndExecuteInstruction();
		Processor_ManageInterrupts();
//		OperatingSystem_PrintReadyToRunQueue();
	}
}

// Fetch an instruction from main memory and put it in the IR register
void Processor_FetchInstruction() {
	// The instruction must be located at the logical memory address pointed by the PC register
	registerMAR_CPU=registerPC_CPU;
	// Send to the MMU the address in which the reading has to take place: use the address bus for this
	Buses_write_AddressBus_From_To(registerMAR_CPU, &registerMAR_MMU);
	// Tell the main memory controller to read
	MMU_readMemory();
	//registerIR_CPU.operationCode= registerMBR_CPU.operationCode;
	//registerIR_CPU.operand1= registerMBR_CPU.operand1;
	//registerIR_CPU.operand2= registerMBR_CPU.operand2;
	// All the read data is stored in the MBR register. Because it is an instruction
	// we have to copy it to the IR register
	memcpy((void *) (&registerIR_CPU), (void *) (&registerMBR_CPU), sizeof(MEMORYCELL));
	ComputerSystem_DebugMessage(HARDWARE,"CkMcsYdsYd",registerIR_CPU.operationCode," ",registerIR_CPU.operand1," ",registerIR_CPU.operand2);
}


// Decode and execute the instruction in the IR register
void Processor_DecodeAndExecuteInstruction() {
	
	switch (registerIR_CPU.operationCode) {
	  
		// Instruction ADD
		case 'a': registerAccumulator_CPU= registerIR_CPU.operand1 + registerIR_CPU.operand2;
			  registerPC_CPU++;
			  break;
		
		// Instruction SUB
		case 's': registerAccumulator_CPU= registerIR_CPU.operand1 - registerIR_CPU.operand2;
			  registerPC_CPU++;
			  break;
		
		// Instruction DIV
		case 'd': if (registerIR_CPU.operand2 == 0)
				Processor_RaiseException(DIVISIONBYZERO);
				//Processor_ActivateBit(EXCEPTION_BIT);
			  else {
				  registerAccumulator_CPU=registerIR_CPU.operand1 / registerIR_CPU.operand2;
				  registerPC_CPU++;
			  }
			  break;
			  
		// Instruction TRAP
		case 't': Processor_ActivateBit(SYSCALL_BIT);
			  registerA_CPU=registerIR_CPU.operand1;
			  registerPC_CPU++;
			  break;
		
		// Instruction NOP
		case 'n': registerPC_CPU++;
			  break;
			  
		// Instruction JUMP
		case 'j': registerPC_CPU+= registerIR_CPU.operand1;
			  break;
			  
		// Instruction ZJUMP
		case 'z': 
			if (registerAccumulator_CPU==0)
				  registerPC_CPU+= registerIR_CPU.operand1;
			  else
				  registerPC_CPU++;
		break;

		// Instruction WRITE
		case 'w': registerMBR_CPU.operationCode= registerMBR_CPU.operand1= registerMBR_CPU.operand2= registerAccumulator_CPU;
			  registerMAR_CPU=registerIR_CPU.operand1;
			  // Send to the main memory controller the data to be written: use the data bus for this
			  Buses_write_DataBus_From_To(registerMBR_CPU, &registerMBR_MainMemory);
			  // Send to the main memory controller the address in which the writing has to take place: use the address bus for this
			  Buses_write_AddressBus_From_To(registerMAR_CPU, &registerMAR_MMU);
			  // Tell the main memory controller to write
			  MMU_writeMemory();
			  registerPC_CPU++;
			  break;

		// Instruction READ
		case 'r': registerMAR_CPU=registerIR_CPU.operand1;
			  // Send to the main memory controller the address in which the reading has to take place: use the address bus for this
			  Buses_write_AddressBus_From_To(registerMAR_CPU, &registerMAR_MMU);
			  // Tell the main memory controller to read
			  MMU_readMemory();
			  // Copy the read data to the accumulator register
			  registerAccumulator_CPU= registerMBR_CPU.operand1;
			  registerPC_CPU++;
			  break;
			  
		// Instruction MEMADD
		case 'm': registerMAR_CPU = registerIR_CPU.operand2;
			   Buses_write_AddressBus_From_To(registerMAR_CPU, &registerMAR_MMU);
			   MMU_readMemory();
			   registerAccumulator_CPU = registerMBR_CPU.operand1;
			   registerAccumulator_CPU = registerAccumulator_CPU + registerIR_CPU.operand1;
			   registerPC_CPU++;
			   break;

		// Instruction INC
		case 'i': registerAccumulator_CPU+= registerIR_CPU.operand1;
			  registerPC_CPU++;
			  break;

		// Instruction HALT
		case 'h': Processor_ActivateBit(POWEROFF_BIT);
			  break;
			  
		// Unknown instruction
		default : 
			Processor_RaiseException(INVALIDINSTRUCTION);
		//registerPC_CPU++;
			  break;
	}
	ComputerSystem_DebugMessage(HARDWARE,"GsGdWsYdWsYdWsYdWs"," (PID: ",executingProcessID,", PC: ",registerPC_CPU,",Accumulator: ",registerAccumulator_CPU," PSW: ",registerPSW_CPU,")\n");
}
	
	
// Hardware interrupt processing
void Processor_ManageInterrupts() {
  
	int i;

	// Copy PC and PSW registers in the system stack
	Processor_CopyInSystemStack(MAINMEMORYSIZE-1, registerPC_CPU);
	Processor_CopyInSystemStack(MAINMEMORYSIZE-2, registerPSW_CPU);	
	
	// Interrupts are noted from bit position 1 in the PSW register
	for (i=1;i<INTERRUPTTYPES;i++)
		// If an 'i'-type interrupt is pending
		if (Processor_BitState(i)) {
			// Deactivate interrupt
			Processor_DeactivateBit(i);
			// Call the appropriate OS interrupt-handling routine
			interruptVectorTable[i]();
		}
}


// Save in the system stack a given value
void Processor_CopyInSystemStack(int physicalMemoryAddress, int data) {

	registerMBR_CPU.operationCode=registerMBR_CPU.operand1=registerMBR_CPU.operand2=data;
	registerMAR_CPU=physicalMemoryAddress;
	Buses_write_AddressBus_From_To(registerMAR_CPU, &registerMAR_MainMemory);
	Buses_write_DataBus_From_To(registerMBR_CPU, &registerMBR_MainMemory);	
	MainMemory_writeMemory();

}

// Set a given bit position in the PSW register
void Processor_ActivateBit(const unsigned int nbit) {
	unsigned int mask = 1;

	mask = mask << nbit;
	registerPSW_CPU = registerPSW_CPU | mask;
}

// Unset a given bit position in the PSW register
void Processor_DeactivateBit(const unsigned int nbit) {
	unsigned int mask = 1;

	mask = mask << nbit;
	mask = ~mask;

	registerPSW_CPU = registerPSW_CPU & mask;
}

// Returns the state of a given bit position in the PSW register
unsigned int Processor_BitState(const unsigned int nbit) {
	unsigned int mask = 1;

	mask = mask << nbit;
	return (registerPSW_CPU & mask) >> nbit;
}

// Function to raise an exception
void Processor_RaiseException(int typeOfException) {
	Processor_ActivateBit(EXCEPTION_BIT);
	registerB_CPU=typeOfException;
}