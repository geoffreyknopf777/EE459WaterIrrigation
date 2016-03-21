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
	int index;
	ColorRGB color;
};

/* Initialize a smart led instance */
void SmartLEDInit(SmartLED* pSmartLed);

/* Set the color of the smart led module */
void SmartLEDSetColor(SmartLED* pSmartLed, ColorRGB uColor);

/* Get the color of the smart led module */
ColorRGB SmartLEDGetColor(SmartLED* pSmartLed);

/* Call this function periodically.
The smartled module must continuously send color commands
or the leds will turn themselves off to save power */
void SmartLEDProcess(void);

#endif /* SMARTLED_H */