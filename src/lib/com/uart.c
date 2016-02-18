/*************************************************
*Geoffrey Knopf
*EE 109
*Tues/Thurs 2:00pm
*uart.c
*************************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include "macros.h"
#include "lcd.h"
#include "uart.h"

#define FOSC 16000000         // Clock frequency
#define BAUD 9600             // Baud rate used
#define MYUBRR FOSC/16/BAUD-1 // Value for UBRR0

void UARTInit(void){
	//Set buad rate
	UBRR0 = MYUBRR;
	// Enable RX and TX
	UCSR0B |= (1 << TXEN0 | 1 << RXEN0); //Turn on transmitter and receiver
	UCSR0C = (3 << UCSZ00); //Async., no parity,
	// 1 stop bit, 8 data bits
}

char rx_char();
void tx_char(char ch);

char UARTSend(char* sMsg){
	unsigned char i;
	
	for(i=0; i<sizeof(sMsg); i++){
		tx_char(sMsg[i]);
		if(sMsg[i] == '\0'){ //detect '\0' and return
			return i+1; //return number of bytes sent
		}
	}
	//if the code gets here, caller forgot to add null terminator
	//insert '\0' at end and send it
	sMsg[sizeof(sMsg)-1] = '\0';
	tx_char(sMsg[sizeof(sMsg)-1]);
	return sizeof(sMsg); //return number of bytes sent
}

char UARTReceive(char* sMsg){
	unsigned char i;
	
	cli(); //clear local interrupt
	if ( !(UCSR0A & (1 << RXC0)) ){ //return if no character available in buffer
		sei(); //enable global interrupts
		return 0; //failure, no bytes received
	}

	for(i=0; i<sizeof(sMsg); i++){
		sMsg[i] = rx_char();
		if(sMsg[i] == '\0'){ //detect '\0' and return
			return i+1; //return number of bytes received
		}
	}
	//if code gets here, sender forgot to add null terminator
	//insert '\0' at end of message
	sMsg[sizeof(sMsg)-1] = '\0';
	sei(); //set enable interrupt
	return sizeof(sMsg); //success
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