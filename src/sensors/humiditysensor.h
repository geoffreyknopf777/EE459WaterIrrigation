/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*humiditysensor.h
*************************************************/

#ifndef HUMIDITYSENSOR_H
#define HUMIDITYSENSOR_H

/* Initialize the humidity sensor module */
void HumiditySensorInit(void);

/* Get the humidity */
int HumiditySensorGetHumidity(void);

#endif /* HUMIDITYSENSOR_H */