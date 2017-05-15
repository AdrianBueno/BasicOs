#include <Clock.h>
#include <Processor.h>

int time=0;

void Clock_Update() {

	time++;
	if(time% INTERVALBETWEENINTERRUPTS  == 0){//Cool code! ;D
	  Processor_ActivateBit(CLOCKINT_BIT);
	}
}


int Clock_GetTime() {

	return time;
}
