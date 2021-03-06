/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*lightsensor.c
*************************************************/

#include "macros.h"
#include "adc.h"
#include "lightsensor.h"

static unsigned char cAnIn;

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