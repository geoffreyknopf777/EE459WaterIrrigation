/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*main.c
*************************************************/

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "macros.h"
#include "uart.h"
#include "test.h"

#define MAX_MSG_LEN 256

char sSendMsg[MAX_MSG_LEN]; //send buffer
char sRecMsg[MAX_MSG_LEN]; //receive buffer

void RunTests(void){
	TestATmega328PPins();
}

SmartLED uLed;

void Init(void){
	int nBaudRate = 9600;
	UARTInit(nBaudRate); //initialize the uart module
	
	//Create a smart led
	ColorRGB uColor;
	uColor = ColorRGBCreate(0, 0, 0);
	SmartLEDInit(&uLed, uColor);
}

int main(void)
{
	int nMsgLen;
	
	Init();

	char color = 0;
	
	while(1){
		SmartLEDProcess();
		uLed.uColor = RGBColorCreate(255-color, color, 2*color);
		color++;
	}
  
	return 0;   /* never reached */
}
