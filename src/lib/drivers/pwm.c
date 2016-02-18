/*************************************************
*Geoffrey Knopf
*EE 109
*Tues/Thurs 2:00pm
*pwm.c
*************************************************/

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "macros.h"
#include "lcd.h"
#include "timer.h"
#include "pwm.h"

void PwmInit(unsigned char cTmrIndex, unsigned char cPrescaler, unsigned char cMode, unsigned char bPinX, unsigned char bPinY){
	TimerInit(cTmrIndex, cPrescaler, bPinX, bPinY);
	TimerInitPwm(cTmrIndex, cMode);
	TimerStart(cTmrIndex);
}

void PwmSetPulsePeriodX(unsigned char cTmrIndex, uint16_t nPulseWidthClocks){
	TimerSetPwmPulsePeriodX(cTmrIndex, nPulseWidthClocks);
}

void PwmSetPulsePeriodY(unsigned char cTmrIndex, uint16_t nPulseWidthClocks){
	TimerSetPwmPulsePeriodY(cTmrIndex, nPulseWidthClocks);
}