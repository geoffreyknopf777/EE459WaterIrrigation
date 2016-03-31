/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*uart_mux.h
*************************************************/

#ifndef UART_MUX_H
#define UART_MUX_H

#include <inttypes.h>
#include "macros.h"

#define UART_MUX_COMPUTER   0
#define UART_MUX_INTERNET   1
#define UART_MUX_SMART_LED  2
	
//PORT pointers						
volatile uint8_t* pPORT_S0;
volatile uint8_t* pPORT_S1;
volatile uint8_t* pPORT_S2;						
						
//Pin numbers
unsigned char nPinNum_S0;
unsigned char nPinNum_S1;
unsigned char nPinNum_S2;

//Initialize the 8 channel mux/demux with 3 select pins
UARTMuxInit(volatile uint8_t* pDDR_S0Set, volatile uint8_t* pPORT_S0Set, unsigned char nPinNum_S0Set,
						volatile uint8_t* pDDR_S1Set, volatile uint8_t* pPORT_S1Set, unsigned char nPinNum_S1Set,
						volatile uint8_t* pDDR_S2Set, volatile uint8_t* pPORT_S2Set, unsigned char nPinNum_S2Set
						){
							
	//save settings
	pPORT_S0 = pPORT_S0Set;
	pPORT_S1 = pPORT_S1Set;
	pPORT_S2 = pPORT_S2Set;
	nPinNum_S0 = nPinNum_S0Set;
	nPinNum_S0 = nPinNum_S0Set;
	nPinNum_S0 = nPinNum_S0Set;
	
	//initialize the select bit outputs
	SetBits(*pDDR_S0Set, nPinNum_S0, 1);
	SetBits(*pDDR_S1Set, nPinNum_S1, 1);
	SetBits(*pDDR_S2Set, nPinNum_S2, 1);
	
	//Set the initial state as off:
	SetBits(*pPORT_S0, nPinNum_S0, 0);
	SetBits(*pPORT_S1, nPinNum_S1, 0);
	SetBits(*pPORT_S2, nPinNum_S2, 0);
}

UARTMuxSelect(char cSelectChan){
	SetBits(*pPORT_S0, nPinNum_S0, GetBit(cSelectChan, 0));
	SetBits(*pPORT_S1, nPinNum_S1, GetBit(cSelectChan, 1));
	SetBits(*pPORT_S2, nPinNum_S2, GetBit(cSelectChan, 2));
}

#endif /* UART_MUX_H */