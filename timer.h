/*************************************************
*Geoffrey Knopf
*EE 109
*Tues/Thurs 2:00pm
*timer.h
*************************************************/

#include <inttypes.h>

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

//Stop a timer
void TimerStop(unsigned char cTmrIndex);

//Clear a timer
void TimerClear(unsigned char cTmrIndex);

//Get a timer count
unsigned int TimerGetCount(unsigned char cTmrIndex);