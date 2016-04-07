/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*uart_mux.c
*************************************************/

#include <inttypes.h>
#include "valves.h"
#include "timer.h"
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
void UARTMuxInit(volatile uint8_t* pDDR_S0Set, volatile uint8_t* pPORT_S0Set, unsigned char nPinNum_S0Set,
						volatile uint8_t* pDDR_S1Set, volatile uint8_t* pPORT_S1Set, unsigned char nPinNum_S1Set,
						volatile uint8_t* pDDR_S2Set, volatile uint8_t* pPORT_S2Set, unsigned char nPinNum_S2Set
						){
							
	//save settings
	pPORT_S0 = pPORT_S0Set;
	pPORT_S1 = pPORT_S1Set;
	pPORT_S2 = pPORT_S2Set;
	nPinNum_S0 = nPinNum_S0Set;
	nPinNum_S1 = nPinNum_S1Set;
	nPinNum_S2 = nPinNum_S2Set;
	
	//initialize the select bit outputs
	SetBits(*pDDR_S0Set, nPinNum_S0, 1);
	SetBits(*pDDR_S1Set, nPinNum_S1, 1);
	SetBits(*pDDR_S2Set, nPinNum_S2, 1);
	
	//Set the initial state as off:
	ClearBits(*pPORT_S0, nPinNum_S0, 1);
	ClearBits(*pPORT_S1, nPinNum_S1, 1);
	ClearBits(*pPORT_S2, nPinNum_S2, 1);
}

void UARTMuxSelect(unsigned char cSelectChan){
	
	//select 0
	if(GetBit(cSelectChan, 0)){
		/*
		ValvesTurnOn0();
		delay_ms(1);
		ValvesTurnOff0();
		delay_ms(1);
		*/
		SetBits(*pPORT_S0, nPinNum_S0, 1);
	}
	else{
		/*
		ValvesTurnOn0();
		delay_ms(1);
		ValvesTurnOff0();
		delay_ms(1);
		ValvesTurnOn0();
		delay_ms(1);
		ValvesTurnOff0();
		delay_ms(1);
		*/
		ClearBits(*pPORT_S0, nPinNum_S0, 1);
	}
	
	//select 1
	if(GetBit(cSelectChan, 1)){
		SetBits(*pPORT_S1, nPinNum_S1, 1);
	}
	else{
		ClearBits(*pPORT_S1, nPinNum_S1, 1);
	}
	
	//select 2
	if(GetBit(cSelectChan, 2)){
		SetBits(*pPORT_S2, nPinNum_S2, 1);
	}
	else{
		ClearBits(*pPORT_S2, nPinNum_S2, 1);
	}
}