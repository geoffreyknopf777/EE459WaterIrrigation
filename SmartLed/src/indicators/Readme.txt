
/**************************************************************/
  SMARTGPU2 PLAIN C LIBRARY V5.0

This library help the user to communicate any SMARTGPU2 board with any platform running C code.
Be sure to check pinout while connecting the SMARTGPU2 boards.

---------------------IMPORTANT------------------------
Before using your smartGPU2 board, go to smartGPU2.h file and uncomment the proper line under "user modifable" section:

/*******************USER MODIFABLE**********************/
//Uncomment your preferred smartGPU2 board(only 1 at time)----------------
//#define LCD160X128   //SmartGPU2 1.8" connected via SmartSHIELD
#define LCD320X240   //SmartGPU2 2.4" connected via SmartSHIELD              //uncommented line
//#define LCD480X320   //SmartGPU2 3.5" connected via SmartSHIELD
//#define LCD480X272   //SmartGPU2 4.3" connected via SmartSHIELD
//#define LCD800X480   //SmartGPU2 7.0" connected via SmartSHIELD


User must also provide protoypes for the general putchar and getchar functions of his platform microcontroller, also for the GPIO pin connected to the Reset of SmartGPU2

/****************************************************************/
//Communication Functions(PLATFORM DEPENDENT) - MODIFY TO FIT YOUR PLATFORM
/****************************************************************/
/***Serial port prototypes configuration/definitions***/
//Sends a single character through the serial port(USART) connected to SmartGPU2
#define PUT_CHAR_SG2(data)    Serial.write(data)      //pchar(data) or put_char(data) etc.
//Returns a single character obtained from the serial port(USART) connected to SmartGPU2
#define GET_CHAR_SG2()        Serial.read()           //gchar() or get_char() etc.
//Changes/Sets a new Baudrate in the Host Processor serial port(USART)
#define SET_BAUDRATE(newBaud) Serial.begin(newBaud)   //setUsartBaud(newBaud) or setBaud(newBaud) etc.
//Performs a Hardware Reset on smartGPU2, Reset pin connected to host
#define RESET_SG2_GPIO_LOW    digitalWrite(p13, LOW)  //GPIO_Set(13,LOW)  or PORTB=0x00 etc.
#define RESET_SG2_GPIO_HIGH   digitalWrite(p13, HIGH) //GPIO_Set(13,HIGH) or PORTB=0x01 etc.
//Delay definition for some SmartGPU2 commands
#define DELAY_SG2(del)        delay(del)              //delay(del) or delay_ms(del) etc.


/**************************************************************/
Finally be sure to download the "SmartGPU2 command set.pdf" to learn more about the C functions of the library
/**************************************************************/
SMARTGPU2 boards:
http://www.vizictechnologies.com/#!products/c161y

VIZIC TECHNOLOGIES Copyright 2014

www.vizictechnologies.com
/**************************************************************/
