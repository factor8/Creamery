#include "SPI.h"
#include "Adafruit_WS2801.h"
#include <Easing.h>
#include "Grid.h"
#include "CTRL.h"

int dataPin  = 2;    // White wire on Adafruit Pixels
int clockPin = 3;    // Green wire on Adafruit Pixels

// Grid Vars
int panelsX = 12;
int panelsY = 1;
int pixelsX = 1;
int pixelsY = 12;
int pixelsTotal = panelsX*panelsY*pixelsX*pixelsY;

// Instantiate Controller. Num Pix Automatically Generated.
// CTRL ctrl = CTRL(pixelsTotal, dataPin, clockPin);

Adafruit_WS2801 *strip = new Adafruit_WS2801(pixelsTotal, dataPin, clockPin);
CTRL ctrl = CTRL(strip,panelsX,panelsY,pixelsX,pixelsY);

void setup() {

	Serial.begin(9600);	
  	
	// Initialize Controller and turn off LEDS.
	strip->begin();
	strip->show();
}

void loop() {	

	ctrl.render();
}
