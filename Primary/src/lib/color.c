/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*color.c
*************************************************/

#include "color.h"

/* Create an RGB color */
struct ColorRGB ColorRGBCreate(unsigned char cRed, unsigned char cGreen, unsigned char cBlue){
	struct ColorRGB uColorRGB;
	
	uColorRGB.cRed = cRed;
	uColorRGB.cGreen = cGreen;
	uColorRGB.cBlue = cBlue;
	
	return uColorRGB;
}