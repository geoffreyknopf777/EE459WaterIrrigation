/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*relay.h
*************************************************/

#ifndef RELAY_H
#define RELAY_H

#include <inttypes.h>

/* Initialize the valves module */
void RelayInit(volatile uint8_t* pDDR_R0Set, volatile uint8_t* pPORT_R0Set, unsigned char nPinNum_R0Set,
						volatile uint8_t* pDDR_R1Set, volatile uint8_t* pPORT_R1Set, unsigned char nPinNum_R1Set);

/* Turn on the first relay */
void RelayTurnOn0(void);

/* Turn off the first relay */
void RelayTurnOff0(void);

/* Turn on the second relay */
void RelayTurnOn1(void);

/* Turn off the second relay */
void RelayTurnOff1(void);

#endif /* RELAY_H */