/*************************************************
*Geoffrey Knopf
*EE 109
*Tues/Thurs 2:00pm
*max232.c
*************************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "macros.h"
#include <string.h>
#include "lcd.h"
#include "max232.h"

#define FOSC 16000000 // Clock frequency
#define BAUD 9600 // Baud rate used
#define MYUBRR FOSC/16/BAUD-1 // Value for UBRR0

void Max232Init(volatile uint8_t* pDDR, volatile uint8_t* pPORT, unsigned char nPinNum){
	//Set buad ratew
	UBRR0 = MYUBRR;
	// Enable RX and TX
	UCSR0B |= (1 << TXEN0 | 1 << RXEN0); 
	UCSR0C = (3 << UCSZ00); // Async., no parity,
	// 1 stop bit, 8 data bits
	//Set enable pin as an output:
	SetBits(*pDDR, nPinNum, 1);
}

char rx_char();
void tx_char(char ch);

void Max232SendMsg(unsigned char* sMsgSend, unsigned char nLength){
	unsigned char i;
	for(i=0; i<nLength; i++){
		tx_char(sMsgSend[i]);
	}
}

unsigned char Max232ReceiveMsg(unsigned char* sMsgReceive, unsigned char nLength){
	unsigned char i = 1;
	unsigned char cChar;
	cli(); //clear local interrupt
	if ( !(UCSR0A & (1 << RXC0)) ){ //return if no character available in buffer
		sei(); //enable global interrupts
		return 0; //failure
	}

	cChar = rx_char();	
	if(cChar != '+' && cChar != '-'){ // first character must be +/-
		sei(); //set enable interrupt
		return 0; //failure
	}

	sMsgReceive[i] = cChar;
	i=1;
	while(i<nLength){
	cChar =	rx_char();
		if(cChar < '0' || cChar > '9'){ //make sure valid digit
			sei(); //set enable interrupt
			return 0; //failure
		}
		sMsgReceive[i] = cChar;
		i++;
	}
	sei(); //set enable interrupt
	return 1; //success
}

char rx_char()
{
 // Wait for receive complete flag to go high
	while ( !(UCSR0A & (1 << RXC0)) ){}
		return UDR0;
}

void tx_char(char ch)
{
 // Wait for transmitter data register empty
 while ((UCSR0A & (1<<UDRE0)) == 0) {}
 UDR0 = ch;
}