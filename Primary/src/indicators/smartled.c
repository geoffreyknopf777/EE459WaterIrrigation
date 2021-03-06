/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*smartled.c
*************************************************/

#include <stdbool.h> 
#include <inttypes.h>
#include "uart.h"
#include "uart_mux.h"
#include "timer.h"
#include "linkedlist.h"
#include "color.h"
#include "smartled.h"

#define SMART_LED_BAUD 115200
#define SMART_LED_NUM 6

SmartLED aSmartLeds[SMART_LED_NUM];

/* Set the color of a smart led */
void SmartLEDSetColor(struct ColorRGB uColor, int nLEDIndex){
	aSmartLeds[nLEDIndex].uColor = uColor;
}


/* Get the color of a smart led */
ColorRGB SmartLEDGetColor(int nLEDIndex){
	return aSmartLeds[nLEDIndex].uColor;
}

/* Call this function continously in a loop or interrupt.
The smartled module must continuously send color commands
or the leds will turn themselves off to save power. 
Must communicate with pixie leds over uart with 115200 baud rate
Each led in chain interprets first 3 bytes as it's own color, 
and forwards subsequent bytes to next led in chain.
*/
void SmartLEDProcess(void){
	int i;
	unsigned char sColor[3];
	
	UARTMuxSetChannel(UART_MUX_SMART_LED);
	//UARTSetBaudRate(SMART_LED_BAUD);
	
	for(i=0; i<SMART_LED_NUM; i++){
		sColor[0] = aSmartLeds[i].uColor.cRed;
		sColor[1] = aSmartLeds[i].uColor.cGreen;
		sColor[2] = aSmartLeds[i].uColor.cBlue;
		UARTSend(sColor, 3);
	}
	
	//Delay for 1ms after sending color info
	//delay_ms(1);
}