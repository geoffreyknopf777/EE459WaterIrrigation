/*********************************************************
VIZIC TECHNOLOGIES. COPYRIGHT 2014.
THE DATASHEETS, SOFTWARE AND LIBRARIES ARE PROVIDED "AS IS." 
VIZIC EXPRESSLY DISCLAIM ANY WARRANTY OF ANY KIND, WHETHER 
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
OR NONINFRINGEMENT. IN NO EVENT SHALL VIZIC BE LIABLE FOR 
ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, 
LOST PROFITS OR LOST DATA, HARM TO YOUR EQUIPMENT, COST OF 
PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, 
ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO 
ANY DEFENCE THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION,
OR OTHER SIMILAR COSTS.
*********************************************************/

/********************************************************
 SMARTGPU2 LIBRARY VERSION V5.0 for plain C platforms
********************************************************/

#include "SMARTGPU2.h"

/****************************************************************/
/****************************************************************/ 
/****************************************************************/
//SmartGPU2 Library exclusive Functions - DO NOT MODIFY DOWN FROM HERE
/****************************************************************/
/****************************************************************/
/****************************************************************/
SMARTGPUREPLY reset_SG2(void){ //Physically Reset the SMARTGPU2 board
	RESET_SG2_GPIO_LOW;        //Set the host pin to GND to set reset 
	DELAY_SG2(200);
	RESET_SG2_GPIO_HIGH;       //Set the host pin to VCC to end reset
	DELAY_SG2(200);	
  return OK;
}

SMARTGPUREPLY start_SG2(void){ //starts the SMARTGPU2
  PUT_CHAR_SG2('U');
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}


/****************************************************************/
//Master Functions
/****************************************************************/
SMARTGPUREPLY erase_SG2(void){       //Erase the SMARTGPU2 screen with the previously set background colour
  PUT_CHAR_SG2('M');             //Master function
  PUT_CHAR_SG2('E'); 
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}

SMARTGPUREPLY sleep_SG2(STATE state){       //Sets SMARTGPU2 sleep mode
  PUT_CHAR_SG2('M');             //Master function
  PUT_CHAR_SG2('Z'); 
  PUT_CHAR_SG2(state);
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}

SMARTGPUREPLY orientation_SG2(LCDORIENTATIONS side){       //Changes display orientation
  PUT_CHAR_SG2('M');             //Master function
  PUT_CHAR_SG2('O'); 
  PUT_CHAR_SG2(side);
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}

SMARTGPUREPLY bright_SG2(unsigned char val){       //Changes display brightness
  PUT_CHAR_SG2('M');             //Master function
  PUT_CHAR_SG2('B'); 
  PUT_CHAR_SG2(val);
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}

// SMART GPU 2 DEFAULT/INITIAL BAUD RATE: 9600bps
SMARTGPUREPLY baudChange_SG2(unsigned long baud){       //Changes baud rate of Host and SMARTGPU2 board
  unsigned char aux;

  PUT_CHAR_SG2('M');             //Master function  
  PUT_CHAR_SG2('X');
  PUT_CHAR_SG2(baud>>24);
  PUT_CHAR_SG2(baud>>16);
  PUT_CHAR_SG2(baud>>8);
  PUT_CHAR_SG2(baud);
  aux=GET_CHAR_SG2();
  if(aux=='O'){ //if command is successfull, change baudrate, if not just leave and return 'F'
	DELAY_SG2(150);
	SET_BAUDRATE(baud);
	DELAY_SG2(200);
	return (SMARTGPUREPLY)GET_CHAR_SG2();
  }else{
	return (SMARTGPUREPLY)aux;
  }
}

SMARTGPUREPLY setEraseBackColour_SG2(COLOUR colour){       //Changes the default background colour for the erase function
  PUT_CHAR_SG2('M');             //Master function
  PUT_CHAR_SG2('C');             //Background Colour
  PUT_CHAR_SG2(colour>>8);
  PUT_CHAR_SG2(colour); 
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}


/****************************************************************/
//Geometric Functions
/****************************************************************/
SMARTGPUREPLY putPixel_SG2(AXIS x, AXIS y, COLOUR colour){       //Draws a pixel on the screen
  PUT_CHAR_SG2('G');             //Geometric function 
  PUT_CHAR_SG2('P'); 
  PUT_CHAR_SG2(x>>8); 
  PUT_CHAR_SG2(x);
  PUT_CHAR_SG2(y>>8);
  PUT_CHAR_SG2(y);
  PUT_CHAR_SG2(colour>>8);
  PUT_CHAR_SG2(colour);
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}

SMARTGPUREPLY drawLine_SG2(AXIS x1, AXIS y1, AXIS x2, AXIS y2, COLOUR colour){       //Draws a line on the screen
  PUT_CHAR_SG2('G');             //Geometric function  
  PUT_CHAR_SG2('L'); 
  PUT_CHAR_SG2(x1>>8); 
  PUT_CHAR_SG2(x1);
  PUT_CHAR_SG2(y1>>8);
  PUT_CHAR_SG2(y1);
  PUT_CHAR_SG2(x2>>8); 
  PUT_CHAR_SG2(x2);
  PUT_CHAR_SG2(y2>>8);
  PUT_CHAR_SG2(y2);  
  PUT_CHAR_SG2(colour>>8);
  PUT_CHAR_SG2(colour);
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}

SMARTGPUREPLY drawRectangle_SG2(AXIS x1, AXIS y1, AXIS x2, AXIS y2, COLOUR colour, FILLGEOM fill){       //Draws a rectangle on the screen
  PUT_CHAR_SG2('G');             //Geometric function 
  PUT_CHAR_SG2('R');             //Rectangle   
  PUT_CHAR_SG2(x1>>8); 
  PUT_CHAR_SG2(x1);
  PUT_CHAR_SG2(y1>>8);
  PUT_CHAR_SG2(y1);
  PUT_CHAR_SG2(x2>>8); 
  PUT_CHAR_SG2(x2);
  PUT_CHAR_SG2(y2>>8);
  PUT_CHAR_SG2(y2);  
  PUT_CHAR_SG2(colour>>8);
  PUT_CHAR_SG2(colour);
  PUT_CHAR_SG2(fill);  
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}

SMARTGPUREPLY drawRoundRect_SG2(AXIS x1, AXIS y1, AXIS x2, AXIS y2, RADIUS radius, COLOUR colour, FILLGEOM fill){      //Draws a rounded rectangle on the screen
  PUT_CHAR_SG2('G');             //Geometric function 
  PUT_CHAR_SG2('O');             //Rounded Rectangle   
  PUT_CHAR_SG2(x1>>8); 
  PUT_CHAR_SG2(x1);
  PUT_CHAR_SG2(y1>>8);
  PUT_CHAR_SG2(y1);
  PUT_CHAR_SG2(x2>>8); 
  PUT_CHAR_SG2(x2);
  PUT_CHAR_SG2(y2>>8);
  PUT_CHAR_SG2(y2);  
  PUT_CHAR_SG2(radius>>8);
  PUT_CHAR_SG2(radius);   
  PUT_CHAR_SG2(colour>>8);
  PUT_CHAR_SG2(colour);
  PUT_CHAR_SG2(fill);  
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}
	
SMARTGPUREPLY drawGradientRect_SG2(AXIS x1, AXIS y1, AXIS x2, AXIS y2, COLOUR firstColour, COLOUR lastColour, ORIENTATIONPARAMETER direction){ //Draws a gradient rectangle on the screen
  PUT_CHAR_SG2('G');             //Geometric function 
  PUT_CHAR_SG2('G');             //Gradient rectangle function
  PUT_CHAR_SG2(x1>>8); 
  PUT_CHAR_SG2(x1);
  PUT_CHAR_SG2(y1>>8);
  PUT_CHAR_SG2(y1);
  PUT_CHAR_SG2(x2>>8); 
  PUT_CHAR_SG2(x2);
  PUT_CHAR_SG2(y2>>8);
  PUT_CHAR_SG2(y2);  
  PUT_CHAR_SG2(firstColour>>8);
  PUT_CHAR_SG2(firstColour);
  PUT_CHAR_SG2(lastColour>>8);
  PUT_CHAR_SG2(lastColour);  
  PUT_CHAR_SG2(direction);  
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}

SMARTGPUREPLY drawTriangle_SG2(AXIS x1, AXIS y1, AXIS x2, AXIS y2, AXIS x3, AXIS y3, COLOUR colour, FILLGEOM fill){       //Draws a triangle on the screen
  PUT_CHAR_SG2('G');             //Geometric function  
  PUT_CHAR_SG2('T'); 
  PUT_CHAR_SG2(x1>>8); 
  PUT_CHAR_SG2(x1);
  PUT_CHAR_SG2(y1>>8);
  PUT_CHAR_SG2(y1);
  PUT_CHAR_SG2(x2>>8); 
  PUT_CHAR_SG2(x2);
  PUT_CHAR_SG2(y2>>8);
  PUT_CHAR_SG2(y2);  
  PUT_CHAR_SG2(x3>>8); 
  PUT_CHAR_SG2(x3);
  PUT_CHAR_SG2(y3>>8);
  PUT_CHAR_SG2(y3);    
  PUT_CHAR_SG2(colour>>8);
  PUT_CHAR_SG2(colour);
  PUT_CHAR_SG2(fill);  
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}

SMARTGPUREPLY drawArc_SG2(AXIS x, AXIS y, RADIUS radiusx, RADIUS radiusy, ARCQUADRANT quadrant, COLOUR colour, FILLGEOM fill){ //Draws an Arc on the screen
  PUT_CHAR_SG2('G');             //Geometric function  
  PUT_CHAR_SG2('A');             //Arc
  PUT_CHAR_SG2(x>>8); 
  PUT_CHAR_SG2(x);
  PUT_CHAR_SG2(y>>8);
  PUT_CHAR_SG2(y);
  PUT_CHAR_SG2(radiusx>>8);
  PUT_CHAR_SG2(radiusx);
  PUT_CHAR_SG2(radiusy>>8);
  PUT_CHAR_SG2(radiusy);  
  PUT_CHAR_SG2(quadrant);
  PUT_CHAR_SG2(colour>>8);
  PUT_CHAR_SG2(colour);
  PUT_CHAR_SG2(fill);  
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}

SMARTGPUREPLY drawCircle_SG2(AXIS x, AXIS y, RADIUS radius, COLOUR colour, FILLGEOM fill){       //Draws a circle on the screen
  PUT_CHAR_SG2('G');             //Geometric function  
  PUT_CHAR_SG2('C');             //Circle 
  PUT_CHAR_SG2(x>>8); 
  PUT_CHAR_SG2(x);
  PUT_CHAR_SG2(y>>8);
  PUT_CHAR_SG2(y);
  PUT_CHAR_SG2(radius>>8);
  PUT_CHAR_SG2(radius);
  PUT_CHAR_SG2(colour>>8);
  PUT_CHAR_SG2(colour);
  PUT_CHAR_SG2(fill);  
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}

SMARTGPUREPLY drawEllipse_SG2(AXIS x, AXIS y, RADIUS radiusx, RADIUS radiusy, COLOUR colour, FILLGEOM fill){       //Draws an Ellipse on the screen
  PUT_CHAR_SG2('G');             //Geometric function 
  PUT_CHAR_SG2('E');             //Ellipse 
  PUT_CHAR_SG2(x>>8); 
  PUT_CHAR_SG2(x);
  PUT_CHAR_SG2(y>>8);
  PUT_CHAR_SG2(y);
  PUT_CHAR_SG2(radiusx>>8);
  PUT_CHAR_SG2(radiusx);
  PUT_CHAR_SG2(radiusy>>8);
  PUT_CHAR_SG2(radiusy);  
  PUT_CHAR_SG2(colour>>8);
  PUT_CHAR_SG2(colour);
  PUT_CHAR_SG2(fill);  
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}


/****************************************************************/
//String Functions
/****************************************************************/
SMARTGPUREPLY putLetter_SG2(AXIS x, AXIS y, char letter, AXIS *xUpdated){  //Draws a letter on the screen on X,Y coords, returns updated value of X axis in xUpdated variable
  unsigned int xUp = 0;          //variable to store the updated position of X axis after command is called/char is printed
  
  PUT_CHAR_SG2('S');             //String Function 
  PUT_CHAR_SG2('L');             //Letter - a simple letter
  PUT_CHAR_SG2(x>>8); 
  PUT_CHAR_SG2(x);
  PUT_CHAR_SG2(y>>8);
  PUT_CHAR_SG2(y);
  PUT_CHAR_SG2(letter); 

  ((unsigned char*)&xUp)[1]=GET_CHAR_SG2();
  ((unsigned char*)&xUp)[0]=GET_CHAR_SG2();  

  *xUpdated = xUp;
  return (SMARTGPUREPLY)GET_CHAR_SG2();  
}

SMARTGPUREPLY printNumber_SG2(AXIS x, AXIS y, float number){ //Prints a float number on screen
  PUT_CHAR_SG2('S');           //String Function 
  PUT_CHAR_SG2('N');           //Number
  PUT_CHAR_SG2(x>>8); 
  PUT_CHAR_SG2(x);
  PUT_CHAR_SG2(y>>8);
  PUT_CHAR_SG2(y);
  PUT_CHAR_SG2(((char *)&number)[3]);
  PUT_CHAR_SG2(((char *)&number)[2]);
  PUT_CHAR_SG2(((char *)&number)[1]);
  PUT_CHAR_SG2(((char *)&number)[0]);    
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}

SMARTGPUREPLY string_SG2(AXIS x1, AXIS y1, AXIS x2, AXIS y2, char text[], NUMBEROFBYTES *SPB){    //Draw a string on the screen on defined Text Box coords, and stores the successfully printed bytes on SPB
  unsigned int counter=0, sp=0; 
  
  PUT_CHAR_SG2('S');             //String Function 
  PUT_CHAR_SG2('S');             //String 
  PUT_CHAR_SG2(x1>>8); 
  PUT_CHAR_SG2(x1);
  PUT_CHAR_SG2(y1>>8);
  PUT_CHAR_SG2(y1);
  PUT_CHAR_SG2(x2>>8); 
  PUT_CHAR_SG2(x2);
  PUT_CHAR_SG2(y2>>8);
  PUT_CHAR_SG2(y2);   
  while(1){
	PUT_CHAR_SG2(text[counter]);
    if(text[counter]==0x00){
      break;
	}	
	counter++;
  }  

  ((unsigned char*)&sp)[1]=GET_CHAR_SG2();
  ((unsigned char*)&sp)[0]=GET_CHAR_SG2();

  *SPB = sp;
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}

SMARTGPUREPLY stringSD_SG2(AXIS x1, AXIS y1, AXIS x2, AXIS y2, NUMBEROFBYTES BS, NUMBEROFBYTES BR, FILENAME name, NUMBEROFBYTES *SPB){       //Draws a String from a text file stored on the micro SD card
  unsigned int counter=0, sp=0;
  
  PUT_CHAR_SG2('S');             //String function 
  PUT_CHAR_SG2('F');             //text File from SD 
  PUT_CHAR_SG2(x1>>8); 
  PUT_CHAR_SG2(x1);
  PUT_CHAR_SG2(y1>>8);
  PUT_CHAR_SG2(y1);
  PUT_CHAR_SG2(x2>>8); 
  PUT_CHAR_SG2(x2);
  PUT_CHAR_SG2(y2>>8);
  PUT_CHAR_SG2(y2);  
  PUT_CHAR_SG2(BS>>8);
  PUT_CHAR_SG2(BS);  
  PUT_CHAR_SG2(BR>>8);
  PUT_CHAR_SG2(BR);  
  while(1){
	PUT_CHAR_SG2(name[counter]);
    if(name[counter]==0x00){
      break;
	}	
	counter++;
  }

  ((unsigned char*)&sp)[1]=GET_CHAR_SG2();
  ((unsigned char*)&sp)[0]=GET_CHAR_SG2();

  *SPB = sp; 
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}

SMARTGPUREPLY setTextColour_SG2(COLOUR colour){        //Sets the default text colour for text and numbers
  PUT_CHAR_SG2('S');             //String Function 
  PUT_CHAR_SG2('C');             //Config  
  PUT_CHAR_SG2('T');             //Text
  PUT_CHAR_SG2(colour>>8);
  PUT_CHAR_SG2(colour); 
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}

SMARTGPUREPLY setTextBackColour_SG2(COLOUR colour){    //Sets the default text background colour for text and strings
  PUT_CHAR_SG2('S');             //String Function 
  PUT_CHAR_SG2('C');             //Config  
  PUT_CHAR_SG2('B');             //Background
  PUT_CHAR_SG2(colour>>8);
  PUT_CHAR_SG2(colour); 
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}

SMARTGPUREPLY setTextSize_SG2(FONTSIZE size){           //Sets the default text size for text and strings
  PUT_CHAR_SG2('S');             //String Function 
  PUT_CHAR_SG2('C');             //Config  
  PUT_CHAR_SG2('S');             //Size
  PUT_CHAR_SG2(size); 
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}

SMARTGPUREPLY setTextBackFill_SG2(TEXTBACKGROUNDCOLOURFILLUNFILL fillState){  //Sets the default text FILL or UNFILL background for text and strings
  PUT_CHAR_SG2('S');             //String Function 
  PUT_CHAR_SG2('C');             //Config  
  PUT_CHAR_SG2('F');             //Fill
  PUT_CHAR_SG2(fillState); 
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}


/****************************************************************/
//Image Functions
/****************************************************************/
SMARTGPUREPLY drawIcon_SG2(AXIS x1, AXIS y1, AXIS x2, AXIS y2, const int icon[]){            //Sends an image or icon pixel by pixel to SMARTGPU2, 16bit(2 bytes) each pixel RGB565
  unsigned int i,j,k=0; 
  
  PUT_CHAR_SG2('I');             //Image function 
  PUT_CHAR_SG2('I');             //Icon image received pixel by pixel
  PUT_CHAR_SG2(x1>>8); 
  PUT_CHAR_SG2(x1);
  PUT_CHAR_SG2(y1>>8);
  PUT_CHAR_SG2(y1);
  PUT_CHAR_SG2(x2>>8); 
  PUT_CHAR_SG2(x2);
  PUT_CHAR_SG2(y2>>8);
  PUT_CHAR_SG2(y2);
  //Send icon buffer pixel by pixel
  for(j=0;j<=(y2-y1);j++){
	for(i=0;i<=(x2-x1);i++){
		PUT_CHAR_SG2(icon[k]>>8); //16bit per pixel - Upper 8bits part
		PUT_CHAR_SG2(icon[k++]);  //16bit per pixel - Lower 8bits part
	}
  }
  
  return (SMARTGPUREPLY)GET_CHAR_SG2();  
}

SMARTGPUREPLY imageBMPSD_SG2(AXIS x, AXIS y, FILENAME name){        //Draws a BMP Image stored on the micro SD card on the screen, at X,Y top right corner coordinates
  unsigned char counter=0;
  
  PUT_CHAR_SG2('I');             //Image function 
  PUT_CHAR_SG2('B');             //BMP from SD card
  PUT_CHAR_SG2(x>>8); 
  PUT_CHAR_SG2(x);
  PUT_CHAR_SG2(y>>8);
  PUT_CHAR_SG2(y);
  while(1){
	PUT_CHAR_SG2(name[counter]);
    if(name[counter]==0x00){
      break;
	}	
	counter++;
  }
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}

SMARTGPUREPLY imageJPGSD_SG2(AXIS x, AXIS y, JPGSCALEFACTOR scaleFactor, FILENAME name){        //Draws a JPG Image stored on the micro SD card on the screen, at X,Y top right corner coordinates and given scale factor
  unsigned char counter=0;
  
  PUT_CHAR_SG2('I');             //Image function 
  PUT_CHAR_SG2('J');             //JPG from SD card
  PUT_CHAR_SG2(x>>8); 
  PUT_CHAR_SG2(x);
  PUT_CHAR_SG2(y>>8);
  PUT_CHAR_SG2(y);
  PUT_CHAR_SG2(scaleFactor);
  while(1){
	PUT_CHAR_SG2(name[counter]);
    if(name[counter]==0x00){
      break;
	}	
	counter++;
  }
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}

//Reads a defined x1,x1,x2,y2 box of the SmartGPU display, and returns it pixel by pixel in RGB 888 format, 1 byte per colour, 3 bytes per pixel
SMARTGPUREPLY getImageFromMemory_SG2(AXIS x1, AXIS y1, AXIS x2, AXIS y2, char buffer[]){ //Reads the internal memory of the SMARTGPU2, This command returns 24bit pixels (3 bytes)
  unsigned int i,j,k=0;
  
  PUT_CHAR_SG2('I');             //Image function
  PUT_CHAR_SG2('M');             //from SmartGPU internal Display Memory
  PUT_CHAR_SG2(x1>>8); 
  PUT_CHAR_SG2(x1);
  PUT_CHAR_SG2(y1>>8);
  PUT_CHAR_SG2(y1);
  PUT_CHAR_SG2(x2>>8); 
  PUT_CHAR_SG2(x2);
  PUT_CHAR_SG2(y2>>8);
  PUT_CHAR_SG2(y2); 
  //receive all the pixels
  for(j=0;j<=(y2-y1);j++){
	for(i=0;i<=(x2-x1);i++){
		buffer[k++]=GET_CHAR_SG2(); //Red
		buffer[k++]=GET_CHAR_SG2(); //Green		
		buffer[k++]=GET_CHAR_SG2(); //Blue
	}	
  }
  return (SMARTGPUREPLY)GET_CHAR_SG2();  
}

SMARTGPUREPLY screenshot_SG2(void){ //Takes a screenshot of SmartGPU2 display and stores it in the microSD card with consecutive names Screenshot000.bmp, Screenshot001.bmp, etc.
  PUT_CHAR_SG2('I');             //Image function
  PUT_CHAR_SG2('S');             //Screenshot
  return (SMARTGPUREPLY)GET_CHAR_SG2();    
}


/****************************************************************/
//Video Functions
/****************************************************************/
//Allocates a ".vid" video stored on the micro SD card with the given FILENAME name
SMARTGPUREPLY allocateVideoSD_SG2(FILENAME name, VIDDATA *videoData){ 
  unsigned int wid=0, hei=0, fra=0, tot=0;
  unsigned char counter=0;
  
  PUT_CHAR_SG2('V');             //Video function   
  PUT_CHAR_SG2('A');             //Allocate
  while(1){                   //Send Video Name
	PUT_CHAR_SG2(name[counter]);
    if(name[counter]==0x00){
      break;
	}	
	counter++;
  }

  ((unsigned char *) &wid)[1]=GET_CHAR_SG2(); //get video width
  ((unsigned char *) &wid)[0]=GET_CHAR_SG2(); 
  ((unsigned char *) &hei)[1]=GET_CHAR_SG2(); //get video height
  ((unsigned char *) &hei)[0]=GET_CHAR_SG2();
  ((unsigned char *) &fra)[1]=GET_CHAR_SG2(); //get video frames per second
  ((unsigned char *) &fra)[0]=GET_CHAR_SG2();
  ((unsigned char *) &tot)[1]=GET_CHAR_SG2(); //get video total frames
  ((unsigned char *) &tot)[0]=GET_CHAR_SG2();
  videoData->width        = wid;
  videoData->height       = hei;
  videoData->framesPerSec = fra;
  videoData->totalFrames  = tot;
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}

//DeAllocates a ".vid" video previously allocated, must be called when no more calls to video will be done
SMARTGPUREPLY freeVideoSD_SG2(void){  
  PUT_CHAR_SG2('V');             //Video function   
  PUT_CHAR_SG2('D');             //DeAllocate
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}

 //Sets a video start Frame position, this function can be used to FastForward video or Rewing, returns 'F' if invalid position
SMARTGPUREPLY setFrameVideoSD_SG2(unsigned int startFrame){
  PUT_CHAR_SG2('V');             //Video function   
  PUT_CHAR_SG2('F');             //set Video Frame
  PUT_CHAR_SG2(startFrame>>8);
  PUT_CHAR_SG2(startFrame);
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}

 //Plays a previously allocated ".vid" video stored on mSD card on X,Y top right corner coordinates, starting from current Video Frame and plays framesToPlay
SMARTGPUREPLY playVideoSD_SG2(AXIS x, AXIS y, unsigned int framesToPlay){ //frames to play from current video Frame
  PUT_CHAR_SG2('V');             //Video function   
  PUT_CHAR_SG2('P');             //Play
  PUT_CHAR_SG2(x>>8); 
  PUT_CHAR_SG2(x);
  PUT_CHAR_SG2(y>>8);
  PUT_CHAR_SG2(y);
  PUT_CHAR_SG2(framesToPlay>>8);
  PUT_CHAR_SG2(framesToPlay);
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}
	

/****************************************************************/
//Audio Functions
/****************************************************************/		
SMARTGPUREPLY initDACAudio_SG2(STATE state){ //Initializes the DAC of SmartGPU2 for audio support
  PUT_CHAR_SG2('A');             //Audio Function
  PUT_CHAR_SG2('I');             //Init - Deinit DACs
  PUT_CHAR_SG2(state);           //Enable/Disable  
  return (SMARTGPUREPLY)GET_CHAR_SG2();      
}

SMARTGPUREPLY audioBoost_SG2(STATE state){ //Turns ON/OFF the Audio Boost - internal audio amplifier
  PUT_CHAR_SG2('A');             //Audio Function
  PUT_CHAR_SG2('B');             //Boost
  PUT_CHAR_SG2(state);           //Enable/Disable
  return (SMARTGPUREPLY)GET_CHAR_SG2();    
}

SMARTGPUREPLY getWAVPlayState_SG2(STATE* state){ //returns EN or DIS if any file is playing
  PUT_CHAR_SG2('A');             //Audio Function
  PUT_CHAR_SG2('G');             //Get playing File status  
  *state = (STATE)GET_CHAR_SG2();        //Get state
  return (SMARTGPUREPLY)GET_CHAR_SG2();  
}

SMARTGPUREPLY playWAVFile_SG2(FILENAME name, unsigned int* seconds){ //Gets in "seconds" variable the song duration in seconds
  unsigned int secs=0;
  unsigned char counter=0;
  
  PUT_CHAR_SG2('A');             //Audio Function
  PUT_CHAR_SG2('P');             //Play WAV file
  while(1){                      //Send file name
  	PUT_CHAR_SG2(name[counter]);
  	if(name[counter]==0x00){
  	break;
  	}	
  	counter++;
  }

  ((unsigned char *) &secs)[1]=GET_CHAR_SG2();  
  ((unsigned char *) &secs)[0]=GET_CHAR_SG2();     
  *seconds = secs;
  return (SMARTGPUREPLY)GET_CHAR_SG2();    
}

SMARTGPUREPLY pauseWAVFile_SG2(void){ //Pauses a playing file, returns 'F' if no file is playing
  PUT_CHAR_SG2('A');             //Audio Function
  PUT_CHAR_SG2('W');             //Pause file
  return (SMARTGPUREPLY)GET_CHAR_SG2();   
}

SMARTGPUREPLY stopWAVFile_SG2(void){ //Stops a playing file, returns 'F' if no file is playing
  PUT_CHAR_SG2('A');             //Audio Function
  PUT_CHAR_SG2('S');             //Stop playing file
  return (SMARTGPUREPLY)GET_CHAR_SG2();   
}

SMARTGPUREPLY advanceWAVFile_SG2(unsigned int seconds){ //Advances the file to the given "seconds" parameter
  PUT_CHAR_SG2('A');             //Audio Function
  PUT_CHAR_SG2('A');             //Advance file  
  PUT_CHAR_SG2(seconds>>8);
  PUT_CHAR_SG2(seconds);  
  return (SMARTGPUREPLY)GET_CHAR_SG2();          //returns 'F' if no file is playing or if no seconds position exists, in this case file will stop playing
}

SMARTGPUREPLY setVolumeWAV_SG2(unsigned char volume){ //Sets the new volume with the "volume" parameter 0-100
  PUT_CHAR_SG2('A');             //Audio Function
  PUT_CHAR_SG2('V');             //Volume
  PUT_CHAR_SG2(volume);
  return (SMARTGPUREPLY)GET_CHAR_SG2();  
}


/****************************************************************/
//Real Time Clock Functions
/****************************************************************/			
SMARTGPUREPLY setupRTC_SG2(STATE *state){ //Initializes the Real Time Clock, returns EN or DIS in "state" variable
  PUT_CHAR_SG2('R');              //RTC function - Real Time Clock
  PUT_CHAR_SG2('S');              //Setup RTC
  *state = (STATE)GET_CHAR_SG2();  //Get state
  return (SMARTGPUREPLY)GET_CHAR_SG2();   
}
	
SMARTGPUREPLY getRTCTimeDate_SG2(TIME *timeDate){ //Gets the current date and time in "timeDate"(TIME*) variable
  unsigned int counter=0;
  
  PUT_CHAR_SG2('R');              //RTC function - Real Time Clock
  PUT_CHAR_SG2('P');              //Parameters
  PUT_CHAR_SG2('G');              //Get
  timeDate->hour = GET_CHAR_SG2();	//hour
  timeDate->minute = GET_CHAR_SG2();	//min
  timeDate->second = GET_CHAR_SG2(); //sec
  timeDate->day = GET_CHAR_SG2();	//day
  timeDate->month = GET_CHAR_SG2();  //month
  ((unsigned char*)&counter)[1] = GET_CHAR_SG2();		 //year upper
  ((unsigned char*)&counter)[0] = GET_CHAR_SG2();		 //year lower
  timeDate->year = counter;		    //year 
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}
	
SMARTGPUREPLY setRTCTimeDate_SG2(TIME *timeDate){ //Sets the current date and time with "timeDate"(TIME*) variable
  PUT_CHAR_SG2('R');              //RTC function - Real Time Clock
  PUT_CHAR_SG2('P');              //Parameters
  PUT_CHAR_SG2('S');              //Set
  PUT_CHAR_SG2(timeDate->hour);   //hour
  PUT_CHAR_SG2(timeDate->minute); //min
  PUT_CHAR_SG2(timeDate->second); //sec
  PUT_CHAR_SG2(timeDate->day);	  //day
  PUT_CHAR_SG2(timeDate->month);  //month
  PUT_CHAR_SG2(timeDate->year>>8);//year upper
  PUT_CHAR_SG2(timeDate->year);	  //year lower	
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}
	
	
/****************************************************************/
//Objects Functions
/****************************************************************/			
SMARTGPUREPLY objButton_SG2(AXIS x1, AXIS y1, AXIS x2, AXIS y2, ACTIVE activeState, char text[]){ //Draws a Button Object in the screen
  unsigned int counter=0;
  
  PUT_CHAR_SG2('O');              //Object function
  PUT_CHAR_SG2('B');              //Button
  PUT_CHAR_SG2(x1>>8);
  PUT_CHAR_SG2(x1);  
  PUT_CHAR_SG2(y1>>8);
  PUT_CHAR_SG2(y1);  
  PUT_CHAR_SG2(x2>>8);
  PUT_CHAR_SG2(x2);  
  PUT_CHAR_SG2(y2>>8);
  PUT_CHAR_SG2(y2);
  PUT_CHAR_SG2(activeState);
  while(1){                      //Send button text
	PUT_CHAR_SG2(text[counter]);
    if(text[counter]==0x00){
      break;
	}	
	counter++;
  }    
  return (SMARTGPUREPLY)GET_CHAR_SG2();  
}

SMARTGPUREPLY objSwitch_SG2(AXIS x, AXIS y, unsigned int switchSize, ACTIVE activeState){ //Draws a Switch Object in the screen
  PUT_CHAR_SG2('O');              //Object function
  PUT_CHAR_SG2('T');              //Switch
  PUT_CHAR_SG2(x>>8);
  PUT_CHAR_SG2(x);  
  PUT_CHAR_SG2(y>>8);
  PUT_CHAR_SG2(y);  
  PUT_CHAR_SG2(switchSize>>8);
  PUT_CHAR_SG2(switchSize);  
  PUT_CHAR_SG2(activeState);
  return (SMARTGPUREPLY)GET_CHAR_SG2();
}
	
SMARTGPUREPLY objCheckbox_SG2(AXIS x, AXIS y, unsigned int checkboxSize, ACTIVE activeState){ //Draws a Checkbox Object in the screen
  PUT_CHAR_SG2('O');              //Object function
  PUT_CHAR_SG2('C');              //Checkbox
  PUT_CHAR_SG2(x>>8);
  PUT_CHAR_SG2(x);  
  PUT_CHAR_SG2(y>>8);
  PUT_CHAR_SG2(y);  
  PUT_CHAR_SG2(checkboxSize>>8);
  PUT_CHAR_SG2(checkboxSize);  
  PUT_CHAR_SG2(activeState);
  return (SMARTGPUREPLY)GET_CHAR_SG2();    
}

SMARTGPUREPLY objProgressBar_SG2(AXIS x1, AXIS y1, AXIS x2, AXIS y2, unsigned char progress){ //Draws a Progress Bar Object in the screen
  PUT_CHAR_SG2('O');              //Object function
  PUT_CHAR_SG2('P');              //Progress Bar
  PUT_CHAR_SG2(x1>>8);
  PUT_CHAR_SG2(x1);  
  PUT_CHAR_SG2(y1>>8);
  PUT_CHAR_SG2(y1);  
  PUT_CHAR_SG2(x2>>8);
  PUT_CHAR_SG2(x2);  
  PUT_CHAR_SG2(y2>>8);
  PUT_CHAR_SG2(y2);
  PUT_CHAR_SG2(progress);
  return (SMARTGPUREPLY)GET_CHAR_SG2();    
}

SMARTGPUREPLY objSlider_SG2(AXIS x1, AXIS y1, AXIS x2, AXIS y2, unsigned char position, unsigned char divisions, ORIENTATIONPARAMETER sliderOrientation){ //Draws a Slider Object in the screen
  PUT_CHAR_SG2('O');              //Object function
  PUT_CHAR_SG2('L');              //Slider
  PUT_CHAR_SG2(x1>>8);
  PUT_CHAR_SG2(x1);  
  PUT_CHAR_SG2(y1>>8);
  PUT_CHAR_SG2(y1);  
  PUT_CHAR_SG2(x2>>8);
  PUT_CHAR_SG2(x2);  
  PUT_CHAR_SG2(y2>>8);
  PUT_CHAR_SG2(y2);
  PUT_CHAR_SG2(position);
  PUT_CHAR_SG2(divisions);
  PUT_CHAR_SG2(sliderOrientation);
  return (SMARTGPUREPLY)GET_CHAR_SG2();    
}

SMARTGPUREPLY objScrollBar_SG2(AXIS x1, AXIS y1, AXIS x2, AXIS y2, unsigned char position, unsigned char divisions, ORIENTATIONPARAMETER scrollBarOrientation, ACTIVE activeState){ //Draws a Scroll Bar Object in the screen
  PUT_CHAR_SG2('O');              //Object function
  PUT_CHAR_SG2('S');              //Scroll bar
  PUT_CHAR_SG2(x1>>8);
  PUT_CHAR_SG2(x1);  
  PUT_CHAR_SG2(y1>>8);
  PUT_CHAR_SG2(y1);  
  PUT_CHAR_SG2(x2>>8);
  PUT_CHAR_SG2(x2);  
  PUT_CHAR_SG2(y2>>8);
  PUT_CHAR_SG2(y2);
  PUT_CHAR_SG2(position);
  PUT_CHAR_SG2(divisions);
  PUT_CHAR_SG2(scrollBarOrientation);
  PUT_CHAR_SG2(activeState);
  return (SMARTGPUREPLY)GET_CHAR_SG2();    
}

SMARTGPUREPLY objWindow_SG2(AXIS x1, AXIS y1, AXIS x2, AXIS y2, FONTSIZE textSize, WINDOWTYPE winType, char text[]){
  unsigned int counter=0;
  
  PUT_CHAR_SG2('O');              //Object function
  PUT_CHAR_SG2('W');              //Window
  PUT_CHAR_SG2(x1>>8);
  PUT_CHAR_SG2(x1);  
  PUT_CHAR_SG2(y1>>8);
  PUT_CHAR_SG2(y1);  
  PUT_CHAR_SG2(x2>>8);
  PUT_CHAR_SG2(x2);  
  PUT_CHAR_SG2(y2>>8);
  PUT_CHAR_SG2(y2);
  PUT_CHAR_SG2(textSize);  
  PUT_CHAR_SG2(winType);
  while(1){                      //Send button text
	PUT_CHAR_SG2(text[counter]);
    if(text[counter]==0x00){
      break;
	}	
	counter++;
  }
  return (SMARTGPUREPLY)GET_CHAR_SG2();    
}


/****************************************************************/
//EEPROM-FLASH Functions - Refer to "smartGPU2 Command Set" to learn about READ-WRITE procedure.
/****************************************************************/			
SMARTGPUREPLY initClearEEPROMBuff_SG2(void){ //Clears the EEPROM RAM buffer
  PUT_CHAR_SG2('E');              //EEPROM function
  PUT_CHAR_SG2('I');              //Init/Clear EEPROM Buffer
  return (SMARTGPUREPLY)GET_CHAR_SG2(); 
}

SMARTGPUREPLY readEEPROMBuff_SG2(char buffer[], ADDRESS EEPROMbufferAddress, NUMBEROFBYTES bytesToRead, NUMBEROFBYTES *SRB){ //Reads the EEPROM RAM buffer
  unsigned int x=0, sr=0;
  
  PUT_CHAR_SG2('E');              //EEPROM function
  PUT_CHAR_SG2('R');              //Read N bytes from EEPROM buffer to received buffer[]
  PUT_CHAR_SG2(EEPROMbufferAddress>>8); //address to start reading from EEPROM buffer
  PUT_CHAR_SG2(EEPROMbufferAddress);  
  PUT_CHAR_SG2(bytesToRead>>8);
  PUT_CHAR_SG2(bytesToRead); 
  
  for(x=0; x<bytesToRead; x++){
	buffer[x]=GET_CHAR_SG2();
  }

  ((unsigned char*)&sr)[1]=GET_CHAR_SG2();
  ((unsigned char*)&sr)[0]=GET_CHAR_SG2();

  *SRB = sr;                   //store succesfully read bytes  
   return (SMARTGPUREPLY)GET_CHAR_SG2();  
}

SMARTGPUREPLY writeEEPROMBuff_SG2(char buffer[], ADDRESS EEPROMbufferAddress, NUMBEROFBYTES bytesToWrite, NUMBEROFBYTES *SWB){ //Writes to the EEPROM RAM buffer
  unsigned int x=0, sw=0;
  
  PUT_CHAR_SG2('E');              //EEPROM function
  PUT_CHAR_SG2('W');              //Write N bytes to EEPROM buffer from received buffer[]
  PUT_CHAR_SG2(EEPROMbufferAddress>>8); //address to start writting to EEPROM buffer
  PUT_CHAR_SG2(EEPROMbufferAddress);  
  PUT_CHAR_SG2(bytesToWrite>>8);
  PUT_CHAR_SG2(bytesToWrite);    
  for(x=0; x<bytesToWrite; x++){
	PUT_CHAR_SG2(buffer[x]);
  }  

  ((unsigned char*)&sw)[1]=GET_CHAR_SG2();
  ((unsigned char*)&sw)[0]=GET_CHAR_SG2();

  *SWB = sw;                   //store succesfully written bytes
   return (SMARTGPUREPLY)GET_CHAR_SG2();    
}

SMARTGPUREPLY saveBuffToEEPROMPage_SG2(EEPROMPAGE page){ //Writes to the EEPROM PAGE the contents of the EEPROM RAM buffer
  PUT_CHAR_SG2('E');              //EEPROM function
  PUT_CHAR_SG2('S');              //Save EEPROM buffer contents to received EEPROM page#
  PUT_CHAR_SG2(page);
  return (SMARTGPUREPLY)GET_CHAR_SG2(); 
}

SMARTGPUREPLY fillBuffFromEEPROMPage_SG2(EEPROMPAGE page){ //Fills the EEPROM RAM buffer with the contents of an EEPROM PAGE
  PUT_CHAR_SG2('E');              //EEPROM function
  PUT_CHAR_SG2('F');              //Fill(copy) EEPROM buffer with received EEPROM page# contents
  PUT_CHAR_SG2(page);
  return (SMARTGPUREPLY)GET_CHAR_SG2(); 
}

SMARTGPUREPLY compBuffToEEPROMPage_SG2(EEPROMPAGE page, unsigned char *result){ //Compares all the EEPROM buffer contents with the EEPROM PAGE contents
  PUT_CHAR_SG2('E');              //EEPROM function
  PUT_CHAR_SG2('C');              //Compare EEPROM buffer contents with received EEPROM page#
  PUT_CHAR_SG2(page);
  *result = GET_CHAR_SG2();
  return (SMARTGPUREPLY)GET_CHAR_SG2(); 
}	

SMARTGPUREPLY eraseEEPROMPage_SG2(EEPROMPAGE page){ //Erases the EEPROM PAGE
  PUT_CHAR_SG2('E');              //EEPROM function
  PUT_CHAR_SG2('E');              //Erase received EEPROM page#
  PUT_CHAR_SG2(page);
  return (SMARTGPUREPLY)GET_CHAR_SG2(); 
}	

	
/****************************************************************/
//Touch Functions
//Those next Touch Functions return valid or invalid touch coordinates status(TOUCHREPLY) instead of ACK 'O' or NAK 'F'(SMARTGPUREPLY)
/****************************************************************/
TOUCHREPLY touchScreen_SG2(POINT *point){ //Ask for a touch on the screen, if return==VALID, touch coords are valid and stored on POINT
  unsigned int x=0,y=0;
  PUT_CHAR_SG2('T');             //Touch Function
  PUT_CHAR_SG2('S');             //Screen touch 
  ((unsigned char *) &x)[1]=GET_CHAR_SG2();
  ((unsigned char *) &x)[0]=GET_CHAR_SG2();
  ((unsigned char *) &y)[1]=GET_CHAR_SG2();
  ((unsigned char *) &y)[0]=GET_CHAR_SG2();
  if(GET_CHAR_SG2()=='O'){  //if touch coordinates are valid, assign values
    point->x=x;
    point->y=y;
	return (TOUCHREPLY)VALID;
  }
  return (TOUCHREPLY)INVALID;
}

#ifdef  LCD320X240 //define function only for the SmartGPU2 LCD320x240 2.4" is selected, as it is the only board with touch icons
TOUCHREPLY touchIcon_SG2(ICON *icon){ //Ask for a touch on the icons, if return==VALID, touch icon is valid and stored on ICON
  PUT_CHAR_SG2('T');             //Touch Function
  PUT_CHAR_SG2('I');             //Icons touch
  *icon = (ICON)GET_CHAR_SG2();
  if(GET_CHAR_SG2()=='O'){  //if touch coordinates are valid
	return (TOUCHREPLY)VALID;
  }
  return (TOUCHREPLY)INVALID;
}
#endif

/****************************************************************/
//SD FAT management Functions
//Those next SDF - SD Functions return file execution status(FILERESULT) instead of ACK 'O' or NAK 'F'(SMARTGPUREPLY)
/****************************************************************/
FILERESULT SDFgetList_SG2(unsigned int *numOfDirs, unsigned int *numOfFiles){ //Gets number of dirs and files
  FILERESULT res;
  unsigned int dirs=0, files=0;
    
  PUT_CHAR_SG2('F');           //File function - memory card file management
  PUT_CHAR_SG2('L');           //List/count dirs and files
  
  ((unsigned char *) &dirs)[1]= GET_CHAR_SG2();       //Get Upper part
  ((unsigned char *) &dirs)[0]= GET_CHAR_SG2();       //Get Lower part
  ((unsigned char *) &files)[1]= GET_CHAR_SG2();      //Get Upper part
  ((unsigned char *) &files)[0]= GET_CHAR_SG2();      //Get Lower part  
  *numOfDirs=dirs;  
  *numOfFiles=files;
  res = (FILERESULT)GET_CHAR_SG2(); //Get SD file execution status
  GET_CHAR_SG2();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status
}

FILERESULT SDFgetDirName_SG2(ITEMNUMBER itemNumber, FILENAME name){ //Searches for the "itemNumber" on the SD current folder and updates the buffer with the Dir name ended with NULL character
  FILERESULT  res;
  unsigned int  i=0;

  PUT_CHAR_SG2('F');           //File function - memory card file management
  PUT_CHAR_SG2('G');           //Get name of given item file number
  PUT_CHAR_SG2('D');           //Directory
  PUT_CHAR_SG2(itemNumber>>8); //Send Upper part of itemNumber
  PUT_CHAR_SG2(itemNumber);    //Send Lower part of itemNumber
  
  while(1){
	name[i]=GET_CHAR_SG2(); 
	if(name[i]==0x00){         //if we find NULL character, means end of name
		break;   
	}
	i++;
  }
  res = (FILERESULT)GET_CHAR_SG2(); //Get SD file execution status
  GET_CHAR_SG2();                   //Discard 'O' or 'F'
  return res;                    //Return SD file execution status
 }

FILERESULT SDFgetFileName_SG2(ITEMNUMBER itemNumber, FILENAME name){ //Searches for the "itemNumber" on the SD current folder and updates the buffer with the File name ended with NULL character
  FILERESULT  res;
  unsigned int  i=0;

  PUT_CHAR_SG2('F');           //File function - memory card file management
  PUT_CHAR_SG2('G');           //Get name of given item file number
  PUT_CHAR_SG2('F');           //File  
  PUT_CHAR_SG2(itemNumber>>8); //Send Upper part of itemNumber
  PUT_CHAR_SG2(itemNumber);    //Send Lower part of itemNumber

  while(1){
	name[i]=GET_CHAR_SG2(); 
	if(name[i]==0x00){         //if we find NULL character, means end of name
		break;   
	}
	i++;
  }
  res = (FILERESULT)GET_CHAR_SG2(); //Get SD file execution status
  GET_CHAR_SG2();                   //Discard 'O' or 'F'
  return res;                    //Return SD file execution status
 }
 
FILERESULT SDFgetDirPath_SG2(char path[]){ //Obtains current dir path and stores on path[] buffer
  FILERESULT  res;
  unsigned int  i=0;
  PUT_CHAR_SG2('F');           //File function - memory card file management
  PUT_CHAR_SG2('H');           //Get current Dir Path
  
  while(1){
	path[i]=GET_CHAR_SG2(); 
	if(path[i]==0x00){         //if we find NULL character, means end of path
		break;   
	}
	i++;
  }
  res = (FILERESULT)GET_CHAR_SG2(); //Get SD file execution status
  GET_CHAR_SG2();                   //Discard 'O' or 'F'
  return res;                    //Return SD file execution status
}

FILERESULT SDFnewDir_SG2(FILENAME name){ //Creates a new Directory, fails if already exist
  FILERESULT res;
  unsigned int counter=0;  
 
  PUT_CHAR_SG2('F');           //File function - memory card file management
  PUT_CHAR_SG2('N');           //New
  PUT_CHAR_SG2('D');           //Directory/Folder  
  while(1){
  	PUT_CHAR_SG2(name[counter]);
  	if(name[counter]==0x00){
  	break;
  	}	
  	counter++;
  }

  res = (FILERESULT)GET_CHAR_SG2(); //Get SD file execution status
  GET_CHAR_SG2();                   //Discard 'O' or 'F'
  return res;                    //Return SD file execution status
}

FILERESULT SDFnewFile_SG2(FILENAME name){ //Creates a new File, fails if already exist
  FILERESULT res;
  unsigned int counter=0;  
 
  PUT_CHAR_SG2('F');           //File function - memory card file management
  PUT_CHAR_SG2('N');           //New
  PUT_CHAR_SG2('F');           //File 
  while(1){
  	PUT_CHAR_SG2(name[counter]);
  	if(name[counter]==0x00){
  	break;
  	}	
  	counter++;
  }

  res = (FILERESULT)GET_CHAR_SG2(); //Get SD file execution status
  GET_CHAR_SG2();                   //Discard 'O' or 'F'
  return res;                    //Return SD file execution status
}

FILERESULT SDFopenDir_SG2(FILENAME name){ //Opens an existing Dir
  FILERESULT res;
  unsigned int counter=0;  
  
  PUT_CHAR_SG2('F');           //File function - memory card file management
  PUT_CHAR_SG2('D');           //Open Dir
  while(1){
	PUT_CHAR_SG2(name[counter]);
	if(name[counter]==0x00){
	  break;
	}	
	counter++;
  }

  res = (FILERESULT)GET_CHAR_SG2(); //Get SD file execution status
  GET_CHAR_SG2();                   //Discard 'O' or 'F'
  return res;                    //Return SD file execution status
}

FILERESULT SDFopenFile_SG2(FILENAME name, OPENMODE mode, WORKSPACEBLOCK objectWorkspaceNo){ //Opens an existing file in READONLY, WRITEONLY or READWRITE mode on the received object # workspace
  FILERESULT res;
  unsigned int counter=0;  
  
  PUT_CHAR_SG2('F');           //File function - memory card file management
  PUT_CHAR_SG2('O');           //Open file
  PUT_CHAR_SG2(objectWorkspaceNo); //object workspace number to allocate open file 0-4
  PUT_CHAR_SG2(mode);          //Mode - READONLY,WRITEONLY,READWRITE
  while(1){
	PUT_CHAR_SG2(name[counter]);
	if(name[counter]==0x00){
	  break;
	}	
	counter++;
  }

  res = (FILERESULT)GET_CHAR_SG2(); //Get SD file execution status
  GET_CHAR_SG2();                   //Discard 'O' or 'F'
  return res;                    //Return SD file execution status  
}

FILERESULT SDFcloseFile_SG2(WORKSPACEBLOCK objectWorkspaceNo){ //Closes and save file object # workspace
  FILERESULT res;

  PUT_CHAR_SG2('F');           //File function - memory card file management
  PUT_CHAR_SG2('C');           //Close File
  PUT_CHAR_SG2(objectWorkspaceNo); //object workspace number to close 0-4  

  res = (FILERESULT)GET_CHAR_SG2(); //Get SD file execution status
  GET_CHAR_SG2();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status
}

FILERESULT SDFsaveFile_SG2(WORKSPACEBLOCK objectWorkspaceNo){ //Sync/save file object # workspace
  FILERESULT res;
  
  PUT_CHAR_SG2('F');           //File function - memory card file management
  PUT_CHAR_SG2('S');           //Save/Sync file - Save changes on file
  PUT_CHAR_SG2(objectWorkspaceNo); //object workspace number to save changes 0-4  

  res = (FILERESULT)GET_CHAR_SG2(); //Get SD file execution status
  GET_CHAR_SG2();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status
}

FILERESULT SDFsetFilePtr_SG2(POINTERPOSITION pointerPosition, WORKSPACEBLOCK objectWorkspaceNo){ //Set/move file pointer of file object # workspace
  FILERESULT res;
  
  PUT_CHAR_SG2('F');           //File function - memory card file management
  PUT_CHAR_SG2('P');           //Pointer position
  PUT_CHAR_SG2(objectWorkspaceNo); //object workspace number to move pointer 0-4  
  PUT_CHAR_SG2('S');           //Set  
  PUT_CHAR_SG2(pointerPosition>>24);
  PUT_CHAR_SG2(pointerPosition>>16);
  PUT_CHAR_SG2(pointerPosition>>8);
  PUT_CHAR_SG2(pointerPosition);

  res = (FILERESULT)GET_CHAR_SG2(); //Get SD file execution status
  GET_CHAR_SG2();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status
}	

FILERESULT SDFgetFilePtr_SG2(POINTERPOSITION *pointerPosition, WORKSPACEBLOCK objectWorkspaceNo){ //Get file pointer of file object # workspace
  FILERESULT res;
  unsigned long pos = 0;
  
  PUT_CHAR_SG2('F');           //File function - memory card file management
  PUT_CHAR_SG2('P');           //Pointer position
  PUT_CHAR_SG2(objectWorkspaceNo); //object workspace number to get pointer 0-4  
  PUT_CHAR_SG2('G');           //Get
  
  ((unsigned char *) &pos)[3]=GET_CHAR_SG2();
  ((unsigned char *) &pos)[2]=GET_CHAR_SG2();
  ((unsigned char *) &pos)[1]=GET_CHAR_SG2();  
  ((unsigned char *) &pos)[0]=GET_CHAR_SG2();
  *pointerPosition =pos;
  res = (FILERESULT)GET_CHAR_SG2(); //Get SD file execution status
  GET_CHAR_SG2();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status
}	

FILERESULT SDFreadFile_SG2(char buffer[], NUMBEROFBYTES BTR, NUMBEROFBYTES *SRB, WORKSPACEBLOCK objectWorkspaceNo){ //Reads data from a selected file objectWorkspace
  FILERESULT res;
  unsigned int x=0, sr=0;

  PUT_CHAR_SG2('F');           //File function - memory card file management
  PUT_CHAR_SG2('R');           //Read file
  PUT_CHAR_SG2(objectWorkspaceNo); //object workspace number to read 0-4    
  PUT_CHAR_SG2(BTR>>8);
  PUT_CHAR_SG2(BTR);  

  for(x=0;x<BTR;x++){
	buffer[x]=GET_CHAR_SG2();
  }

  ((unsigned char*)&sr)[1]=GET_CHAR_SG2();
  ((unsigned char*)&sr)[0]=GET_CHAR_SG2();

  *SRB = sr;                   //store succesfully read bytes
  res = (FILERESULT)GET_CHAR_SG2(); //Get SD file execution status
  GET_CHAR_SG2();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status
}	

FILERESULT SDFwriteFile_SG2(char buffer[], NUMBEROFBYTES BTW, NUMBEROFBYTES *SWB,  WORKSPACEBLOCK objectWorkspaceNo){ //Writes data to a selected file objectWorkspace
  FILERESULT res;
  unsigned int x=0, sw=0;
 
  PUT_CHAR_SG2('F');           //File function - memory card file management
  PUT_CHAR_SG2('W');           //Write file
  PUT_CHAR_SG2(objectWorkspaceNo); //object workspace number to write bytes 0-4    
  PUT_CHAR_SG2(BTW>>8);
  PUT_CHAR_SG2(BTW);    
  for(x=0;x<BTW;x++){
	PUT_CHAR_SG2(buffer[x]);
  }

  ((unsigned char*)&sw)[1]=GET_CHAR_SG2();
  ((unsigned char*)&sw)[0]=GET_CHAR_SG2();

  *SWB = sw;                   //store succesfully written bytes   
  res = (FILERESULT)GET_CHAR_SG2(); //Get SD file execution status
  GET_CHAR_SG2();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status
}

FILERESULT SDFtestFileError_SG2(WORKSPACEBLOCK objectWorkspaceNo){  //Test for an error on file # workspace
  FILERESULT res;

  PUT_CHAR_SG2('F');           //File function - memory card file management
  PUT_CHAR_SG2('Q');           //Test 
  PUT_CHAR_SG2(objectWorkspaceNo); //object workspace number to write bytes 0-4    
  PUT_CHAR_SG2('R');           //Test Error  

  res = (FILERESULT)GET_CHAR_SG2(); //Get SD file execution status
  GET_CHAR_SG2();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status
}

FILERESULT SDFtestFileEnd_SG2(WORKSPACEBLOCK objectWorkspaceNo){  //Test for an error on file # workspace
  FILERESULT res;
  
  PUT_CHAR_SG2('F');           //File function - memory card file management
  PUT_CHAR_SG2('Q');           //Test 
  PUT_CHAR_SG2(objectWorkspaceNo); //object workspace number to write bytes 0-4    
  PUT_CHAR_SG2('E');           //Test End of File

  res = (FILERESULT)GET_CHAR_SG2(); //Get SD file execution status
  GET_CHAR_SG2();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status 
}

FILERESULT SDFtruncateFile_SG2(WORKSPACEBLOCK objectWorkspaceNo){  //Truncates the file size to the current file read/write pointer of the file # workspace
  FILERESULT res;
  
  PUT_CHAR_SG2('F');           //File function - memory card file management
  PUT_CHAR_SG2('V');           //Truncate
  PUT_CHAR_SG2(objectWorkspaceNo); //object workspace number 0-4 to truncate on current pointerPosition

  res = (FILERESULT)GET_CHAR_SG2(); //Get SD file execution status
  GET_CHAR_SG2();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status 
}

FILERESULT SDFeraseDirFile_SG2(FILENAME name){ //Erases an existing Dir or File
  FILERESULT res;
  unsigned int counter=0;  
  
  PUT_CHAR_SG2('F');           //File function - memory card file management
  PUT_CHAR_SG2('E');           //Erase Dir File
  PUT_CHAR_SG2('O');           //Unlock Erase Protection
  while(1){
	PUT_CHAR_SG2(name[counter]);
	if(name[counter]==0x00){
	  break;
	}	
	counter++;
  }

  res = (FILERESULT)GET_CHAR_SG2(); //Get SD file execution status
  GET_CHAR_SG2();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status
}

FILERESULT SDFsetFileTimeDate_SG2(TIME *timeDate, FILENAME name){ //Set Time and Date to an existing File
  FILERESULT res;
  unsigned int counter=0;  
  
  PUT_CHAR_SG2('F');              //File function - memory card file management
  PUT_CHAR_SG2('T');              //Time/Date
  PUT_CHAR_SG2('S');              //Set
  PUT_CHAR_SG2(timeDate->hour);   //hour
  PUT_CHAR_SG2(timeDate->minute); //min
  PUT_CHAR_SG2(timeDate->second); //sec
  PUT_CHAR_SG2(timeDate->day);	  //day
  PUT_CHAR_SG2(timeDate->month);  //month
  PUT_CHAR_SG2(timeDate->year>>8);//year upper
  PUT_CHAR_SG2(timeDate->year);	  //year lower	
  while(1){
	PUT_CHAR_SG2(name[counter]);
	if(name[counter]==0x00){
	  break;
	}	
	counter++;
  }

  res = (FILERESULT)GET_CHAR_SG2(); //Get SD file execution status
  GET_CHAR_SG2();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status 
}

FILERESULT SDFgetFileTimeDate_SG2(TIME *timeDate, FILENAME name){ //Get Time and Date to an existing File
  FILERESULT res;
  unsigned int counter=0;  
  
  PUT_CHAR_SG2('F');           //File function - memory card file management
  PUT_CHAR_SG2('T');           //Time/Date
  PUT_CHAR_SG2('G');           //Get
  while(1){
	PUT_CHAR_SG2(name[counter]);
	if(name[counter]==0x00){
	  break;
	}	
	counter++;
  }	

  timeDate->hour = GET_CHAR_SG2();   //hour
  timeDate->minute = GET_CHAR_SG2(); //min
  timeDate->second = GET_CHAR_SG2(); //sec
  timeDate->day = GET_CHAR_SG2();    //day
  timeDate->month = GET_CHAR_SG2();  //month
  ((unsigned char*)&counter)[1] = GET_CHAR_SG2();		 //year upper
  ((unsigned char*)&counter)[0] = GET_CHAR_SG2();		 //year lower
  timeDate->year = counter;		    //year
  res = (FILERESULT)GET_CHAR_SG2();  //Get SD file execution status
  GET_CHAR_SG2();                    //Discard 'O' or 'F'
  return res;                     //Return SD file execution status
}

FILERESULT SDFgetFileSize_SG2(FILENAME name, unsigned long *fileSize){ //Get Size of an existing File
  FILERESULT res;
  unsigned int counter=0;  
  unsigned long size=0;
  
	PUT_CHAR_SG2('F');           //File function - memory card file management
	PUT_CHAR_SG2('I');           //Info
	PUT_CHAR_SG2('S');           //Size
	while(1){
		PUT_CHAR_SG2(name[counter]);
		if(name[counter]==0x00){
		break;
		}	
		counter++;
	}	

  ((unsigned char *) &size)[3]=GET_CHAR_SG2();
  ((unsigned char *) &size)[2]=GET_CHAR_SG2();
  ((unsigned char *) &size)[1]=GET_CHAR_SG2();  
  ((unsigned char *) &size)[0]=GET_CHAR_SG2(); 
  *fileSize=size;
  res = (FILERESULT)GET_CHAR_SG2(); //Get SD file execution status
  GET_CHAR_SG2();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status 
}

FILERESULT SDFrenameMoveDirFile_SG2(FILENAME oldName, FILENAME newName){ //Renames or moves an existing Dir or File
  FILERESULT res;
  unsigned int counter=0;  
  
	PUT_CHAR_SG2('F');           //File function - memory card file management
	PUT_CHAR_SG2('M');           //Rename / Move
	while(1){
		PUT_CHAR_SG2(oldName[counter]);
		if(oldName[counter]==0x00){
		break;
		}	
		counter++;
	}
	counter=0;
	while(1){
		PUT_CHAR_SG2(newName[counter]);
		if(newName[counter]==0x00){
		break;
		}	
		counter++;
  }	

  res = (FILERESULT)GET_CHAR_SG2(); //Get SD file execution status
  GET_CHAR_SG2();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status 
}

FILERESULT SDFgetFreeTotalSpace_SG2(unsigned long *freeSpace,unsigned long *totalSpace){ //Get free and total space in bytes of the microSD card
  FILERESULT res;
  unsigned long fSpace=0, tSpace=0;
  
  PUT_CHAR_SG2('F');           //File function - memory card file management
  PUT_CHAR_SG2('F');           //Free/Total space

  ((unsigned char *) &fSpace)[3]=GET_CHAR_SG2();
  ((unsigned char *) &fSpace)[2]=GET_CHAR_SG2();
  ((unsigned char *) &fSpace)[1]=GET_CHAR_SG2();  
  ((unsigned char *) &fSpace)[0]=GET_CHAR_SG2(); 
  ((unsigned char *) &tSpace)[3]=GET_CHAR_SG2();
  ((unsigned char *) &tSpace)[2]=GET_CHAR_SG2();
  ((unsigned char *) &tSpace)[1]=GET_CHAR_SG2();  
  ((unsigned char *) &tSpace)[0]=GET_CHAR_SG2(); 
  *freeSpace=fSpace;
  *totalSpace=tSpace;  
  res = (FILERESULT)GET_CHAR_SG2(); //Get SD file execution status
  GET_CHAR_SG2();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status 
}
