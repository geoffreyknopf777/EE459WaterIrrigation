/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*encoder.h
*************************************************/

#ifndef ENCODER_H
#define ENCODER_H

#include <inttypes.h>

//Initialize the encoder module
void EncoderInit(volatile uint8_t* pPORT, volatile uint8_t* pPIN, unsigned char cPINA, unsigned char cPINB, unsigned char bWrapping);

//Initiaize the encoder module to use interupts
//EncoderInit() must be called before this funtion
void EncoderInitInterrupts(volatile uint8_t* pInterruptRegister, unsigned char cEnable, volatile uint8_t* pPinChangeRegister, unsigned char PCINT_A, unsigned char PCINT_B);

//Process loop for the encoder module
//Should be called as part of the main loop
//or as part of an interrupt service routine
void EncoderProcess(void);

void EncoderSetMaxPos(int nSetMaxPos);

int EncoderGetMaxPos();

void EncoderSetMinPos(int nSetMinPos);

#endif /* ENCODER_H */

int EncoderGetMinPos();

//Sets the position of the encoder
void EncoderSetPos(int nSetPos);

//Returns the current position of the encoder
int EncoderGetPos(void);

//Set the increment of the encoder
void EncoderSetIncrement(int nIncrementSet);