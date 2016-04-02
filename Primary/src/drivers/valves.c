/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*valves.c
*************************************************/

#include "macros.h"
#include "valves.h"

//PORT pointers						
volatile uint8_t* pPORT_V0;
volatile uint8_t* pPORT_V1;					
						
//Pin numbers
unsigned char nPinNum_V0;
unsigned char nPinNum_V1;

/* Initialize the valves module */
void ValvesInit(volatile uint8_t* pDDR_V0Set, volatile uint8_t* pPORT_V0Set, unsigned char nPinNum_V0Set,
						volatile uint8_t* pDDR_V1Set, volatile uint8_t* pPORT_V1Set, unsigned char nPinNum_V1Set){

	//save settings
	pPORT_V0 = pPORT_V0Set;
	pPORT_V1 = pPORT_V1Set;
	nPinNum_V0 = nPinNum_V0Set;
	nPinNum_V0 = nPinNum_V0Set;
	
	//initialize the select bit outputs
	SetBits(*pDDR_V0Set, nPinNum_V0, 1);
	SetBits(*pDDR_V1Set, nPinNum_V1, 1);
	
	//Set the initial state as off:
	SetBits(*pPORT_V0, nPinNum_V0, 0);
	SetBits(*pPORT_V1, nPinNum_V1, 0);
						
}

/* Turn on the first valve */
void ValvesTurnOn0(void){
	SetBits(*pPORT_V0, nPinNum_V0, 1);
}

/* Turn off the first valve */
void ValvesTurnOff0(void){
	ClearBits(*pPORT_V0, nPinNum_V0, 1);
}

/* Turn on the second valve */
void ValvesTurnOn1(void){
	SetBits(*pPORT_V1, nPinNum_V1, 1);
}

/* Turn off the second valve */
void ValvesTurnOff1(void){
	ClearBits(*pPORT_V1, nPinNum_V1, 1);
}