/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*lcd.c
*************************************************/

#include <avr/io.h>
#include "timer.h"
#include "macros.h"
#include "adc.h"
#include "lcd.h"

//LCD Button Voltages
#define UP_V     055
#define DOWN_V   103
#define LEFT_V   156
#define RIGHT_V  000
#define SELECT_V 204
#define TOL_V    010 //Tolerance for button voltages

//Prototypes for helper functions
void writenibble(unsigned char x);
void writebyte(unsigned char x);
void writedata(unsigned char x);

//Initialize the LCD module
void LcdInit()
{
	//Initialize the ADC module so that the buttons on the LCD can be detected:
	AdcInit(0);
	SetBits(DDRD, 0, 0b11111111); //Port D as outputs
	SetBits(DDRB, 0, 0b00000011); //Port B as outputs

  delay_ms(15);              // Delay at least 15ms
  // Use writenibble to send 0011
	writenibble(0x03);
  delay_ms(5);               // Delay at least 4msec
  // Use writenibble to send 0011
	writenibble(0x03);
  delay_us(120);             // Delay at least 100usec
  // Use writenibble to send 0011
	writenibble(0x03);
  // Use writenibble to send 0010    // Function Set: 4-bit interface
	writenibble(0x02);
	delay_ms(2);
  LcdWriteCommand(0x28);         // Function Set: 4-bit interface, 2 lines
	delay_ms(2);
  LcdWriteCommand(LCD_DISPLAY_ON);         // Display and cursor on
	delay_ms(2);
	LcdWriteCommand(LCD_CLEAR_SCREEN);
}

//Output the given string to the current cursor position
void LcdStringOut(unsigned char *str)
{
	unsigned char i=0;
	while(str[i]){
		writedata(str[i]);
		i++;
	}
}

//Move the cursor to the given row and column
void LcdMoveTo(unsigned char row, unsigned char col)
{
	//Create the move command:
	unsigned char cCmd = ((row==0)?(0x80):(0xc0)) + col;
	//Send the move to command:
	LcdWriteCommand(cCmd);
}

//Get the lcd button that was pressed
LCD_BTN_PRESSED LcdGetBtnPressed(void){
	int cRead;
	cRead = AdcRead();
	
	if (cRead > (UP_V - TOL_V) && cRead < (UP_V + TOL_V))
		{return UP;}
	else if (cRead > (DOWN_V - TOL_V) && cRead < (DOWN_V + TOL_V))
		{return DOWN;}
	else if (cRead > (LEFT_V - TOL_V) && cRead < (LEFT_V + TOL_V))
		{return LEFT;}
	else if (cRead > (RIGHT_V - TOL_V) && cRead < (RIGHT_V + TOL_V))
		{return RIGHT;}
	else if (cRead > (SELECT_V - TOL_V) && cRead < (SELECT_V + TOL_V))
		{return SELECT;}
	else
		{return NONE;}
}

//Output a byte to the LCD display instruction register
void LcdWriteCommand(unsigned char x)
{
	ClearBits(PORTB, LCD_RS, 1); //Select the command register
	writebyte(x); //Write a byte to the command register
}

//Output four bits from "x" to the display
void writenibble(unsigned char x)
{
	//Write data to pins:
	ClearBits(PORTD, LCD_DATA_LINE, 0x0F);
	SetBits(PORTD, LCD_DATA_LINE, x);
	//Toggle enable bit:
	ClearBits(PORTB, LCD_ENABLE, 1);
	SetBits(PORTB, LCD_ENABLE, 1);
	delay_us(250); //hold the pin high for a bit
	ClearBits(PORTB, LCD_ENABLE, 1);
}

//Output 8 bits from "x" to the display
void writebyte(unsigned char x){
	writenibble(x >> 4); //write high nibble
	writenibble(x & 0x0F); //write low nibble
	delay_ms(2);
}

//Output a byte to the LCD display data register
void writedata(unsigned char x)
{
	SetBits(PORTB, LCD_RS, 1); //Select the data register
	writebyte(x); //Write a byte to the data register
}