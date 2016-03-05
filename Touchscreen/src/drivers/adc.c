/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*adc.c
*************************************************/

#include <avr/io.h>
#include "adc.h"
#include "macros.h"

void AdcInit(unsigned char cAnalogPortNum)
{
#define PRESCALER_64 0x07
	ADMUX = 0x00; //Set all bits to zero initially
	ADMUX |= (1 << REFS0); 	//Use the AVcc 5V as the  reference
	ADMUX |= (1 << ADLAR); //Left adjust for 8 bit resolution
	ADMUX |= cAnalogPortNum; //Select which input to use for the ADC
	ADCSRA |= PRESCALER_64; //Set the pre-scaler of the ADC clock to 128 
							//to bring the ADC clock in a range of 50kHz to 200kHz
	ADCSRA |= (1 << ADEN); //Enable the ADC module
}

unsigned char AdcRead(void){
	SetBits(ADCSRA, ADSC, 1); //Initiate single conversion
	while(GetBit(ADCSRA, ADSC) == 1); //Wait for conversion to finish
	return ADCH; //Return the result of the conversion
}