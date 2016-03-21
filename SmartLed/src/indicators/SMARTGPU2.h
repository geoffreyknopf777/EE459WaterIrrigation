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

#ifndef SMARTGPU2_h
#define SMARTGPU2_h

//Includes of your host hardware for USART and GPIO configurations
//#include "XXXXXXX.h"

/*******************USER MODIFABLE**********************/
//-Uncomment your preferred smartGPU2 board(only 1 at time)----------------
//#define LCD160X128   //SmartGPU2 1.8"
//#define LCD320X240   //SmartGPU2 2.4"
//#define LCD480X320   //SmartGPU2 3.5"
//#define LCD480X272   //SmartGPU2 4.3"
//#define LCD800X480   //SmartGPU2 7.0"

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
/****************END OF USER MODIFABLE******************/




/*************DON'T MODIFY DOWN FROM HERE***************/
#ifdef  LCD160X128          //defines for SmartGPU2 LCD160x128 1.8" ONLY
#define LCD_WIDTH  160
#define LCD_HEIGHT 128
#elif defined  LCD320X240   //defines for SmartGPU2 LCD320x240 2.4" ONLY
#define LCD_WIDTH  320
#define LCD_HEIGHT 240
#elif defined  LCD480X320   //defines for SmartGPU2 LCD480x320 3.5" ONLY
#define LCD_WIDTH  480
#define LCD_HEIGHT 320
#elif defined  LCD480X272   //defines for SmartGPU2 LCD480x272 4.3" ONLY
#define LCD_WIDTH  480
#define LCD_HEIGHT 272
#elif defined  LCD800X480   //defines for SmartGPU2 LCD800x480 7.0" ONLY
#define LCD_WIDTH  800
#define LCD_HEIGHT 480
#else
#error "No <smartGPU2 LCDXXXxXXX> board defined in SMARTGPU2.h file, please uncomment your smartGPU2 board!!!"
#endif

//Max X, Y values depending on orientation definitions
#define MAX_X_LANDSCAPE LCD_WIDTH-1
#define MAX_Y_LANDSCAPE LCD_HEIGHT-1
#define MAX_X_PORTRAIT  LCD_HEIGHT-1
#define MAX_Y_PORTRAIT  LCD_WIDTH-1

//General definitions
#define OFF 0
#define ON  1
#define GND 0
#define VCC 1
#define SCROLLBUTTONSIZE 25
typedef unsigned int AXIS;
typedef unsigned int COLOUR;
typedef unsigned int RADIUS;
typedef unsigned int NUMBEROFBYTES;
typedef unsigned int ITEMNUMBER;
typedef unsigned int ADDRESS;
typedef unsigned long POINTERPOSITION;
typedef char FILENAME[];

typedef enum {
	DIS, //0
	EN   //1
} STATE; //to set Enable/Disable States

typedef enum {
	DESELECTED, //0
	SELECTED    //1
} ACTIVE; //to set Selected/DeSelected Active objects

typedef enum {
	DESELECTEDTRANS, //0 set an unselected top window with transparent center
	SELECTEDTRANS,   //1 set a selected window with transparent center
	SELECTEDGRAY,    //2 set a selected window with gray center
	SELECTEDWHITE    //3 set a selected window with white center
} WINDOWTYPE; //to set type of window to draw

typedef struct {
	AXIS x; //X axis
	AXIS y; //Y axis
} POINT;    //to create a point with point.x and point.y variables

typedef enum {
	OK   = 'O',  //Command successfully executed
	FAIL = 'F'   //Command Fail
} SMARTGPUREPLY; //to get SmartGPU2 command responses

//Graphics functions definitions
typedef enum {
	UNFILL, //0
	FILL    //1
} FILLGEOM;  //to set fill or unfill colour geometry

typedef enum {
	HORIZONTAL, //0
	VERTICAL    //1
} ORIENTATIONPARAMETER;//to set gradient colour fade orientation and objects: scrollBar and Slider orientations

typedef enum {
	LANDSCAPE_LEFT,     //0 left
	PORTRAIT_LOW,       //1 low
	LANDSCAPE_RIGHT,    //2 right
	PORTRAIT_TOP        //3 top
} LCDORIENTATIONS;  //to set LCD orientations

typedef enum {
	QUADRANT1 = 1, //1
	QUADRANT2,     //2
	QUADRANT3,     //3
	QUADRANT4      //4
} ARCQUADRANT;     //to set desired arc drawing quadrant

//basic colours definitions
#define BLACK   0x0000
#define WHITE   0xFFFF
#define RED     0xF800
#define GREEN   0x07E0
#define BLUE    0x001F
#define YELLOW  0xFFE0
#define CYAN    0x07FF
#define MAGENTA 0xF81F

//fonts definitions
typedef enum {
	FONT0 = 0,
	FONT1,
	FONT2,
	FONT3,
	FONT4,
	FONT5,
	FONT6,
	FONT7,
	FONT8,
	FONT9,
	FONT10,
	FONT11,
	FONT12,
	FONT13
} FONTSIZE; //to set text font sizes

typedef enum {
	TRANS = 0,
	FILLED
} TEXTBACKGROUNDCOLOURFILLUNFILL; //to set text background colour to transparent or filled

//Video 
typedef struct {
	unsigned int width;  //X width
	unsigned int height; //Y height
	unsigned int framesPerSec; //video frames per second
	unsigned int totalFrames;  //video total frames in the file
} VIDDATA;    //to create a Video Data struct containing, size X, size Y, frames per second and totalframes info

//Touch definitions
typedef enum {
	INVALID,  //returned touch point is invalid
	VALID     //returned touch point is valid
} TOUCHREPLY; //to get SmartGPU2 touch responses

typedef enum {
	HOUSE    = 'H',
	MESSAGE  = 'M',
	BOOK     = 'B',
	PHONE    = 'P',
	SONG     = 'S',
	NONE     = 'N'
} ICON;  //to get the type of touched icon

//File access definitions
#define BEGINNING    0
#define ALLCONTENTS  0
typedef enum {
	READONLY = 1, //1
	WRITEONLY,    //2
	READWRITE     //3
} OPENMODE;       //to set the file access open mode

//SMARTGPU2 Command Execution responses definitions
typedef enum {
	F_OK = 0,				/* (0) Succeeded */
	F_DISK_ERR,				/* (1) A hard error occurred in the low level disk I/O layer */
	F_INT_ERR,				/* (2) Assertion failed */
	F_NOT_READY,			/* (3) The physical drive cannot work */
	F_NO_FILE,				/* (4) Could not find the file */
	F_NO_PATH,				/* (5) Could not find the path */
	F_INVALID_NAME,			/* (6) The path name format is invalid */
	F_DENIED,				/* (7) Access denied due to prohibited access or directory full */
	F_EXIST,				/* (8) Access denied due to prohibited access */
	F_INVALID_OBJECT,		/* (9) The file/directory object is invalid */
	F_WRITE_PROTECTED,		/* (10) The physical drive is write protected */
	F_INVALID_DRIVE,		/* (11) The logical drive number is invalid */
	F_NOT_ENABLED,			/* (12) The volume has no work area */
	F_NO_FILESYSTEM,		/* (13) There is no valid FAT volume */
	F_MKFS_ABORTED,			/* (14) The f_mkfs() aborted due to any parameter error */
	F_TIMEOUT,				/* (15) Could not get a grant to access the volume within defined period */
	F_LOCKED,				/* (16) The operation is rejected according to the file sharing policy */
	F_NOT_ENOUGH_CORE,		/* (17) LFN working buffer could not be allocated */
	F_TOO_MANY_OPEN_FILES,	/* (18) Number of open files > _FS_SHARE */
	F_INVALID_PARAMETER		/* (19) Given parameter is invalid */
} FILERESULT;               //Gets all FAT functions related responses

//SMARTGPU2 WorkSpaces definitions
typedef enum {
	WORKSPACE0 = 0, 
	WORKSPACE1,
	WORKSPACE2,
	WORKSPACE3 
} WORKSPACEBLOCK;  //to set the working workspace

//SMARTGPU2 EEPROM pages definitions, each page is 2048bytes (2Kb) in size
typedef enum {
	PAGE0 = 0, 
	PAGE1,
	PAGE2,
	PAGE3,
	PAGE4,
	PAGE5,
	PAGE6,
	PAGE7
} EEPROMPAGE;  //to set the EEPROM page

//Files Time and Date
typedef struct {
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
	unsigned char day;
	unsigned char month;
	unsigned int  year;	
} TIME;    //to create a Time-Date info struct

//JPG images scale factor definitions
typedef enum {
	SCALE1_1 = 0,  // 1 to 1
	SCALE1_2,      // 1 to 2
	SCALE1_4,      // 1 to 4
	SCALE1_8       // 1 to 8
} JPGSCALEFACTOR; //to set the desired JPG image decompression scale factor

//Recommended(but not limited to) Host-SmartGPU Baud rate definitions
typedef enum{
	BAUD0 = 9600,
	BAUD1 = 19200,
	BAUD2 = 57600,
	BAUD3 = 115200,
	BAUD4 = 256000,
	BAUD5 = 500000,
	BAUD6 = 1000000,
	BAUD7 = 2000000
} BAUDRATE;


/***************************************************************************/
/***************************************************************************/
/***************************************************************************/
/************************SMARTGPU2 FUNCTIONS!!!!****************************/
/***************************************************************************/
/***************************************************************************/
/***************************************************************************/
//Call those 2 next commands before calling any Master,Geometric,String,etc.functions of smartGPU2
//NOTE: Prior to call reset_SG2() and start_SG2(), host USART and reset GPIO pin must be already configured and running
	SMARTGPUREPLY reset_SG2(void); //Physically Reset the SMARTGPU2 board
	
	SMARTGPUREPLY start_SG2(void); //starts the SMARTGPU2 

/****************************************************************/
//Master Functions
/****************************************************************/	
	SMARTGPUREPLY erase_SG2(void);  //Erase the SMARTGPU2 screen with the previously set background colour

	SMARTGPUREPLY sleep_SG2(STATE); //Sets SMARTGPU2 sleep mode
	
	SMARTGPUREPLY orientation_SG2(LCDORIENTATIONS); //Changes display orientation
	
	SMARTGPUREPLY bright_SG2(unsigned char); //Changes display brightness
	
	SMARTGPUREPLY baudChange_SG2(unsigned long); //Changes baud rate of Host and SMARTGPU2 board
		
	SMARTGPUREPLY setEraseBackColour_SG2(COLOUR); //Changes the default background colour for the erase function
	
/****************************************************************/
//Geometric Functions
/****************************************************************/		
	SMARTGPUREPLY putPixel_SG2(AXIS, AXIS, COLOUR); //Draws a pixel on the screen
	
	SMARTGPUREPLY drawLine_SG2(AXIS, AXIS, AXIS, AXIS, COLOUR); //Draws a line on the screen
	
	SMARTGPUREPLY drawRectangle_SG2(AXIS, AXIS, AXIS, AXIS, COLOUR, FILLGEOM); //Draws a rectangle on the screen

	SMARTGPUREPLY drawRoundRect_SG2(AXIS, AXIS, AXIS, AXIS, RADIUS, COLOUR, FILLGEOM); //Draws a rounded rectangle on the screen
	
	SMARTGPUREPLY drawGradientRect_SG2(AXIS, AXIS, AXIS, AXIS, COLOUR, COLOUR, ORIENTATIONPARAMETER); //Draws a gradient rectangle on the screen
	
	SMARTGPUREPLY drawTriangle_SG2(AXIS, AXIS, AXIS, AXIS, AXIS, AXIS, COLOUR, FILLGEOM); //Draws a triangle on the screen
	
	SMARTGPUREPLY drawArc_SG2(AXIS, AXIS, RADIUS, RADIUS, ARCQUADRANT, COLOUR, FILLGEOM); //Draws an Arc on the screen
	
	SMARTGPUREPLY drawCircle_SG2(AXIS, AXIS, RADIUS, COLOUR, FILLGEOM); //Draws a circle on the screen
	
	SMARTGPUREPLY drawEllipse_SG2(AXIS, AXIS, RADIUS, RADIUS, COLOUR, FILLGEOM); //Draws an Ellipse on the screen		
	
/****************************************************************/
//String Functions
/****************************************************************/		
	SMARTGPUREPLY putLetter_SG2(AXIS, AXIS, char, AXIS*); //Draws a letter on the screen on X,Y coords, returns updated value of X axis in xUpdated variable
	
	SMARTGPUREPLY printNumber_SG2(AXIS, AXIS, float); //Prints a float number on screen
	
	SMARTGPUREPLY string_SG2(AXIS, AXIS, AXIS, AXIS, char[], NUMBEROFBYTES*); //Draws a string on the screen on defined Text Box coords, and stores the successfully printed bytes on SPB
	
	SMARTGPUREPLY stringSD_SG2(AXIS, AXIS, AXIS, AXIS, NUMBEROFBYTES, NUMBEROFBYTES, FILENAME, NUMBEROFBYTES*); //Draws a String from a text file stored on the micro SD card
	
	SMARTGPUREPLY setTextColour_SG2(COLOUR); //Sets the default text colour for text and numbers
	
	SMARTGPUREPLY setTextBackColour_SG2(COLOUR); //Sets the default text background colour for text and strings

	SMARTGPUREPLY setTextSize_SG2(FONTSIZE); //Sets the default text size for text and strings

	SMARTGPUREPLY setTextBackFill_SG2(TEXTBACKGROUNDCOLOURFILLUNFILL); //Sets the default text FILL or UNFILL background for text and strings
	
/****************************************************************/
//Image Functions
/****************************************************************/		
	SMARTGPUREPLY drawIcon_SG2(AXIS, AXIS, AXIS, AXIS, const int[]); //Sends an image or icon pixel by pixel to SMARTGPU2, 16bit(2 bytes) each pixel RGB565
	
	SMARTGPUREPLY imageBMPSD_SG2(AXIS, AXIS, FILENAME); //Draws a BMP Image stored on the micro SD card on the screen, at X,Y top right corner coordinates
	
	SMARTGPUREPLY imageJPGSD_SG2(AXIS, AXIS, JPGSCALEFACTOR, FILENAME);	//Draws a JPG Image stored on the micro SD card on the screen, at X,Y top right corner coordinates and given scale factor

	SMARTGPUREPLY getImageFromMemory_SG2(AXIS, AXIS, AXIS, AXIS, char[]); //Reads the internal memory of the SMARTGPU2, This command returns 24bit pixels (3 bytes)

	SMARTGPUREPLY screenshot_SG2(void); //Takes a screenshot of SmartGPU2 display and stores it in the microSD card with consecutive names Screenshot000.bmp, Screenshot001.bmp, etc.
	
/****************************************************************/
//Video Functions
/****************************************************************/			
	SMARTGPUREPLY allocateVideoSD_SG2(FILENAME, VIDDATA*); //Allocates a ".vid" video stored on the micro SD card with the given FILENAME name

	SMARTGPUREPLY freeVideoSD_SG2(void); //DeAllocates a ".vid" video previously allocated, must be called when no more calls to video will be done
	
	SMARTGPUREPLY setFrameVideoSD_SG2(unsigned int); //Sets a video start Frame position, this function can be used to FastForward video or Rewing, returns 'F' if invalid position
	
	SMARTGPUREPLY playVideoSD_SG2(AXIS, AXIS, unsigned int); //Plays a previously allocated ".vid" video stored on mSD card on X,Y top right corner coordinates, starting from current Video Frame and plays framesToPlay	
	
/****************************************************************/
//Audio Functions
/****************************************************************/		
	SMARTGPUREPLY initDACAudio_SG2(STATE); //Initializes the DAC of SmartGPU2 for audio support

	SMARTGPUREPLY audioBoost_SG2(STATE); //Turns ON/OFF the Audio Boost - internal audio amplifier

	SMARTGPUREPLY getWAVPlayState_SG2(STATE*); //returns EN or DIS if any file is playing

	SMARTGPUREPLY playWAVFile_SG2(FILENAME, unsigned int*); //Gets in "seconds"(int*) variable the song duration in seconds

	SMARTGPUREPLY pauseWAVFile_SG2(void); //Pauses a playing file, returns 'F' if no file is playing

	SMARTGPUREPLY stopWAVFile_SG2(void); //Stops a playing file, returns 'F' if no file is playing

	SMARTGPUREPLY advanceWAVFile_SG2(unsigned int); //Advances the file to the given "seconds"(unsigned int) parameter

	SMARTGPUREPLY setVolumeWAV_SG2(unsigned char); //Sets the new volume with the "volume"(unsigned int) parameter 0-100
	
/****************************************************************/
//Real Time Clock Functions
/****************************************************************/			
	SMARTGPUREPLY setupRTC_SG2(STATE*); //Initializes the Real Time Clock, returns EN or DIS in "state"(STATE*) variable
	
	SMARTGPUREPLY getRTCTimeDate_SG2(TIME*); //Gets the current date and time in "timeDate"(TIME*) variable
	
	SMARTGPUREPLY setRTCTimeDate_SG2(TIME*); //Sets the current date and time with "timeDate"(TIME*) variable

/****************************************************************/
//Objects Functions - Refer to "smartGPU2 Command Set" to learn about minimum width and height objects size.
/****************************************************************/			
	SMARTGPUREPLY objButton_SG2(AXIS, AXIS, AXIS, AXIS, ACTIVE, char[]); //Draws a Button Object in the screen

	SMARTGPUREPLY objSwitch_SG2(AXIS, AXIS, unsigned int, ACTIVE); //Draws a Switch Object in the screen
	
	SMARTGPUREPLY objCheckbox_SG2(AXIS, AXIS, unsigned int, ACTIVE); //Draws a Checkbox Object in the screen

	SMARTGPUREPLY objProgressBar_SG2(AXIS, AXIS, AXIS, AXIS, unsigned char); //Draws a Progress Bar Object in the screen

	SMARTGPUREPLY objSlider_SG2(AXIS, AXIS, AXIS, AXIS, unsigned char, unsigned char, ORIENTATIONPARAMETER); //Draws a Slider Object in the screen

	SMARTGPUREPLY objScrollBar_SG2(AXIS, AXIS, AXIS, AXIS, unsigned char, unsigned char, ORIENTATIONPARAMETER, ACTIVE); //Draws a Scroll Bar Object in the screen

	SMARTGPUREPLY objWindow_SG2(AXIS, AXIS, AXIS, AXIS, FONTSIZE, WINDOWTYPE, char[]);

/****************************************************************/
//EEPROM-FLASH Functions - Refer to "smartGPU2 Command Set" to learn about READ-WRITE procedure, and page SIZE.
/****************************************************************/			
	SMARTGPUREPLY initClearEEPROMBuff_SG2(void); //Clears the EEPROM RAM buffer

	SMARTGPUREPLY readEEPROMBuff_SG2(char[], ADDRESS, NUMBEROFBYTES, NUMBEROFBYTES*); //Reads the EEPROM RAM buffer

	SMARTGPUREPLY writeEEPROMBuff_SG2(char[], ADDRESS, NUMBEROFBYTES, NUMBEROFBYTES*); //Writes to the EEPROM RAM buffer

	SMARTGPUREPLY saveBuffToEEPROMPage_SG2(EEPROMPAGE); //Writes to the EEPROM PAGE the contents of the EEPROM RAM buffer

	SMARTGPUREPLY fillBuffFromEEPROMPage_SG2(EEPROMPAGE); //Fills the EEPROM RAM buffer with the contents of an EEPROM PAGE

	SMARTGPUREPLY compBuffToEEPROMPage_SG2(EEPROMPAGE, unsigned char*); //Compares all the EEPROM buffer contents with the EEPROM PAGE contents
	
	SMARTGPUREPLY eraseEEPROMPage_SG2(EEPROMPAGE); //Erases the EEPROM PAGE
	
/****************************************************************/
//Touch Functions
//Those next Touch Functions return valid or invalid touch coordinates status(TOUCHREPLY) instead of ACK 'O' or NAK 'F'(SMARTGPUREPLY)
/****************************************************************/	
	TOUCHREPLY touchScreen_SG2(POINT*); //Ask for a touch on the screen, if return==VALID, touch coords are valid and stored on POINT
#ifdef  LCD320X240 //define function only for the SmartGPU2 LCD320x240 2.4" is selected, as it is the only board with touch icons
	TOUCHREPLY touchIcon_SG2(ICON*); //Ask for a touch on the icons, if return==VALID, touch icon is valid and stored on ICON
#endif
	
/****************************************************************/
//SD FAT management Functions
//Those next SDF - SD Functions return file execution status(FILERESULT) instead of ACK 'O' or NAK 'F'(SMARTGPUREPLY)
/****************************************************************/
	FILERESULT SDFgetList_SG2(unsigned int*, unsigned int*); //Gets number of dirs and files

	FILERESULT SDFgetDirName_SG2(ITEMNUMBER, FILENAME); //Searches for the "itemNumber" on the SD current folder and updates the buffer with the Dir name ended with NULL character

	FILERESULT SDFgetFileName_SG2(ITEMNUMBER, FILENAME); //Searches for the "itemNumber" on the SD current folder and updates the buffer with the File name ended with NULL character

	FILERESULT SDFgetDirPath_SG2(char[]); //Obtains current dir path and stores on path[] buffer

	FILERESULT SDFnewDir_SG2(FILENAME); //Creates a new Directory, fails if already exist

	FILERESULT SDFnewFile_SG2(FILENAME); //Creates a new File, fails if already exist
	
	FILERESULT SDFopenDir_SG2(FILENAME); //Opens an existing Dir

	FILERESULT SDFopenFile_SG2(FILENAME, OPENMODE, WORKSPACEBLOCK); //Opens an existing file in READONLY, WRITEONLY or READWRITE mode on the received object # workspace

	FILERESULT SDFcloseFile_SG2(WORKSPACEBLOCK); //Closes and save file object # workspace
 
	FILERESULT SDFsaveFile_SG2(WORKSPACEBLOCK); //Sync/save file object # workspace

	FILERESULT SDFsetFilePtr_SG2(POINTERPOSITION, WORKSPACEBLOCK); //Set/move file pointer of file object # workspace

	FILERESULT SDFgetFilePtr_SG2(POINTERPOSITION*, WORKSPACEBLOCK); //Get file pointer of file object # workspace

	FILERESULT SDFreadFile_SG2(char[], NUMBEROFBYTES, NUMBEROFBYTES*, WORKSPACEBLOCK); //Reads data from a selected file objectWorkspace

	FILERESULT SDFwriteFile_SG2(char[], NUMBEROFBYTES,NUMBEROFBYTES*,  WORKSPACEBLOCK); //Writes data to a selected file objectWorkspace

	FILERESULT SDFtestFileError_SG2(WORKSPACEBLOCK);  //Test for an error on file # workspace

	FILERESULT SDFtestFileEnd_SG2(WORKSPACEBLOCK);  //Test for an error on file # workspace

	FILERESULT SDFtruncateFile_SG2(WORKSPACEBLOCK);  //Truncates the file size to the current file read/write pointer of the file # workspace

	FILERESULT SDFeraseDirFile_SG2(FILENAME); //Erases an existing Dir or File

	FILERESULT SDFsetFileTimeDate_SG2(TIME*, FILENAME); //Set Time and Date to an existing File

	FILERESULT SDFgetFileTimeDate_SG2(TIME*, FILENAME); //Get Time and Date to an existing File

	FILERESULT SDFgetFileSize_SG2(FILENAME, unsigned long *); //Get Size of an existing File

	FILERESULT SDFrenameMoveDirFile_SG2(FILENAME, FILENAME); //Renames or moves an existing Dir or File

	FILERESULT SDFgetFreeTotalSpace_SG2(unsigned long *,unsigned long *); //Get free and total space in bytes of the microSD card

#endif
