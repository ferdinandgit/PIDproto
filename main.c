#include <stdint.h>
#include <stdio.h>
#include "hardware/structs/interp.h"
#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "pico/time.h"
#include <pidll.h>
#include <pid.h>


float pid[16] ={1,0,0};

int main(){
	stdio_init_all();
	encoderIrqSetup();
	initMotors();
	commandMotors(16,17,-1000);
	commandMotors(15,14,-1000);
	while(1){
		printf("left %d, right %d \n",leftcounter,rightcounter);	
		sleep_ms(100);
	}
 }

