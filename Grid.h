#include <Arduino.h>
#include "Adafruit_WS2801.h"

/*
 * The Grid Superclass
 * 
 */

class Grid {
  public:
	
    Grid(int total);
	
	int gridMode;
	
	void
		translate(int mode);
		setMode(int mode_id);
		
	
};


