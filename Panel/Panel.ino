/* Original Code by Tom Igoe :: edited John Schimmel */

#include <SPI.h>
#include <Ethernet.h>
#include "Adafruit_WS2801.h"
#include "CTRL.h"
#include "Grid.h"
#include "TrueRandom.h"

int dataPin  = 2;    // White wire on Adafruit Pixels
int clockPin = 3;    // Green wire on Adafruit Pixels

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

//your arduino's IP address might need to change depending on your network
byte ip[] = { 
  192,168,1,9 };

// IMPORTANT
// CHANGE THE SERVER IP ADDRESS
byte server[] = {
  192,168,1,69 };

uint8_t port = 1337;

// Socket socket = Socket(mac,ip,server,port);

boolean DEBUG = true;

// Grid Vars
int panelsX = 1;
int panelsY = 1;
int pixelsX = 3;
int pixelsY = 6;
int pixelsTotal = panelsX*panelsY*pixelsX*pixelsY;

// Instantiate Controller. Num Pix Automatically Generated.
Adafruit_WS2801 *strip = new Adafruit_WS2801(pixelsTotal, dataPin, clockPin);
CTRL ctrl = CTRL(strip,panelsX,panelsY,pixelsX,pixelsY);

int iter;
uint32_t c = Color(20,20,20);
long last_step = 0;
uint32_t freq = 100;

// ====

void setup() {
  	// memset(json, 0, BUFFER_SIZE); // paranoia

  	Serial.begin(9600); //start serializing
	Serial.println("Setting Up");

	// Initialize the Socket!
	// socket.begin();
	
	// Initialize Controller and turn off LEDS!
	strip->begin();
	strip->show();

	Serial.println("Ending Setup...");
	
	iter = 0;
}

void loop()
{
	// ctrl.step();
	// We need this here too so that we can work without the connection
	
	if (testWipe(c)) {
		// Serial.println("nex	....");
		c = Color(TrueRandom.random(0,100),TrueRandom.random(0,100),TrueRandom.random(0,100));
		
	}
	// Serial.println("running....");
}


bool testWipe(uint32_t c) {
	
	// if (current_time - this->last_execution < this->frequency) {
	//     return true;
	//   }
  
	
	if (millis()>last_step+freq) {
		strip->setPixelColor(iter,c);	
		iter++;
		last_step = millis();
		strip->show();
		
		Serial.println(iter);
				
		if (iter > strip->numPixels()) {
			Serial.println("Completed");
			iter = 0;
			
			c = Color(TrueRandom.random(0,100),TrueRandom.random(0,100),TrueRandom.random(0,100));
			return true;		
		}		
	}
	return false;
}


uint32_t Color(byte r, byte g, byte b) {
	Serial.println("Color	....");
	uint32_t c;
	c = r;
	c <<= 8;
	c |= g;
	c <<= 8;  
	c |= b;
	
  	return c;
}