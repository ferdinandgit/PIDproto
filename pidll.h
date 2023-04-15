

#pragma once 

#include <stdint.h>
#include <pid.h>
extern int leftcounter;
extern int rightcounter;


typedef struct{
	int pina;
	int pinb;
	int counter; 
}encoder; 

typedef struct{
	int pin;
}motor;

int encoderIrqSetup();
void incrementIrq(uint gpio,uint32_t event);
int initMotors();
int commandMotors (int pinforward,int pinbackward,double command);
int initTimer();
int removeTimer();
int movelow(PIDArchi* PIDArchi);

