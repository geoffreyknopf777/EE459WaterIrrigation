/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*pwm.h
*************************************************/

#ifndef PWM_H
#define PWM_H

#include <inttypes.h>

//Initialize the pulse width modulation module
void PwmInit(unsigned char cTmrIndex, unsigned char cPrescaler, unsigned char cMode, unsigned char bPinX, unsigned char bPinY);

//Set the pulse width for pin X
void PwmSetPulsePeriodX(unsigned char cTmrIndex, uint16_t cPulseWidthClocks);

//Set the pulse width for pin Y
void PwmSetPulsePeriodY(unsigned char cTmrIndex, uint16_t cPulseWidthClocks);

#endif /* PWM_H */