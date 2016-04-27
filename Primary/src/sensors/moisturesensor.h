/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*moisturesensor.h
*************************************************/

#ifndef MOISTURESENSOR_H
#define MOISTURESENSOR_H

/* Initialize the humidity sensor module */
void MoistureSensorInit(volatile uint8_t* pDDRSet, volatile uint8_t* pPORTSet, unsigned char nPinNumSet, unsigned char nAnalogPinNumSet);

/* Get the moisture */
unsigned char MoistureSensorGetMoisture(void);

#endif /* MOISTURESENSOR_H */