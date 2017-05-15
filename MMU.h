#ifndef MMU_H
#define MMU_H

#include <MainMemory.h>

#define MMU_SUCCESS 1
#define MMU_FAIL -1

// Functions prototypes
int MMU_readMemory();
int MMU_writeMemory();

// These "extern" declarations enables other source code files to gain access
// to the variables listed
extern int registerBase_MMU;
extern int registerLimit_MMU;
extern int registerMAR_MMU;

#endif