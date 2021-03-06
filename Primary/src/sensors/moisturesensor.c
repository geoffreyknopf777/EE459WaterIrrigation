/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*moisturesensor.c
*************************************************/

#include "macros.h"
#include "timer.h"
#include "adc.h"
#include "moisturesensor.h"

volatile uint8_t* pPORT;
unsigned char nPinNum;
unsigned char nAnalogPinNum;

/* Initialize the humidity sensor module */
void MoistureSensorInit(volatile uint8_t* pDDRSet, volatile uint8_t* pPORTSet, unsigned char nPinNumSet, unsigned char nAnalogPinNumSet){
	nAnalogPinNum = nAnalogPinNumSet;	
	nPinNum = nPinNumSet;
	pPORT = pPORTSet;
	
	//initialize the select bit outputs
	SetBits(*pDDRSet, nPinNumSet, 1);
	
	//Set the initial state as off:
	ClearBits(*pPORTSet, nPinNumSet, 1);
}

/* Get the moisture */
unsigned char MoistureSensorGetMoisture(void){
	int i;
	int sum = 0;
	unsigned average;
	int elements = 10;
	
	//select the correct analog input pin for adc conversion
	AdcInit(nAnalogPinNum);
	
	//Turn on the moisture sensor
	SetBits(*pPORT, nPinNum, 1);
	
	//read in the raw data
	for(int i=0; i<elements; i++){
		sum += AdcRead();	
		delay_ms(10);
	}
	average = sum / elements;
	
	//Turn off the moisture sensor
	ClearBits(*pPORT, nPinNum, 1);
	
	return average;
}