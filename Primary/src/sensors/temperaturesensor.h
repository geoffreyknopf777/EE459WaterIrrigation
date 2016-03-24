/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*temperaturesensor.h
*************************************************/

#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include <inttypes.h>

/* Initialize the temperature sensor module */
void TemperatureSensorInit(volatile uint8_t* pPORTSet, volatile unsigned char* pPINSet, unsigned char cAnInSet);

/* Get the tempurature in Celsius*/
unsigned char TemperatureSensorReadC(void);

#endif /* TEMPERATURESENSOR_H */