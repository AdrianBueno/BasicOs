#include <MMU.h>
#include <Buses.h>
#include <Processor.h>
#include <string.h>

// The base register
int registerBase_MMU;
// The limit register
int registerLimit_MMU;

// The MAR register
int registerMAR_MMU;

// Logical address is in registerMAR_MMU. If correct, physical address is produced
// by adding logical address and base register
int MMU_readMemory() {
	if (registerMAR_MMU >= 0 && registerMAR_MMU<registerLimit_MMU) {
		// Physical address = logical address + base register
		registerMAR_MMU+=registerBase_MMU;
                // Send to the main memory HW the physical address to write in
		Buses_write_AddressBus_From_To(registerMAR_MMU, &registerMAR_MainMemory);
		// Tell the main memory HW to read
		MainMemory_readMemory();
		return MMU_SUCCESS;
	}
	else{
		Processor_RaiseException(INVALIDADDRESS);
		return MMU_FAIL;
	}
}

// Logical address is in registerMAR_MMU. If correct, physical address is produced
// by adding logical address and base register
int MMU_writeMemory() {

	if (registerMAR_MMU >= 0 && registerMAR_MMU<registerLimit_MMU) {
		// Physical address = logical address + base register
		registerMAR_MMU+=registerBase_MMU;
                // Send to the main memory HW the physical address to read from
		Buses_write_AddressBus_From_To(registerMAR_MMU, &registerMAR_MainMemory);
		// Tell the main memory HW to write
		MainMemory_writeMemory();
		return MMU_SUCCESS;
	}
	else{
		Processor_RaiseException(INVALIDADDRESS);
		return MMU_FAIL;
	}
}