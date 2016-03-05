/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*lcd.h
*************************************************/

#ifndef LCD_H
#define LCD_H

//LCD Pin Redefines
#define LCD_RS PB0
#define LCD_ENABLE PB1
#define LCD_DATA_LINE PD4

//LCD Commands
#define LCD_CLEAR_SCREEN 0x01
#define LCD_CURSOR_HOME 0x02
#define LCD_DISPLAY_ON 0x0f
#define LCD_DISPLAY_OFF 0x08

typedef enum {
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	SELECT,
} LCD_BTN_PRESSED;

//Initialize the lcd module:
void LcdInit();

//Write a command to the lcd board:
void LcdWriteCommand(unsigned char x);

//Output the given string to the current cursor position:
void LcdStringOut(unsigned char *str);

//Move the cursor to the given row and column (starting index of 0):
void LcdMoveTo(unsigned char row, unsigned char col);

//Get the button pressed on the LCD board:
LCD_BTN_PRESSED LcdGetBtnPressed(void);

#endif /* LCD_H */