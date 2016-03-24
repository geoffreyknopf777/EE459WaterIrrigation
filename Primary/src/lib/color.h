/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*color.h
*************************************************/

#ifndef COLOR_H
#define COLOR_H

/* Common color definitions */
#define COLOR_RED   ( ColorCreate(255, 0, 0) )
#define COLOR_GREEN ( ColorCreate(0, 255, 0) )
#define COLOR_BLUE  ( ColorCreate(0, 0, 255) )

/* RGB color structure definition */
typedef struct {
	char cRed;
	char cGreen;
	char cBlue;
} ColorRGB;

/* Create an RGB color */
ColorRGB ColorRGBCreate(char cRed, char cGreen, char cBlue);

/* Get the red component of an RGB color */
#define ColorRGBGetRed(uColorRGB) ( uColorRGB.cRed )

/* Get the green component of an RGB color */
#define ColorRGBGetGreen(uColorRGB) ( uColorRGB.cGreen )

/* Get the blue component of an RGB color */
#define ColorRGBGetBlue(uColorRGB) ( uColorRGB.cBlue )

#endif /* COLOR_H */