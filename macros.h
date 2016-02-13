/*************************************************
*EE 459
*Team 4
*Geoffrey Knopf
*Timothy Odonga
*Jonathan Wong
*Ying Ying

*Tues/Thurs 2:00pm
*macros.h
*************************************************/

//Length of array
#define ARR_SIZE(arr) (sizeof((arr))/sizeof((arr)[0]))

//Bit manipulation macros

/* 
BYTE: byte to change
BITNUM: bit shift corresponding to where to start changing bytes. measured from the LSB
VALUE: a 1 will change the value, while a zero will leave the value the same

USAGE:
SetBits(PORTB, 0, 1) sets portb pin0 high
SetBits(PORTB, 0, 0xff) set all portb pins high
The same usage rules apply to the other macros in this file
 */
#define SetBits(BYTE, BITNUM, VALUE) ( BYTE |= (VALUE << BITNUM) )
#define ClearBits(BYTE, BITNUM, VALUE) ( BYTE &= ~(VALUE << BITNUM) )
#define ToggleBits(BYTE, BITNUM, VALUE) ( BYTE ^= (VALUE << BITNUM) )
#define GetBit(BYTE, BITNUM) ( (BYTE & (1 << BITNUM)) >> BITNUM )