/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*proximitysensor.h
*************************************************/

#ifndef PROXIMITYSENSOR_H
#define PROXIMITYSENSOR_H

#include <stdbool.h>

/* Initialize the proximity sensor module */
void ProximitySensorInit(volatile uint8_t* pDDR_Set, volatile uint8_t* pPORT_Set, volatile uint8_t* pPIN_Set, unsigned char nPinNum_Set);

/* Detect whether in range */
bool ProximitySensorInRange(void);

#endif /* PROXIMITYSENSOR_H */