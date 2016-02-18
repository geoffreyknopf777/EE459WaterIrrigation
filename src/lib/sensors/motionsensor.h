/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*motionsensor.h
*************************************************/

#include <avr/stdbool.h>

/* Initialize the motion sensor module */
void MotionSensorInit(int nThreshold);

/* Detect whether there has been motion */
bool MotionSensorMotionDetected(void);