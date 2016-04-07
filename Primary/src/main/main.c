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
#include "smartled.h"
#include "valves.h"
#include "timer.h"
#include "test.h"

#define MAX_MSG_LEN 256

char sSendMsg[MAX_MSG_LEN]; //send buffer
char sRecMsg[MAX_MSG_LEN]; //receive buffer

void RunTests(void){
	TestATmega328PPins();
}

struct SmartLED uLed;

void Init(void){
	//int nBaudRate = 9600;
	//UARTInit(nBaudRate); //uart init
	UARTMuxInit(&DDRD, &PORTD, 4, &DDRD, &PORTD, 5, &DDRD, &PORTD, 6); //uart mux init
	//TemperatureSensorInit(&DDRC, &PORTC, 0);
	
	ValvesInit(&DDRB, &PORTB, 0, &DDRD, &PORTD, 7); //sprinkler valve init
	
}

int main(void)
{
	int i;
	int nMsgLen;
	char sMsg[254];
	//unsigned char degreesCelsius;
	
	Init();
	
	while(1){
		
		//delay_ms(1000);
		
		//degreesCelsius = TemperatureSensorReadC();
		
			//UARTMuxSelect(i);
			//i++;
			//if (i>8){
			//	i=0;
			//}
			
			//RunTests();
			
			
			ValvesTurnOn0();
			ValvesTurnOn1();

			delay_ms(1000);
	
			ValvesTurnOff0();
			ValvesTurnOff1();
		
		//UARTMuxSelect(UART_MUX_COMPUTER);
		//sprintf(sMsg, "hello\r\n");
		//UARTSend(sMsg);
		
	}
  
	return 0;   /* never reached */
}
