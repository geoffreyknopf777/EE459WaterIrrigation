/*************************************************
*Geoffrey Knopf
*EE 109
*Tues/Thurs 2:00pm
*max232.h
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