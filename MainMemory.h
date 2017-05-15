#ifndef MAINMEMORY_H
#define MAINMEMORY_H

#include <Simulator.h>

// Main memory size (number of memory cells)
#define MAINMEMORYSIZE 256

// A memory cell is capable of storing a structure of the 
// MEMORYCELL TYPE
typedef struct {
    char operationCode;
    int operand1;
    int operand2;
} MEMORYCELL;

// Function prototypes
void MainMemory_readMemory();
void MainMemory_writeMemory();

extern MEMORYCELL registerMBR_MainMemory;
extern int registerMAR_MainMemory;

#endif