/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*adc.h
*************************************************/

#ifndef ADC_H
#define ADC_H

//Initialize the ADC module on the given analog port number
//If you wish to read from a different port, 
//This function must be called again with a new port number
void AdcInit(unsigned char cAnalogPortNum);

//Read the value from the analog port specified when the ADCInit() function was called
unsigned char AdcRead(void);

#endif /* ADC_H */