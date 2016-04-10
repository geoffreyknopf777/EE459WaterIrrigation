/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*relay.c
*************************************************/

#include "macros.h"
#include "relay.h"

//PORT pointers						
static volatile uint8_t* pPORT_R0;
static volatile uint8_t* pPORT_R1;					
						
//Pin numbers
static unsigned char nPinNum_R0;
static unsigned char nPinNum_R1;

/* Initialize the relay module */
void RelayInit(volatile uint8_t* pDDR_R0Set, volatile uint8_t* pPORT_R0Set, unsigned char nPinNum_R0Set,
						volatile uint8_t* pDDR_R1Set, volatile uint8_t* pPORT_R1Set, unsigned char nPinNum_R1Set){

	//save settings
	pPORT_R0 = pPORT_R0Set;
	pPORT_R1 = pPORT_R1Set;
	nPinNum_R0 = nPinNum_R0Set;
	nPinNum_R0 = nPinNum_R0Set;
	
	//initialize the select bit outputs
	SetBits(*pDDR_R0Set, nPinNum_R0, 1);
	SetBits(*pDDR_R1Set, nPinNum_R1, 1);
	
	//Set the initial state as off:
	ClearBits(*pPORT_R0, nPinNum_R0, 1);
	ClearBits(*pPORT_R1, nPinNum_R1, 1);
						
}

/* Turn on the first relay */
void RelayTurnOn0(void){
	SetBits(*pPORT_R0, nPinNum_R0, 1);
}

/* Turn off the first relay */
void RelayTurnOff0(void){
	ClearBits(*pPORT_R0, nPinNum_R0, 1);
}

/* Turn on the second relay */
void RelayTurnOn1(void){
	SetBits(*pPORT_R1, nPinNum_R1, 1);
}

/* Turn off the second relay */
void RelayTurnOff1(void){
	ClearBits(*pPORT_R1, nPinNum_R1, 1);
}