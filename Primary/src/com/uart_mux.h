/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*uart_mux.h
*************************************************/

#ifndef UART_MUX_H
#define UART_MUX_H

#include <inttypes.h>
#include "valves.h"
#include "timer.h"
#include "macros.h"

#define UART_MUX_COMPUTER   0
#define UART_MUX_INTERNET   1
#define UART_MUX_SMART_LED  2

//Initialize the 8 channel mux/demux with 3 select pins
void UARTMuxInit(volatile uint8_t* pDDR_S0Set, volatile uint8_t* pPORT_S0Set, unsigned char nPinNum_S0Set,
						volatile uint8_t* pDDR_S1Set, volatile uint8_t* pPORT_S1Set, unsigned char nPinNum_S1Set,
						volatile uint8_t* pDDR_S2Set, volatile uint8_t* pPORT_S2Set, unsigned char nPinNum_S2Set
						);

void UARTMuxSelect(unsigned char cSelectChan);

#endif /* UART_MUX_H */