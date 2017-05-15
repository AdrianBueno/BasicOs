#include <Buses.h>
#include <string.h>

//  Function that simulates the delivery of an address by means of the address bus
//  from a hardware component register to another hardware component register
void Buses_write_AddressBus_From_To(int fromRegister, int *toRegister) {
  
      *toRegister=fromRegister;
}

//  Function that simulates the delivery of memory word by means of the data bus
//  from a hardware component register to another hardware component register
void Buses_write_DataBus_From_To(MEMORYCELL fromRegister, MEMORYCELL *toRegister) {
  
//      (*toRegister).operationCode=fromRegister.operationCode;
//      (*toRegister).operand1      =fromRegister.operand1;
//      (*toRegister).operand2      =fromRegister.operand2;

	memcpy((void*) toRegister, (void *) (&fromRegister), sizeof(MEMORYCELL));
}