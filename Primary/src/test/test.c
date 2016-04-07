/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*test.c
*************************************************/

#include <avr/io.h>
#include "timer.h"
#include "uart_mux.h"
#include "macros.h"

#define MS_DELAY 2

/* Test all of the pins on the ATmega328P in an infinite loop */
void TestATmega328PPins(void){
	int i=0;
	
		//Set outputs
		DDRB = 0b11111101;
    DDRC = 0b11111100;
		DDRD = 0b11111111;

    while (1) {
			
			//Toggle all B outputs
			for(i=0; i<8; i++){
				SetBits(PORTB, i, 1);
				delay_ms(MS_DELAY);
				ClearBits(PORTB, i, 1);
			}
			
			//Toggle all C outputs
			for(i=0; i<8; i++){
				SetBits(PORTC, i, 1);
				delay_ms(MS_DELAY);
				ClearBits(PORTC, i, 1);
			}
			
			//Toggle all D outputs
			for(i=0; i<8; i++){
				SetBits(PORTD, i, 1);
				delay_ms(MS_DELAY);
				ClearBits(PORTD, i, 1);
			}
			
    }	
}

void TestUartMux(void){
	UARTMuxInit(&DDRD, &PORTD, 4, &DDRD, &PORTD, 5, &DDRD, &PORTD, 6); //uart mux init
	
	while(1){
		UARTMuxSelect(i);
		delay_ms(1);
		i++;
	}
}