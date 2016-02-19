/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*btn.c
*************************************************/

#include "macros.h"
#include "btn.h"

//Initialize the button:
void BtnInit(BTN* pBtn, volatile uint8_t* pDDR, volatile uint8_t* pPORT, volatile uint8_t* pPIN, unsigned char nPinNum, unsigned char bPullup){
	//Set button attributes:
	(*pBtn).pPIN = pPIN;
	(*pBtn).nPinNum = nPinNum;
	//Set pin as input:
	SetBits(*pDDR, nPinNum, 0);
	//Enable the pullup resistor:
	if(bPullup){
		SetBits(*pPORT, nPinNum, 1);
	}
}

//Get state of the button:
unsigned char BtnPressed(BTN* pBtn){
	return !GetBit(*(*pBtn).pPIN, (*pBtn).nPinNum);
}