/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*temperaturesensor.c
*************************************************/

#include "adc.h"
#include "temperaturesensor.h"

unsigned char cAnIn;

/* Initialize the temperature sensor module */
void TemperatureSensorInit(unsigned char cAnInSet){
	cAnIn = cAnInSet;
}

/* Get the tempurature in Celsius */
unsigned char TemperatureSensorReadC(void){
	unsigned char data;
	
	//select the correct analog input pin for adc conversion
	AdcInit(cAnIn);
	
	//read in the raw data
	data = AdcRead();
	
	//convert the data into celcius
	return (data*5000/1024 - 500)/10;
}