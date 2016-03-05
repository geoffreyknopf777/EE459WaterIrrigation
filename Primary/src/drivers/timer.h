/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*timer.h
*************************************************/

#ifndef TIMER_H
#define TIMER_H

#include <inttypes.h>
#include <util/delay.h>

//Initialize a timer
void TimerInit(unsigned char cTmrIndex, unsigned char cPrescaler, unsigned char bPinX, unsigned char bPinY);

//Initialize a timer interrupt
void TimerInitInterrupt(unsigned char cTmrIndex, int nCyclesPerInterrupt, void* pCallback);

//Initialize a timer pwm
void TimerInitPwm(unsigned char cTmrIndex, unsigned char cMode);

//Set pulse width for pin X
void TimerSetPwmPulsePeriodX(unsigned char cTmrIndex, uint16_t cPulsePeriodClocks);

//Set pulse width for pin Y
void TimerSetPwmPulsePeriodY(unsigned char cTmrIndex, uint16_t nPulsePeriodClocks);

//Start a timer
void TimerStart(unsigned char cTmrIndex);

#endif /* TIMER_H */

//Stop a timer
void TimerStop(unsigned char cTmrIndex);

//Clear a timer
void TimerClear(unsigned char cTmrIndex);

//Get a timer count
unsigned int TimerGetCount(unsigned char cTmrIndex);

//Delay microseconds
void delay_us(int nUs);

//Delay milliseonds
void delay_ms(int nMs);