/* Original Code by Tom Igoe :: edited John Schimmel */

#include "TrueRandom.h"
#include <SPI.h>
#include "Adafruit_WS2801.h"
// #include <Ethernet.h>

/// This should just be #include Creamery.h
// #include "Creamery.h"
#include "CTRL.h"
#include "Grid.h"


/// MAKE #DEFINE
#define DATAPIN 2    // White wire on Adafruit Pixels
#define CLOCKPIN 3    // Green wire on Adafruit Pixels

boolean DEBUG = true;

// Grid Vars
int panelsX = 1;
int panelsY = 11;
int pixelsX = 1;
int pixelsY = 1;
int pixelsTotal = panelsX*panelsY*pixelsX*pixelsY;

// Instantiate Controller. Num Pix Automatically Generated.
Adafruit_WS2801 *strip = new Adafruit_WS2801(pixelsTotal, DATAPIN, CLOCKPIN);
CTRL ctrl = CTRL(strip,panelsX,panelsY,pixelsX,pixelsY);

int iter = 0;
long last_step = 0;
uint32_t freq = 100;

// ====

void setup() {
  	// memset(json, 0, BUFFER_SIZE); // paranoia

  Serial.begin(9600); //start serializing
	Serial.println("Setting Up");
	
	// Initialize Controller and turn off LEDS!
	/// creamery->init();
	strip->begin();
	strip->show();

	Serial.println("Ending Setup...");

}

void loop()
{
	ctrl.render();
}
