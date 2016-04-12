/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*uart.h
*************************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include "macros.h"
#include "lcd.h"
#include "uart.h"

#define FOSC 7372800      // Clock frequency
#define RX_TIMEOUT 10000  // Timeout for rx function

uint32_t nBaudRate;

void UARTInit(uint32_t nBaudRateSet){
	//Set baud rate
	nBaudRate = nBaudRateSet;
	//UBRR0 = (char) FOSC/16/nBaudRate-1;
	UBRR0 = (char) 3;
	// Enable RX and TX
	UCSR0B |= (1 << TXEN0 | 1 << RXEN0); //Turn on transmitter and receiver
	UCSR0C = (3 << UCSZ00); //Async., no parity,
	// 1 stop bit, 8 data bits
}

/* Get the current baud rate */
uint32_t UARTGetBaudRate(void){
	return nBaudRate;
}

/* Set the baud rate */
void UARTSetBaudRate(uint32_t nBaudRate){
	UARTInit(nBaudRate);
}

char rx_char();
void tx_char(char ch);

char UARTSend(char* sMsg){
	unsigned char i;
	
	for(i=0; i<sizeof(sMsg); i++){
		if(sMsg[i] == '\0'){ //detect '\0' and return
			return i; //return number of bytes sent
		}
		tx_char(sMsg[i]);
	}
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
	int nTimeout = 0;

 // Wait for receive complete flag to go high
	while ( !(UCSR0A & (1 << RXC0)) ){
		if(nTimeout > RX_TIMEOUT){
			return '\0';
		}
		nTimeout++;
	}
		return UDR0;
}

void tx_char(char ch)
{
 // Wait for transmitter data register empty
 while ((UCSR0A & (1<<UDRE0)) == 0) {}
 UDR0 = ch;
}