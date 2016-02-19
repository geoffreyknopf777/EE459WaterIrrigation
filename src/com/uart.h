/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*uart.h
*************************************************/

#include <inttypes.h>

void UARTInit(void);

/* Sends the contents of sMsg up to nMaxBytes. Returns the number of bytes sent. 
Will stop sending when '\0' or nMaxBytes is encountered
*/
char UARTSend(char* sMsg);

/* Receives message into sMsg up to nMaxBytes. Returns the number of bytes received. 
Will stop receiving when '\0' or nMaxBytes is encountered
*/
char UARTReceive(char* sMsg);