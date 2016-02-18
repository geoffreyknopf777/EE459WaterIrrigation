/*************************************************************
*       at328-0.c - Demonstrate simple I/O functions of ATmega328
*
*       Program loops turning PC0 on and off as fast as possible.
*
* The program should generate code in the loop consisting of
*   LOOP:   SBI  PORTC,0        (2 cycles)
*           CBI  PORTC,0        (2 cycles)
*           RJMP LOOP           (2 cycles)
*
* PC0 will be low for 4 / XTAL freq
* PC0 will be high for 2 / XTAL freq
* A 9.8304MHz clock gives a loop period of about 600 nanoseconds.
*
* Revision History
* Date     Author      Description
* 09/14/12 A. Weber    Initial Release
* 11/18/13 A. Weber    Renamed for ATmega328P
*************************************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "macros.h"

#DEFINE MAX_MSG_LEN 10

unsigned char sMsg[MAX_MSG_LEN]; //buffer to store messages

void Init(void){
	UARTInit(); //initialize the uart module
}

//Infinite loop of test cases
void testPins(void){
	int i=0;
	int msDelay = 2;
	
		//Set outputs
		DDRB = 0b11111101;
    DDRC = 0b11111100;
		DDRD = 0b11111111;

    while (1) {
			
			//Toggle all B outputs
			for(i=0; i<8; i++){
				SetBits(PORTB, i, 1);
				_delay_ms(msDelay);
				ClearBits(PORTB, i, 1);
			}
			
			//Toggle all C outputs
			for(i=0; i<8; i++){
				SetBits(PORTC, i, 1);
				_delay_ms(msDelay);
				ClearBits(PORTC, i, 1);
			}
			
			//Toggle all D outputs
			for(i=0; i<8; i++){
				SetBits(PORTD, i, 1);
				_delay_ms(msDelay);
				ClearBits(PORTD, i, 1);
			}
			
    }	
}

int main(void)
{
	int nMsgLen;
	
	Init();
	
	while(true){
		sprintf(sMsg, "Hello");
		nMsgLen = UARTSend(sMsg);
		nMsgLen = UARTReceive(sMsg);
	}
    return 0;   /* never reached */
}