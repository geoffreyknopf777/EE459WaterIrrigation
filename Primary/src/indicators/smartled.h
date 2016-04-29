/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*smartled.h
*************************************************/

#ifndef SMARTLED_H
#define SMARTLED_H

#include "color.h"

struct SmartLED{
	struct ColorRGB uColor;
};

/* Set the color of a smart led instance */
void SmartLEDSetColor(struct ColorRGB uColor, int nLEDIndex);

/* Get the color of a smart led instance */
ColorRGB SmartLEDGetColor(int nLEDIndex);

/* Call this function continously in a loop or interrupt.
The smartled module must continuously send color commands
or the leds will turn themselves off to save power. 
Must communicate with pixie leds over uart with 115200 baud rate
Each led in chain interprets first 3 bytes as it's own color, 
and forwards subsequent bytes to next led in chain.
*/
void SmartLEDProcess(void);

#endif /* SMARTLED_H */