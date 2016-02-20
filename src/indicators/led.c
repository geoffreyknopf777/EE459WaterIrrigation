/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*led.c
*************************************************/

#include "timer.h"
#include "macros.h"
#include "led.h"

//Initialize the led:
void LedInit(LED* pLed, volatile uint8_t* pDDR, volatile uint8_t* pPORT, unsigned char nPinNum){
	//Set the led attributes:
	(*pLed).pPORT = pPORT;
	(*pLed).nPinNum = nPinNum;
	//Set the pin as output:
	SetBits(*pDDR, nPinNum, 1);
	//Set the initial state as off:
	SetBits(*pPORT, nPinNum, 0);
}

//Turn the led on:
void LedTurnOn(LED* pLed){
	SetBits(*(*pLed).pPORT, (*pLed).nPinNum, 1);
}

//Turn the led off:
void LedTurnOff(LED* pLed){
	ClearBits(*(*pLed).pPORT, (*pLed).nPinNum, 1);
}

//Blink the led for the specified number of milliseconds:
void LedBlink(LED* pLed, int nMilliseconds){
	SetBits(*(*pLed).pPORT, (*pLed).nPinNum, 1);
	delay_ms(nMilliseconds);
	ClearBits(*(*pLed).pPORT, (*pLed).nPinNum, 1);
	delay_ms(nMilliseconds);
}

//Get the state of the led:
unsigned char LedOn(LED* pLed){
	return GetBit(*(*pLed).pPORT, (*pLed).nPinNum);
}