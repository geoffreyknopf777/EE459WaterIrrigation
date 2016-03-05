/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*temperaturesensor.h
*************************************************/

#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

/* Initialize the temperature sensor module */
void TemperatureSensorInit(void);

/* Get the tempurature */
int TemperatureSensorGetTemp(void);

#endif /* TEMPERATURESENSOR_H */