#include <Arduino.h>
#include "Adafruit_WS2801.h"

/*
 * The Grid Superclass
 * 
 */

class Grid {
	public:
				
		Grid(Adafruit_WS2801 strip,int panelsX, int panelsY,int pixelsX,int pixelsY, int mode=left);
		
		int 
			getGridMode(),
			setGridMode(int modeid),
			getXY(int x, int y); // Returns Serial ID of XY position in grid.
	
	private:

		int 
			mode,
			panelsX,
			panelsY,
			pixelsX,
			pixelsY;
    

};