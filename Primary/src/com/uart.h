/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*uart.h
*************************************************/

#include <inttypes.h>

/* Initialize the UART module with a particular baud rate */
void UARTInit(uint32_t nBaudRateSet);

/* Get the current baud rate */
uint32_t UARTGetBaudRate(void);

/* Set the baud rate */
void UARTSetBaudRate(uint32_t nBaudRateSet);

/* Sends the contents of sMsg up to nMaxBytes. Returns the number of bytes sent. 
Will stop sending when '\0' or nMaxBytes is encountered
*/
uint32_t UARTSend(char* sMsg, uint32_t size);

/* Receives message into sMsg up to nMaxBytes. Returns the number of bytes received. 
Will stop receiving when '\0' or nMaxBytes is encountered
*/
uint32_t UARTReceive(char* sMsg, uint32_t size);