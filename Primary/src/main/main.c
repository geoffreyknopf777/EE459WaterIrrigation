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
//#include "ds1631.h"
#include "lightsensor.h"
#include "moisturesensor.h"
#include "proximitysensor.h"
#include "smartled.h"
#include "led.h"
#include "relay.h"
#include "timer.h"
#include "test.h"

#define UART_BAUD_RATE 9600
#define MAX_MSG_LEN 256
#define SMART_LED_NUM 6

//DEBUG: fix later
#define TEMP_MIN 60
#define MOISTURE_MAX 10
#define LIGHT_MIN 10
#define LIGHT_MAX 20

/*
void ds1631_init ();
void ds1631_conv ();
void ds1631_temp (unsigned char *);
*/

LED uTestLed; //test led
SmartLED aSmartLED[SMART_LED_NUM]; //smart led
char sSendMsg[MAX_MSG_LEN]; //send buffer
char sRecMsg[MAX_MSG_LEN]; //receive buffer

/*
int getTempF(){
#define DEC 0x80
	int nF, nF2, nC2;
	unsigned char aTempC[2];
	ds1631_temp(aTempC); // Read the temperature data
	if(aTempC[1] == DEC){ //with 0.5 decimal
		nC2 = 2*aTempC[0] + 1; //multiply by two for better resolution
		nF2 = 4 * (nC2) / 5 + (nC2) + 64; //calculate with 0.5 decimal portion
		nF = nF2 / 2;
	}
	else{ //without 0.5 decimal
		nF = 4*aTempC[0]/5 + aTempC[0] + 32; //calculate just integer portion
	}

	return nF;
}
*/

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
	UARTInit(UART_BAUD_RATE);                                          //uart init
	UARTMuxInit(&DDRD, &PORTD, 4, &DDRD, &PORTD, 5, &DDRD, &PORTD, 6); //uart mux init
	ds1631_init(); ds1631_conv();                                      //temperature sensor init                                          
	MoistureSensorInit(&DDRC, &PORTC, 1, 3);                           //moisture sensor init
	LightSensorInit(2);                                                //light sensor init
	ProximitySensorInit(&PORTD, &DDRD, &PIND, 2);                      //proximity sensor init
	RelayInit(&DDRB, &PORTB, 0, &DDRD, &PORTD, 7);                     //sprinkler relay init
}

int main(void)
{
	//sensor variables
	int nTemp;
	unsigned char cMoisture;
	unsigned char cLight;
	bool bProx;
	
	char sSend[2] = "g";
	char sRec[2] = "";
	char sZone1[2] = "0";
	char sZone2[2] = "0";
	
	Init();
	
	while(1){
		
		//Read sensors
		nTemp = getTempF();	                      //temperature
		cMoisture = MoistureSensorGetMoisture();	//moisture
		cLight = LightSensorGetIntensity();	      //light
		bProx = ProximitySensorInRange();	        //proximity
		
		//Get Schedule from PI
		UARTMuxSetChannel(UART_MUX_PI);
		
		while(sRec[0] != 'a'){ //keep sending signal until acknowledged
			UARTSend(sSend, 1);
			UARTReceive(sRec, 1);
		}
		sRec[0] = 0;
		
		UARTReceive(sZone1, 1); //zone 1
		UARTReceive(sZone2, 1); //zone 2
		
		//Control the valves
		if(sZone1[0] == 1 && nTemp > TEMP_MIN && cMoisture < MOISTURE_MAX && cLight > LIGHT_MIN && cLight < LIGHT_MAX && !bProx){
			RelayTurnOn0();
		}
		else{
			RelayTurnOff0();
		}
		if(sZone2[0] == 1 && nTemp > TEMP_MIN && cMoisture < MOISTURE_MAX && cLight > LIGHT_MIN && cLight < LIGHT_MAX && !bProx){
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
