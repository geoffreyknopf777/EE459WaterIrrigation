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
#include "uart_mux.h"
#include "temperaturesensor.h"
#include "proximitysensor.h"
#include "smartled.h"
#include "relay.h"
#include "timer.h"
#include "test.h"

#define UART_BAUD_RATE 9600
#define MAX_MSG_LEN 256

char sSendMsg[MAX_MSG_LEN]; //send buffer
char sRecMsg[MAX_MSG_LEN]; //receive buffer

void RunTests(void){
	TestATmega328PPins();
}

struct SmartLED uLed;

void Init(void){
	UARTInit(UART_BUAD_RATE); //uart init
	UARTMuxInit(&DDRD, &PORTD, 4, &DDRD, &PORTD, 5, &DDRD, &PORTD, 6); //uart mux init
	TemperatureSensorInit(&DDRC, &PORTC, 0); //temperature sensor init
	ProximitySensorInit(&PORTD, &DDRD, &PIND, 2); //proximity sensor init
	RelayInit(&DDRB, &PORTB, 0, &DDRD, &PORTD, 7); //sprinkler valve init
}

int main(void)
{
	unsigned char i = 0;
	int nMsgLen;
	char sMsg[254];
	//unsigned char degreesCelsius;
	
	Init();
	
	while(1){
		
		TestUartMux();
		
		//delay_ms(1000);
		
		//degreesCelsius = TemperatureSensorReadC();
		
		//RelayTurnOn0();
		//RelayTurnOn1();
		//delay_ms(500);
		
		//UARTMuxSelect(i);
		//delay_ms(1);
		//i++;
		
		
		/*
		SetBits(PORTD, 4, 1);
		SetBits(PORTD, 5, 1);
		SetBits(PORTD, 6, 1);
		delay_ms(100);
		ClearBits(PORTD, 4, 1);
		ClearBits(PORTD, 5, 1);
		ClearBits(PORTD, 6, 1);
		delay_ms(100);
		*/
		
		/*
		delay_ms(1000);
		for(int j=1; j<i+1; j++){
			RelayTurnOn0();
			delay_ms(100);
			RelayTurnOff0();
			delay_ms(100);
		}
		i++;
			
		delay_ms(1000);		
		*/
		
		//RelayTurnOff0();
		//RelayTurnOff1();
		//delay_ms(500);
			
		//RunTests();
		
		//UARTMuxSelect(UART_MUX_COMPUTER);
		//sprintf(sMsg, "hello\r\n");
		//UARTSend(sMsg);
		
		
		//if(ProximitySensorInRange()){
			//code gets here if the proximity sensor is in range
		//}
	}
  
	return 0;   /* never reached */
}
