/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*proximitysensor.c
*************************************************/

#include "proximitysensor.h"

volatile uint8_t* pPIN;
unsigned char nPinNum;

/* Initialize the proximity sensor module */
void ProximitySensorInit(volatile uint8_t* pDDR_Set, volatile uint8_t* pPORT_Set, volatile uint8_t* pPIN_Set, unsigned char nPinNum_Set){
	//set pin as input
	ClearBits(*pDDR_Set, nPinNum_Set, 1);
	
	//disable the pull-up resistor
	ClearBits(*pPORT_Set, nPinNum_Set, 1);
}

/* Detect whether in range */
bool ProximitySensorInRange(void){
	return (bool)GetBit(*pPIN, nPinNum);
}

#endif /* PROXIMITYSENSOR_H */