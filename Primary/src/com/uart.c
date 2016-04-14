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

uint32_t nBaudRate;

void UARTInit(uint32_t nBaudRateSet){
	//Set baud rate
	nBaudRate = nBaudRateSet;
	//UBRR0 = (char) FOSC/16/nBaudRate-1;
	UBRR0 = (char) 2;
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

uint32_t UARTSend(void* sMsg, uint32_t size){
	uint32_t i;
	
	for(i=0; i<size; i++){
		tx_char(((char*)sMsg)[i]);
	}
	
	return size;
}

uint32_t UARTReceive(void* sMsg, uint32_t size){
	uint32_t i;
	
	cli(); //clear local interrupt
	for(i=0; i<size; i++){
		((char*)sMsg)[i] = rx_char();
	}
	sei(); //set enable interrupt
	
  return size;
}

char rx_char()
{
	int nTimeout = 0;

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