/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*main.c
*************************************************/

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "macros.h"
#include "uart.h"
#include "test.h"

#define MAX_MSG_LEN 256

char sSendMsg[MAX_MSG_LEN]; //send buffer
char sRecMsg[MAX_MSG_LEN]; //receive buffer

void RunTests(void){
	TestATmega328PPins();
}

void Init(void){
	int nBaudRate = 9600;
	UARTInit(nBaudRate); //initialize the uart module
}

int main(void)
{
	int nMsgLen;
	
	Init();
	
	while(1){
		// Wait for transmitter data register empty
                //while ((UCSR0A & (1<<UDRE0)) == 0) {}
                //UDR0 = 'a';
		
		//sprintf(sMsg, "Hello world!\r\n", sizeof(sMsg));
	        nMsgLen = UARTReceive(sRecMsg);
		sprintf(sSendMsg, "%s\r\n", sRecMsg);
		if(nMsgLen > 0){
			nMsgLen = UARTSend(sSendMsg);
		}
	}
  
	return 0;   /* never reached */
}
