/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*encoder.c
*************************************************/

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "macros.h"
#include "lcd.h"
#include "encoder.h"

#define ENCODER_TICKS_PER_REV 64

volatile uint8_t* PORT;
volatile uint8_t* PIN;
static unsigned char PIN_A;
static unsigned char PIN_B;
int volatile nPos;
unsigned char volatile cInput;
unsigned char volatile cLastInput;
typedef enum{
	CW,
	CCW,
} ENCODER_DIR;
static ENCODER_DIR volatile eDirection;
static unsigned char bWrapping;
static int nMaxPos = ENCODER_TICKS_PER_REV;
static int nMinPos = 0;
static int nIncrement = 1;

void incrementPos(void);
void decrementPos(void);

//Initialize the encoder module
void EncoderInit(volatile uint8_t* pPORT, volatile unsigned char* pPIN, unsigned char cPINA, unsigned char cPINB, unsigned char bSetWrapping){
	
	//Set whether to wrap around:
	bWrapping = bSetWrapping;
	//Store the information about the ports:
	PORT = pPORT;
	PIN = pPIN;
	PIN_A = cPINA;
	PIN_B = cPINB;

	//Set the pull-up resistors for pins A and B:
	SetBits(*PORT, PIN_A, 1);
	SetBits(*PORT, PIN_B, 1);
	//Initialize variables:
	nPos = 0;
	//Initialize cLastInput:
	SetBits(cInput, 
			GetBit(*PIN, PIN_A), 
			0); //Put pin A in bit 0 of cInput
	SetBits(cInput, 
			GetBit(*PIN, PIN_B), 
			1); //Put pin B in bit 1 of cInput
	cLastInput = 0;
}

//Initiaize the encoder module to use interupts
void EncoderInitInterrupts(volatile uint8_t* pInterruptRegister, unsigned char cEnable, volatile uint8_t* pPinChangeRegister, unsigned char cPCINT_A, unsigned char cPCINT_B){
	//Enable interrupts for the port:
	SetBits(*pInterruptRegister, cEnable, 1);
	//Turn on the interrupts for PIN_A and PIN_B:
	SetBits(*pPinChangeRegister, cPCINT_A, 1);
	SetBits(*pPinChangeRegister, cPCINT_B, 1);
	//Enable interrupts globally:
	sei();
}

//The process for the encoder module
void EncoderProcess(void){

	//Get the current state of the encoder:
	cInput = 0;
	uint8_t PINTemp = *PIN;
	SetBits(cInput, 
			0,
			GetBit(PINTemp, PIN_A)); //Put pin A in bit 0 of cInput
	SetBits(cInput, 
			1,
			GetBit(PINTemp, PIN_B)); //Put pin B in bit 1 of cInput

	//Determine whether the rotation was clockwise or counterclockwise:
	if(cInput == cLastInput){
		return;
	}
	switch(cLastInput){
		case 0b00:
			if(cInput == 0b01)
				eDirection = CW;
			else if(cInput == 0b10)
				eDirection = CCW;
			break;
		case 0b01:
			if(cInput == 0b11)
				eDirection = CW;
			else if(cInput == 0b00)
				eDirection = CCW;
			break;
		case 0b11:
			if(cInput == 0b10)
				eDirection = CW;
			else if(cInput == 0b01)
				eDirection = CCW;
			break;
		case 0b10:
			if(cInput == 0b00)
				eDirection = CW;
			else if(cInput == 0b11)
				eDirection = CCW;
			break;
		default:
			//do nothing
			break;
	}

	//Determine which position the encoder is at:
	if(eDirection == CW)
		incrementPos();
	else if (eDirection == CCW)
		decrementPos();

	//Store the last state of the encoder:
	cLastInput = cInput;
}

void EncoderSetMaxPos(int nSetMaxPos){
	nMaxPos = nSetMaxPos;
}

int EncoderGetMaxPos(){
	return nMaxPos;
}

void EncoderSetMinPos(int nSetMinPos){
	nMinPos = nSetMinPos;
}

int EncoderGetMinPos(){
	return nMinPos;
}

void EncoderSetPos(int nSetPos){
	nPos = nSetPos;
}

int EncoderGetPos(void){
	return nPos;
}

void EncoderSetIncrement(int nIncrementSet){
	nIncrement = nIncrementSet;
}

void incrementPos(){
	nPos += nIncrement;
	if(nPos > nMaxPos){
		if(bWrapping)
			nPos = nMinPos;
		else
			nPos = nMaxPos;
	}
}

void decrementPos(){
	nPos -= nIncrement;
	if(nPos < nMinPos){
		if(bWrapping)
			nPos = nMaxPos;
		else
			nPos = nMinPos;
	}
}