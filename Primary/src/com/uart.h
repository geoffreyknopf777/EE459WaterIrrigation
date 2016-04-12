/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*uart.h
*************************************************/

#include <inttypes.h>

/* Initialize the UART module with a particular buad rate */
void UARTInit(uint32_t nBaudRateSet);

/* Get the current baud rate */
uint32_t UARTGetBuadRate(void);

/* Set the baud rate */
void UARTSetBuadRate(uint32_t nBaudRateSet);

/* Sends the contents of sMsg up to nMaxBytes. Returns the number of bytes sent. 
Will stop sending when '\0' or nMaxBytes is encountered
*/
char UARTSend(char* sMsg);

/* Receives message into sMsg up to nMaxBytes. Returns the number of bytes received. 
Will stop receiving when '\0' or nMaxBytes is encountered
*/
char UARTReceive(char* sMsg);