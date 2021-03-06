/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*uart_mux.c
*************************************************/

#include <inttypes.h>
#include "relay.h"
#include "timer.h"
#include "macros.h"
#include "uart_mux.h"

#define UART_MUX_COMPUTER   0
#define UART_MUX_INTERNET   1
#define UART_MUX_SMART_LED  2
	
//Selected channel
unsigned char cChannel;
	
//PORT pointers						
static volatile uint8_t* pPORT_S0;
static volatile uint8_t* pPORT_S1;
static volatile uint8_t* pPORT_S2;						
						
//Pin numbers
static unsigned char nPinNum_S0;
static unsigned char nPinNum_S1;
static unsigned char nPinNum_S2;

//Initialize the 8 channel mux/demux with 3 select pins
void UARTMuxInit(volatile uint8_t* pDDR_S0Set, volatile uint8_t* pPORT_S0Set, unsigned char nPinNum_S0Set,
						volatile uint8_t* pDDR_S1Set, volatile uint8_t* pPORT_S1Set, unsigned char nPinNum_S1Set,
						volatile uint8_t* pDDR_S2Set, volatile uint8_t* pPORT_S2Set, unsigned char nPinNum_S2Set
						){
							
	cChannel = 0; //initialize the channel to 0						
							
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

void UARTMuxSetChannel(unsigned char cSelectChan){
	cChannel = cSelectChan;
	
	//select 0
	if(GetBit(cChannel, 0)){
		SetBits(*pPORT_S0, nPinNum_S0, 1);
	}
	else{
		ClearBits(*pPORT_S0, nPinNum_S0, 1);
	}
	
	//select 1
	if(GetBit(cChannel, 1)){
		SetBits(*pPORT_S1, nPinNum_S1, 1);
	}
	else{
		ClearBits(*pPORT_S1, nPinNum_S1, 1);
	}
	
	//select 2
	if(GetBit(cChannel, 2)){
		SetBits(*pPORT_S2, nPinNum_S2, 1);
	}
	else{
		ClearBits(*pPORT_S2, nPinNum_S2, 1);
	}
	
}

unsigned char UARTMuxGetChannel(void){
	return cChannel;
}