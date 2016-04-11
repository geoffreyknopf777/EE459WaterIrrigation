/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*proximitysensor.c
*************************************************/

#include "macros.h"
#include "proximitysensor.h"

static volatile uint8_t* pPIN;
static unsigned char nPinNum;

/* Initialize the proximity sensor module */
void ProximitySensorInit(volatile uint8_t* pDDR_Set, volatile uint8_t* pPORT_Set, volatile uint8_t* pPIN_Set, unsigned char nPinNum_Set){
	//get settings
	pPIN = pPIN_Set;
	
	//set pin as input
	ClearBits(*pDDR_Set, nPinNum_Set, 1);
	
	//enable the pull-up resistor
	SetBits(*pPORT_Set, nPinNum_Set, 1);
}

/* Detect whether in range */
bool ProximitySensorInRange(void){
	return (bool)GetBit(*pPIN, nPinNum);
}