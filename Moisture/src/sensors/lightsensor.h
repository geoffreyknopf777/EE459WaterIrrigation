/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*lightsensor.h
*************************************************/

#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

/* Initialize the light sensor module */
void LightSensorInit(void);

/* Get the light intensity */
int LightSensorGetIntensity(void);

#endif /* LIGHTSENSOR_H */