/*************************************************
*Geoffrey Knopf
*EE 109
*Tues/Thurs 2:00pm
*max232.h
*************************************************/

#include <inttypes.h>

void Max232Init(volatile uint8_t* pDDR, volatile uint8_t* pPORT, unsigned char nPinNum);

void Max232Process(void);

void Max232SendMsg(unsigned char* sMsgSend, unsigned char nLength);

unsigned char Max232ReceiveMsg(unsigned char* sMsgRecieve, unsigned char nLength);