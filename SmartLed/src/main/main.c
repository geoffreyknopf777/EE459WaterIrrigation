/*************************************************
*Water Irrigation Project
*EE 459
*Team 4
*main.c
*************************************************/
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "macros.h"
#include "uart.h"
#include "test.h"
#include "Adafruit_Pixie.h"

#define MAX_MSG_LEN 256

char sMsg[MAX_MSG_LEN]; //buffer to store messages

void RunTests(void){
	TestATmega328PPins();
}

void Init(void){
	int nBaudRate = 9600;
	UARTInit(nBaudRate); //initialize the uart module
}

void setup() {
  int i;

  Serial.begin(9600);
  Serial.println("Ready to Pixie!");

  pixieSerial.begin(115200); // Pixie REQUIRES this baud rate
  // Serial1.begin(115200);  // <- Alt. if using hardware serial port

  strip.setBrightness(200);  // Adjust as necessary to avoid blinding

  Serial.println("Red!");
  for(i=0; i< NUMPIXELS; i++)
    strip.setPixelColor(i, 255, 0, 0);
  strip.show();
  delay(300);

  Serial.println("Green!");
  for(i=0; i< NUMPIXELS; i++)
    strip.setPixelColor(i, 0, 255, 0);
  strip.show();
  delay(300);

  Serial.println("Blue!");
  for(i=0; i< NUMPIXELS; i++)
    strip.setPixelColor(i, 0, 0, 255);
  strip.show();
  delay(300);
}

void loop() {
  Serial.println("Rainbow!");
  rainbowCycle(10);
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< NUMPIXELS; i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

int main(void)
{
	int nMsgLen;
	
	Init();
	
	while(1){
		sprintf(sMsg, "Hello I am Geoff\r\n");
	  nMsgLen = UARTSend(sMsg);
		//nMsgLen = UARTReceive(sMsg);
	}
  
	return 0;   /* never reached */
}