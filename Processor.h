#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <MainMemory.h>

#define POWEROFF 1

#define INTERRUPTTYPES 10

// Enumerated type that connects bit positions in the PSW register with
// processor events 
enum PSW_BITS {POWEROFF_BIT=0, IOEND_BIT=1, CLOCKINT_BIT=2, EXCEPTION_BIT=8, SYSCALL_BIT=9};
//Exeptions
enum EXCEPTIONS {DIVISIONBYZERO, INVALIDADDRESS, INVALIDINSTRUCTION};
// Functions prototypes
void Processor_InitializeInterruptVectorTable();
void Processor_InstructionCycleLoop();
void Processor_FetchInstruction();
void Processor_DecodeAndExecuteInstruction();
void Processor_ManageInterrupts();
void Processor_CopyInSystemStack(int, int);
void Processor_ActivateBit(const unsigned int);
void Processor_DeactivateBit(const unsigned int);
unsigned int Processor_BitState(const unsigned int);
void Processor_RaiseException(int);


extern MEMORYCELL registerMBR_CPU;
extern int registerMAR_CPU;

// The OS needs to access the PC register to restore the context of
// the process to which the processor is being assigned
extern int registerPC_CPU;

// The OS needs to access the accumulator register to restore the context of
// the process to which the processor is being assigned and to save the context
// of the process being preempted for another ready process
extern int registerAccumulator_CPU;

// The OS needs to access register A to when executing the system call management
// routine, so it will be able to know the invoked system call identifier
// llamada al sistema realizada
extern int registerA_CPU;

//Por si algo fuera necesita acceder
extern int registerB_CPU;

#endif
