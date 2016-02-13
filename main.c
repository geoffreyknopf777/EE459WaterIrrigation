/*************************************************
*Geoffrey Knopf
*EE 109
*Tues/Thurs 2:00pm
*main.c
*************************************************/

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macros.h"
#include "lcd.h"
#include "encoder.h"
#include "btn.h"
#include "led.h"
#include "ds1631.h"
#include "max232.h"

#define MAX_TEMP 100
#define MIN_TEMP 0
#define LED_GREEN PB4
#define LED_RED PB5

//Global variables:
LED uLedGreen;
LED uLedRed;
BTN uBtnGreen;
BTN uBtnRed;
unsigned char sMsgSend[4];
unsigned char sMsgReceive[4];
unsigned char bSetHigh; //TRUE for set high, FALSE for set low
unsigned char sTemp[4];
unsigned char sRmt[4];
unsigned char sHigh[4];
unsigned char sLow[4];
int nTemp = 0;
int nRmt = 0;
unsigned char nLow = 0;
unsigned char nHigh = 100;

void ds1631_init ();
void ds1631_conv ();
void ds1631_temp (unsigned char *);

ISR(PCINT2_vect){
	EncoderProcess();
}

int getTempF(){
#define DEC 0x80
	int nF, nF2, nC2;
	unsigned char aTempC[2];
	ds1631_temp(aTempC); // Read the temperature data
	//Formula:
	//F = (9/5) * C + 32
	//To prevent overflow:
	//F =(4*C)/5 + C + 32
	if(aTempC[1] == DEC){ //with 0.5 decimal
		nC2 = 2*aTempC[0] + 1; //multiply by two for better resolution
		nF2 = 4 * (nC2) / 5 + (nC2) + 64; //calculate with 0.5 decimal portion
		nF = nF2 / 2;
	}
	else{ //without 0.5 decimal
		nF = 4*aTempC[0]/5 + aTempC[0] + 32; //calculate just integer portion
	}

	return nF;
}

void SendMsg(int nTemp){
		if(nTemp > 0){
			sMsgSend[0] = '+';
		}
		else{
			sMsgSend[0] = '-';
		}
		sMsgSend[1] = nTemp / 100 + '0';
		sMsgSend[2] = nTemp / 10 % 10 + '0';
		sMsgSend[3] = nTemp % 10 + '0';
		Max232SendMsg(sMsgSend, 4);
}

//Program initialization:
void Init(){
	//Lcd:
		LcdInit();
		LcdStringOut((unsigned char*)"Geoffrey Knopf");
		LcdMoveTo(1, 0);
		LcdStringOut((unsigned char*)"Thermostat");
		_delay_ms(250);
	//Temperature sensor:
		ds1631_init(); // Initialize the DS1631
		ds1631_conv(); // Set the DS1631 to do conversions
	//RS-232:
		Max232Init(&DDRB, &PORTB, PB3);
	//Encoder:
		EncoderInit(&PORTD, &PIND, PD2, PD3, 0);
		EncoderInitInterrupts(&PCICR, PCIE2, &PCMSK2, PCINT18, PCINT19);
		EncoderSetMaxPos(MAX_TEMP);
		EncoderSetMinPos(MIN_TEMP);
	//Leds:
		LedInit(&uLedGreen, &DDRB, &PORTB, PB4);
		LedInit(&uLedRed, &DDRB, &PORTB, PB5);
	//Buttons:
		BtnInit(&uBtnGreen, &DDRC, &PORTC, &PINC, PC1, TRUE);
		BtnInit(&uBtnRed, &DDRC, &PORTC, &PINC, PC2, TRUE);
	//Display labels:
		LcdWriteCommand(LCD_CLEAR_SCREEN);
		LcdStringOut((unsigned char*)"Tem:");
		LcdMoveTo(0, 8);
		LcdStringOut((unsigned char*)"Rmt:");
		LcdMoveTo(1, 0);
		LcdStringOut((unsigned char*)"L:");
		LcdMoveTo(1, 8);
		LcdStringOut((unsigned char*)"H:");
	//Initialize high and low bounds:
		nTemp = getTempF();
		nHigh = nTemp + 10;
		nLow = nTemp - 10;
	//Initialize high temperature setting:	
		EncoderSetPos(nHigh);
		EncoderSetMaxPos(MAX_TEMP);
		EncoderSetMinPos(nLow);
		bSetHigh = TRUE;
	//Send initial message to the other device:
		SendMsg(nTemp);
	//Create default strings:
		itoa((int)nTemp, (char*)sTemp, 10);
		itoa((int)nRmt, (char*)sRmt, 10);
		itoa((int)nLow, (char*)sLow, 10);
		itoa((int)nHigh, (char*)sHigh, 10);
}

void updateDisplay(unsigned char* sTemp, unsigned char* sRmt, unsigned char* sLow, unsigned char* sHigh){
	LcdStringOut((unsigned char*)"   ");
	LcdMoveTo(0, 5);
	LcdStringOut(sTemp);
	LcdMoveTo(0, 13);
	LcdStringOut((unsigned char*)"   ");
	LcdMoveTo(0, 13);
	LcdStringOut(sRmt);
	LcdMoveTo(1, 5);
	LcdStringOut((unsigned char*)"   ");
	LcdMoveTo(1, 5);
	LcdStringOut(sLow);
	LcdMoveTo(1, 13);
	LcdStringOut((unsigned char*)"   ");
	LcdMoveTo(1, 13);
	LcdStringOut(sHigh);
}

int main(void) {	
	unsigned char nSuccess = 0;
	unsigned char nEncPos = 0;
	unsigned char nTempLast = 255;
	unsigned char nRmtLast = 255;
	unsigned char nHighLast = 255;
	unsigned char nLowLast = 255;

	//Initialize modules:
	Init();

	//Loop continously:
  while (1) {

		//Get the current temperature:
		nTemp = getTempF();
		itoa(nTemp, (char*)sTemp, 10);
		
		//Send message to remote device:
		if(nTemp != nTempLast){
			SendMsg(nTemp);
		}

		//Receive message from remote device:
		nSuccess = Max232ReceiveMsg(sMsgReceive, 4);
		if(nSuccess){
			nRmt = (sMsgReceive[1] - '0') * 100 + (sMsgReceive[2] - '0') * 10 + (sMsgReceive[3]-'0');
			if(sMsgReceive[0] == '-'){
				nRmt = -nRmt;
			}
		}
		itoa(nRmt, (char*)sRmt, 10);

		//Get button presses to determine whether in set high or set low state:
		if(BtnPressed(&uBtnGreen)){
			EncoderSetPos(nHigh);
			EncoderSetMaxPos(MAX_TEMP);
			EncoderSetMinPos(nLow);
			bSetHigh = TRUE;
		}
		else if(BtnPressed(&uBtnRed)){
			EncoderSetPos(nLow);
			EncoderSetMaxPos(nHigh);
			EncoderSetMinPos(MIN_TEMP);
			bSetHigh = FALSE;
		}

		//Set the high or low temperatures:
		nEncPos = EncoderGetPos();
		if(bSetHigh){
			nHigh = nEncPos;
			itoa((int)nHigh, (char*)sHigh, 10);
		}
		else{
			nLow = nEncPos;
			itoa((int)nLow, (char*)sLow, 10);
		}

		//Decide whether to cool or heat:
		if(nTemp < nLow){ //heat
			LedTurnOn(&uLedGreen);
			LedTurnOff(&uLedRed);
		}
		else if (nTemp > nHigh){ //cool
			LedTurnOn(&uLedRed);
			LedTurnOff(&uLedGreen);
		}
		else{ //make sure both leds are off
			LedTurnOff(&uLedGreen);
			LedTurnOff(&uLedRed);
		}

		//Update Display if values change:
		if(nTemp != nTempLast || nRmt != nRmtLast || nLow != nLowLast || nHigh != nHighLast){
			updateDisplay(sTemp, sRmt, sLow, sHigh);
		}
		nTempLast = nTemp;
		nRmtLast = nRmt;
		nLowLast = nLow;
		nHighLast = nHigh;
	}

	return 0; //Code will never reach this point
}
