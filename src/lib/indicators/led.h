/*************************************************
*Geoffrey Knopf
*EE 109
*Tues/Thurs 2:00pm
*led.h
*************************************************/

#include <inttypes.h>

typedef struct {
	volatile uint8_t* pPORT;
	unsigned char nPinNum;
} LED;

//Initialize the led:
void LedInit(LED* pLed, volatile uint8_t* pDDR, volatile uint8_t* pPORT, unsigned char nPinNum);

//Turn the led on:
void LedTurnOn(LED* pLed);

//Turn the led off:
void LedTurnOff(LED* pLed);

//Blink the led for the specified number of milliseconds:
void LedBlink(LED* pLed, int nMilliseconds);

//Get the state of the led:
unsigned char LedOn(LED* pLed);