#include <TimerOne.h>
#include "LPD6803.h"

// Choose which 2 pins you will use for output.
// Can be any valid output pins.
int dataPin = 2;       // 'yellow' wire
int clockPin = 3;      // 'green' wire
// Don't forget to connect 'blue' to ground and 'red' to +5V

LPD6803 strip = LPD6803(25, dataPin, clockPin);
int static ANA0 = 0;		//Method choosing pot
int static ANA0MAX = 9;
int static ANA1 = 1;		//Something I haven't decided pot
int static ANA1MAX = 95;
int static ANA2 = 2;		//Foreground color choosing pot
int static ANA2MAX = 95;
int static ANA3 = 3;		//Background color choosing pot
int static ANA3MAX = 95;
int static numPixel = strip.numPixels();	//Set this static so we don't have to go get it ever again


void setup() {
	Serial.begin(9600);

	// start with 50% CPU usage. up this if the strand flickers or is slow
	strip.setCPUmax(40);  

	// Start up the LED counter
	strip.begin();

	// Update the strip, to start they are all 'off'
	strip.show();
}


void loop() {
	Serial.println("Starting...");
	
	switch(getRead(ANA0, ANA0MAX))
	{
		case 0:
			Serial.println("Running 0 Color Wipe by ANA3");
				colorWipe(Wheel(getRead(ANA3, ANA3MAX)), 200);
			Serial.println(analogRead(ANA3));
			Serial.println(getRead(ANA3, ANA3MAX));
			break;
		case 1:
			Serial.println("Running 1 BACK AND FORTH");
				oneDir(100);
				revDir(100);
			break;
		case 2:
			Serial.println("Running 2 OUT TO IN");
				outToIn(100);
			break;
		case 3:
			Serial.println("Running 3 IN TO OUT");
				inToOut(100);
			break;
		case 4:
			Serial.println("Running 4");
			break;
		case 5:
			Serial.println("Running 5 Random Colors!");
				randomColorsOne(25);
			break;
		case 6:
			Serial.println("Running 6");
			break;
		case 7:
			Serial.println("Running 7");
			break;
		case 8:
			Serial.println("Running 8 PATTERN RUN MODE");
			//runPattern(50);
			break;
		case 9:
			Serial.println("Running 9 TO THE SOUND ");
			toTheSound(50);
			break;
		default:
			Serial.println("Running default SOMETHINGS WRONG");
				colorWipe(Wheel(32), 250);
			break;
			
	}
	delay(250);

	//colorWipe(Color(0, 0, 63), 50);
	//colorWipe(Color(0, 63, 0), 50);
	//colorWipe(Color(63, 63, 63), 50);
	//rainbow(50);
	//rainbowCycle(50);
	//colorWipe(Wheel(02), 1);
	//strip.show();
	//delay(255);
	//oneDir(100, 45, 60);
	//revDir(100, 02, 22);
	//outToIn(100, 02, 22);
	//inToOut(100, 40, 02);
        //int b = constrain(analogRead(0), 0, 96);
        //Serial.println(b);
        //int c = map(analogRead(0), 0, 1023, 0, 96);
        //colorWipe(Wheel(c), 50);
        //Serial.println(c);
        //Serial.println(analogRead(0));
	//rainbow(50);
	//rainbowCycle(25);
	//run(100);
	//Serial.println(32 >> 5);
}
// run all tests
/*
void run(uint8_t wait) 
{
	int i;
	for(i=0; i < 94; i+=5)
	{
		Serial.print("Color: ");
		Serial.println(i);
		colorWipe(Wheel(i*2), 1);
		oneDir(wait, i, i*2);
		revDir(wait, i, i*2);
		outToIn(wait, i, i*2);
		inToOut(wait, i, i*2);
		delay(wait);
	}
}
*/

void oneDir(uint8_t wait)
{
	int i;
	for(i=0; i <= numPixel; i++)
	{
		strip.setPixelColor(i, Wheel(rand() % 96));
		strip.setPixelColor(i-1, Wheel(getRead(ANA3, ANA3MAX)));
		strip.show();
		delay(wait);
	} 
}

void revDir(uint8_t wait)
{
	int i;
	for(i=numPixel; i >= 0; i--)
	{
		strip.setPixelColor(i, Wheel(rand() % 96));
		strip.setPixelColor(i+1, Wheel(getRead(ANA3, ANA3MAX)));
		strip.show();
		delay(wait);
	} 

}

void outToIn(uint8_t wait)
{
	int i;
	for(i=0; i <= (numPixel/2); i++)
	{
		strip.setPixelColor(i, Wheel(rand() % 96));
		strip.setPixelColor((numPixel - i) - 1, Wheel(rand() % 96));
		strip.setPixelColor(i - 1, Wheel(getRead(ANA3, ANA3MAX)));
		strip.setPixelColor((numPixel - i), Wheel(getRead(ANA3, ANA3MAX)));
		strip.show();
		delay(wait);
	} 

}

void inToOut(uint8_t wait)
{
	int i;
	for(i=((numPixel/2) - 1); i >= 0; i--)
	{
		strip.setPixelColor(i, Wheel(rand() % 96));
		strip.setPixelColor(((numPixel - i) - 1), Wheel(rand() % 96));
		if(i != ((numPixel/2) - 1))
		{
			strip.setPixelColor(i + 1, Wheel(getRead(ANA3, ANA3MAX)));
			strip.setPixelColor((numPixel - i - 2), Wheel(getRead(ANA3, ANA3MAX)));
		}
		strip.show();
		delay(wait);
	} 
}

//Random pixel + random color for wait
void randomColorsOne(uint8_t wait)
{
	for(int i=0; i < wait*4; i++)
	{
		strip.setPixelColor(rand() % numPixel, Wheel(rand() % 96));
		strip.show();
		delay(wait);
	}
}

/*
//run through multiple patterns
void runPattern(uint8_t wait)
{
		for(i=0; i < 94; i+=5)
	{
		Serial.print("Color: ");
		Serial.println(i);
		colorWipe(Wheel(i*2), 1);
		oneDir(wait, i, i*2);
		revDir(wait, i, i*2);
		outToIn(wait, i, i*2);
		inToOut(wait, i, i*2);
		delay(wait);
	}
}
*/

//LEDs go to the sound
void toTheSound(uint8_t wait)
{

}

void rainbow(uint8_t wait) {
	int i, j;

	for (j=0; j < 96 * 3; j++) {     // 3 cycles of all 96 colors in the wheel
		for (i=0; i < numPixel; i++) {
			strip.setPixelColor(i, Wheel( (i + j) % 96));
		}  
		strip.show();   // write all the pixels out
		delay(wait);
	}
}

// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void rainbowCycle(uint8_t wait) {
	int i, j;

	for (j=0; j < 96 * 5; j++) {     // 5 cycles of all 96 colors in the wheel
		for (i=0; i < numPixel; i++) {
			// tricky math! we use each pixel as a fraction of the full 96-color wheel
			// (thats the i / numPixel part)
			// Then add in j which makes the colors go around per pixel
			// the % 96 is to make the wheel cycle around
			strip.setPixelColor(i, Wheel( ((i * 96 / numPixel) + j) % 96) );
		}  
		strip.show();   // write all the pixels out
		delay(wait);
	}
}

// Immediately fill strip with color
void colorWipe(uint16_t c, uint8_t wait) {
	int i;

	for (i=0; i < numPixel; i++) {
		strip.setPixelColor(i, c);
	}
	strip.show();
	delay(wait);
}

/* Helper functions */

// Create a 15 bit color value from R,G,B
unsigned int Color(byte r, byte g, byte b)
{
	//Take the lowest 5 bits of each value and append them end to end
	uint16_t a;
	a = (((unsigned int)g & 0x1F )<<10 | ((unsigned int)b & 0x1F)<<5 | ((unsigned int)r & 0x1F));
	//Serial.println(a);
	return(a);
}

//Input a value 0 to 127 to get a color value.
//The colours are a transition r - g -b - back to r
unsigned int Wheel(byte WheelPos)
{

	byte r,g,b;
	switch(WheelPos >> 5)
	{
	case 0:
		r=31- WheelPos % 32;   //Red down
		g=WheelPos % 32;      // Green up
		
		b=0;                  //blue off
		break; 
	case 1:
		g=31- WheelPos % 32;  //green down
		b=WheelPos % 32;      //blue up
		r=0;                  //red off
		break; 
	case 2:
		b=31- WheelPos % 32;  //blue down 
		r=WheelPos % 32;      //red up
		g=0;                  //green off
		break; 
	}
	return(Color(r,g,b));
}

//Input the analog you want to read and the max amount
//Will return value between 0 and max
int getRead(int ana, int max)
{
	return map(analogRead(ana), 0, 1023, 0, max); 
}
