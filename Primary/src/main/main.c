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
#include "led.h"
#include "relay.h"
#include "timer.h"
#include "test.h"

#define UART_BAUD_RATE 9600
#define MAX_MSG_LEN 256
#define SMART_LED_NUM 6

LED uTestLed; //test led
SmartLED aSmartLED[SMART_LED_NUM]; //smart led
char sSendMsg[MAX_MSG_LEN]; //send buffer
char sRecMsg[MAX_MSG_LEN]; //receive buffer

void RunTests(void){
	TestATmega328PPins();
}

struct SmartLED uLed;

void Init(void){
	int i;
	
	LedInit(&uTestLed, &DDRB, &PORTB, 1); //test led init
	for(i=0; i<SMART_LED_NUM; i++){
		SmartLEDInit(&aSmartLED[i], COLOR_RED); //smart led init
	}
	UARTInit(UART_BAUD_RATE); //uart init
	UARTMuxInit(&DDRD, &PORTD, 4, &DDRD, &PORTD, 5, &DDRD, &PORTD, 6); //uart mux init
	TemperatureSensorInit(&DDRC, &PORTC, 0); //temperature sensor init
	ProximitySensorInit(&PORTD, &DDRD, &PIND, 2); //proximity sensor init
	RelayInit(&DDRB, &PORTB, 0, &DDRD, &PORTD, 7); //sprinkler relay init
}

int main(void)
{
	unsigned char i = 0;
	int nGetScheduleLen = 11;
	char sGetSchedule[] = "GetSchedule";
	char sZone1[1];
	char sZone2[2];
	//unsigned char degreesCelsius;
	
	Init();
	
	while(1){
		
		
		//Get Schedule from PI
		UARTMuxSelect(UART_MUX_PI);
		UARTSend(sGetSchedule, nGetScheduleLen);
		UARTReceive(sZone1, 1); //zone 1
		UARTReceive(sZone2, 1); //zone 2
		
		//Control the valves
		if(sZone1[0] == '1'){
			RelayTurnOn0();
		}
		else{
			RelayTurnOff0();
		}
		if(sZone2[0] == '1'){
			RelayTurnOn1();
		}
		else{
			RelayTurnOff1();
		}		
		
		
		//LedBlink(&uTestLed, 50);
		//SmartLEDProcess();
		
		//TestUartMux();
		
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
		
		/*
		UARTMuxSetChannel(UART_MUX_COMPUTER);
		sprintf(sMsg, "a\r\n");
		UARTSend(sMsg, strlen(sMsg));
		*/
		
		/*
		//Proximity sensor code
		if(ProximitySensorInRange()){
			//code gets here if the proximity sensor is in range
			LedBlink(&uTestLed, 50);
			RelayTurnOn0();
		}
		else{
			LedBlink(&uTestLed, 2000);
		}
		*/
	}
  
	return 0;   /* never reached */
}
