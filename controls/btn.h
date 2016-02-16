/*************************************************
*Geoffrey Knopf
*EE 109
*Tues/Thurs 2:00pm
*btn.h
*************************************************/

#include <inttypes.h>

typedef struct {
	volatile uint8_t* pPIN;
	unsigned char nPinNum;
} BTN;

//Initialize the button:
void BtnInit(BTN* pBtn, volatile uint8_t* pDDR, volatile uint8_t* pPORT, volatile uint8_t* pPIN, unsigned char nPinNum, unsigned char bPullup);

//Get state of the button:
unsigned char BtnPressed(BTN* pBtn);