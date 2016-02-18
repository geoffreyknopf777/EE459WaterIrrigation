/*************************************************
*Geoffrey Knopf
*EE 109
*Tues/Thurs 2:00pm
*timer.c
*************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "macros.h"
#include "lcd.h"
#include "timer.h"

//Define arrays for relevant registers:
volatile uint8_t* aTCCRA[] = {&TCCR0A, &TCCR1A, &TCCR2A}; //pwm upper threshold
volatile uint8_t* aTCCRB[] = {&TCCR0B, &TCCR1B, &TCCR2B}; //pwm lower threshold
volatile uint16_t* aTCNT[] = {(uint16_t*)&TCNT0, &TCNT1, (uint16_t*)&TCNT2}; //either uint8_t* or uint16_t* for timer1
volatile uint16_t* aOCRA[] = {(uint16_t*)&OCR0A, (uint16_t*)&OCR1A, (uint16_t*)&OCR2A}; //either uint8_t* or uint16_t* for timer1 //Note: may need to switch for 16 bit timer
volatile uint16_t* aOCRB[] = {(uint16_t*)&OCR0B, (uint16_t*)&OCR1B, (uint16_t*)&OCR2B}; //either uint8_t* or uint16_t* for timer1
volatile uint16_t* aICR[] = {0, &ICR1, 0};
volatile uint8_t* aTIMSK[] = {&TIMSK0, &TIMSK1, &TIMSK2};
volatile uint8_t* aTIFR[] = {&TIFR0, &TIFR1, &TIFR2};
volatile uint8_t* aDDRX[] = {&DDRD, &DDRB, &DDRD}; //store register pointers of pwm X pins
volatile uint8_t* aDDRY[] = {&DDRD, &DDRB, &DDRB}; //store register pointers of pwm Y pins

//Define arrays for relevant register nicknames:
const unsigned char aWGML[] = {WGM00, WGM10, WGM20};
const unsigned char aWGMH[] = {WGM02, WGM12, WGM20};
const unsigned char aCS[] = {CS00, CS10, CS20};
const unsigned char aOCIEA[] = {OCIE0A, OCIE1A, OCIE2A};
const unsigned char aOCIEB[] = {OCIE0B, OCIE1B, OCIE2B};
const unsigned char aCOMA[] = {COM0A0, COM1A0, COM2A0};
const unsigned char aCOMB[] = {COM0B0, COM1B0, COM2B0};
const unsigned char aPINX[] = {PD5, PB1, PB3}; //store port numbers of pwm X pins
const unsigned char aPINY[] = {PD6, PB2, PD3}; //store port numbers of pwm Y pins

//Define constants
const uint16_t aPwmModuli[] = {255, 65534, 255};

//Callback function pointers:
static void (*aCallbacks[3])(void);

//Timer variables:
static unsigned char aPrescalers[3];
static unsigned int aPinX[3];
static unsigned int aPinY[3];


void TimerInit(unsigned char cTmrIndex, unsigned char cPrescaler, unsigned char bPinX, unsigned char bPinY){
	aPrescalers[cTmrIndex] = cPrescaler;
	aPinX[cTmrIndex] = bPinX;
	aPinY[cTmrIndex] = bPinY;
}


void TimerInitInterrupt(unsigned char cTmrIndex, int nCyclesPerInterrupt, void* pCallback){
	//Set the callback function:
	aCallbacks[cTmrIndex] = pCallback;
	//Enable the interrupts:
	if(aPinX[cTmrIndex]){
		*aOCRA[cTmrIndex] = nCyclesPerInterrupt;
		SetBits(*aTIMSK[cTmrIndex], aOCIEA[cTmrIndex], 1);
	}
	if(aPinY[cTmrIndex]){
		*aOCRB[cTmrIndex] = nCyclesPerInterrupt;
		SetBits(*aTIMSK[cTmrIndex], aOCIEB[cTmrIndex], 1);
	}
	//Enable global interrupts:
	sei();
}


//Timer0: Pins 5D(bPinA) and 6D(bPinB)
//Timer1: Pins 9D(bPinA) and 10D(bPinB)
//Timer2: Pins 11D(bPinA) and 3D(bPinB)
//Duty cycle ranging 1-100 for percentage of waveform
void TimerInitPwm(unsigned char cTmrIndex, unsigned char cMode){
	unsigned char cLowerModeBits = cMode & 0b00000011;
	unsigned char cUpperModeBits = (cMode & 0b00001100) >> 2;
	SetBits(*aTCCRA[cTmrIndex], aWGML[cTmrIndex], cLowerModeBits);
	SetBits(*aTCCRB[cTmrIndex], aWGMH[cTmrIndex], cUpperModeBits);

	//Set which pins should be controlled by the pwm and configure them as outputs:
	if(aPinX[cTmrIndex]){
		SetBits(*aTCCRA[cTmrIndex], aCOMA[cTmrIndex], 0b10);
		SetBits(*aDDRX[cTmrIndex], aPINX[cTmrIndex], 1);
	}
	if(aPinY[cTmrIndex]){
		SetBits(*aTCCRA[cTmrIndex], aCOMB[cTmrIndex], 0b10); 
		SetBits(*aDDRY[cTmrIndex], aPINY[cTmrIndex], 1);
	}
}


void TimerSetPwmPulsePeriodX(unsigned char cTmrIndex, uint16_t nPulsePeriodClocks){
	if(cTmrIndex == 1){
		*aOCRA[cTmrIndex] = nPulsePeriodClocks;
	}
	else{
		*aOCRA[cTmrIndex] = (uint8_t) nPulsePeriodClocks;
	}
}


void TimerSetPwmPulsePeriodY(unsigned char cTmrIndex, uint16_t nPulsePeriodClocks){
	if(cTmrIndex == 1){
		*aOCRB[cTmrIndex] = nPulsePeriodClocks;
	}
	else{
		*aOCRB[cTmrIndex] = (uint8_t) nPulsePeriodClocks;
	}
}


void TimerStart(unsigned char cTmrIndex){
	SetBits(*aTCCRB[cTmrIndex], aCS[cTmrIndex], aPrescalers[cTmrIndex]);
}


void TimerStop(unsigned char cTmrIndex){
	ClearBits(*aTCCRB[cTmrIndex], aCS[cTmrIndex], 0b111);
}


void TimerClear(unsigned char cTmrIndex){
	if(cTmrIndex == 1){
		*aTCNT[cTmrIndex] = 0;
	}
	else{
		*aTCNT[cTmrIndex] = (uint8_t)0;
	}
}


unsigned int TimerGetCount(unsigned char cTmrIndex){
	return (unsigned int) *aTCNT[cTmrIndex];
}


//ISRs for the timers:
ISR(TIMER0_COMPA_vect) { 
	//Call the callback function:
	aCallbacks[0]();
}

ISR(TIMER1_COMPA_vect) { 
	//Call the callback function:
	aCallbacks[1]();
}

ISR(TIMER2_COMPA_vect) { 
	//Call the callback function:
	aCallbacks[2]();
}