/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*color.h
*************************************************/

#ifndef COLOR_H
#define COLOR_H

/* Common color definitions */
#define COLOR_RED     ( ColorRGBCreate(255, 0, 0) )
#define COLOR_GREEN   ( ColorRGBCreate(0, 255, 0) )
#define COLOR_BLUE    ( ColorRGBCreate(0, 0, 255) )
#define COLOR_PURPLE  ( ColorRGBCreate(160, 32, 240) )
#define COLOR_NONE    ( ColorRGBCreate(0, 0, 0) )

/* RGB color structure definition */
struct ColorRGB{
	unsigned char cRed;
	unsigned char cGreen;
	unsigned char cBlue;
};

/* Get the red component of an RGB color */
#define ColorRGBGetRed(uColorRGB) ( uColorRGB.cRed )

/* Get the green component of an RGB color */
#define ColorRGBGetGreen(uColorRGB) ( uColorRGB.cGreen )

/* Get the blue component of an RGB color */
#define ColorRGBGetBlue(uColorRGB) ( uColorRGB.cBlue )

/* Create an RGB color */
struct ColorRGB ColorRGBCreate(unsigned char cRed, unsigned char cGreen, unsigned char cBlue);

#endif /* COLOR_H */