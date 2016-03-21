/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*smartled.h
*************************************************/

#ifndef SMARTLED_H
#define SMARTLED_H

#include color.h

typedef struct SmartLED{
	ColorRGB;
};

/* Initialize the smart led module */
void SmartLEDInit(SmartLED* pSmartLed);

/* Set the color of the smart led module */
void SmartLEDSetColor(SmartLED* pSmartLed, ColorRGB uColor);

/* Get the color of the smart led module */
ColorRGB SmartLEDGetColor(SmartLED* pSmartLed);

#endif /* SMARTLED_H */