/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*smartled.c
*************************************************/

#include <stdbool.h> 
#include <inttypes.h>
#include "uart.h"
#include "uart_mux.h"
#include "timer.h"
#include "linkedlist.h"
#include "color.h"
#include "smartled.h"

#define SMART_LED_BAUD 115200

linkedlist led_list;
bool initialized = false;

/* Initialize a smart led instance.
The first led to be initialized will be the first led in the chain,
the next led to be initialized will be the next led in the chain,
and so on. */
void SmartLEDInit(struct SmartLED* pSmartLed, struct ColorRGB uColor){
	
	if(!initialized){ //initialize the linked list on first call
		LinkedListCreate(&led_list, sizeof(SmartLED), NULL, NULL);
		initialized = true;
	}
	
	(*pSmartLed).uColor = uColor; //set the color of the led
	
	LinkedListInsert(&led_list, pSmartLed); //insert the led into the linked list
}

/* Set the color of a smart led instance */
void SmartLEDSetColor(struct SmartLED* pSmartLed, struct ColorRGB uColor){
	(*pSmartLed).uColor = uColor;
}

/* Get the color of a smart led instance */
ColorRGB SmartLEDGetColor(struct SmartLED* pSmartLed){
	return (*pSmartLed).uColor;
}

/* Call this function continously in a loop or interrupt.
The smartled module must continuously send color commands
or the leds will turn themselves off to save power. 
Must communicate with pixie leds over uart with 115200 baud rate
Each led in chain interprets first 3 bytes as it's own color, 
and forwards subsequent bytes to next led in chain.
*/
void SmartLEDProcess(void){
	node* pNode;
	struct SmartLED* pLed;
	struct ColorRGB* pColor;
	char sMsg[2];
	uint32_t oldBaud;
	unsigned char oldChannel;
	
	//Set uart baud rate
	oldBaud = UARTGetBaudRate();
	oldChannel = UARTMuxGetChannel();
	UARTMuxSetChannel(UART_MUX_SMART_LED);
	UARTSetBaudRate(SMART_LED_BAUD);
	
	//Loop over each element of the led linked list
	pNode = led_list.pHead;
	while(pNode != NULL){
		pLed = (SmartLED*)(pNode->pData);
		pColor = &pLed->uColor;
		
		sprintf(sMsg, "%u", pColor->cRed);
		UARTSend(sMsg); //send red byte
		
		delay_ms(100);
		
		sprintf(sMsg, "%u", pColor->cGreen);
		UARTSend(sMsg); //send green byte
		
		delay_ms(100);
		
		sprintf(sMsg, "%u", pColor->cBlue);
		UARTSend(sMsg); //send blue byte
		
		pNode = (node*)pNode->pNext;
	}
	
	//UARTMuxSetChannel(oldChannel);
	//UARTSetBaudRate(oldBaud);
	
	//Delay for 1ms after sending color info
	delay_ms(1000);
	
}