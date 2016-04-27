/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*lightsensor.c
*************************************************/

#include "adc.h"
#include "lightsensor.h"

unsigned char cAnIn;

/* Initialize the light sensor module */
void LightSensorInit(unsigned char cAnInSet){
	cAnIn = cAnInSet;		
}

/* Get the light intensity */
unsigned char LightSensorGetIntensity(void){
	//select the correct analog input pin for adc conversion
	AdcInit(cAnIn);
	
	//read in the raw data
	return AdcRead();	
}