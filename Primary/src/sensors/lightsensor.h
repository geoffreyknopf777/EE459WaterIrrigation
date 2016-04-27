/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*lightsensor.h
*************************************************/

#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

/* Initialize the light sensor module */
void LightSensorInit(unsigned char cAnInSet);

/* Get the light intensity */
unsigned char LightSensorGetIntensity(void);

#endif /* LIGHTSENSOR_H */