/*************************************************
*Geoffrey Knopf
*EE 109
*Tues/Thurs 2:00pm
*macros.h
*************************************************/

#define TRUE 1
#define FALSE 0

//Length of array
#define ARR_SIZE(arr) (sizeof((arr))/sizeof((arr)[0]))

//Bit manipulation macros
#define SetBits(BYTE, BITNUM, VALUE) ( BYTE |= (VALUE << BITNUM) )
#define ClearBits(BYTE, BITNUM, VALUE) ( BYTE &= ~(VALUE << BITNUM) )
#define ToggleBits(BYTE, BITNUM, VALUE) ( BYTE ^= (VALUE << BITNUM) )
#define GetBit(BYTE, BITNUM) ( (BYTE & (1 << BITNUM)) >> BITNUM )