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

char sMsg[MAX_MSG_LEN]; //buffer to store messages

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
		sprintf(sMsg, "Hello I am Geoff\n");
		nMsgLen = UARTSend(sMsg);
		nMsgLen = UARTReceive(sMsg);
	}
  
	return 0;   /* never reached */
}