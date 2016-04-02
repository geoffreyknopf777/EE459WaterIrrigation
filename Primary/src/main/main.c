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
	int nBaudRate = 9600;
	UARTInit(nBaudRate); //initialize the uart module
	//TemperatureSensorInit(&DDRC, &PORTC, 0);
	
	//Sprinkler init outputs
	ValvesInit(&DDRB, &PORTB, 0, &DDRD, &PORTD, 7);
}

int main(void)
{
	//int nMsgLen;
	//char sMsg[254];
	//unsigned char degreesCelsius;
	
	Init();
	
	while(1){
		
		ValvesTurnOn0();
		ValvesTurnOn1();
	
		delay_ms(1000);
	
		ValvesTurnOff0();
		ValvesTurnOff1();
		
		delay_ms(1000);
		
		//degreesCelsius = TemperatureSensorReadC();
		//sprintf(sMsg, "degrees Celcius: %c\r\n", degreesCelsius);
		//UARTSend(sMsg);
	}
  
	return 0;   /* never reached */
}
