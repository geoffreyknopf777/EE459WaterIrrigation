/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*valves.h
*************************************************/

#ifndef VALVES_H
#define VALVES_H

#include <inttypes.h>

/* Initialize the valves module */
void ValvesInit(volatile uint8_t* pDDR_V0Set, volatile uint8_t* pPORT_V0Set, unsigned char nPinNum_V0Set,
						volatile uint8_t* pDDR_V1Set, volatile uint8_t* pPORT_V1Set, unsigned char nPinNum_V1Set);

/* Turn on the first valve */
void ValvesTurnOn0(void);

/* Turn off the first valve */
void ValvesTurnOff0(void);

/* Turn on the second valve */
void ValvesTurnOn1(void);

/* Turn off the second valve */
void ValvesTurnOff1(void);

#endif /* VALVES_H */