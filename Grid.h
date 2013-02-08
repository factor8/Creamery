#include <Arduino.h>
#include "Adafruit_WS2801.h"

/*
 * The Grid Superclass
 * 
 */

class Grid {
	public:
		
		// Alignment,Direction,Pattern Enumeration
		enum {asc,desc,horizontal,vertical,strand,panel,mirrored};
				
		Grid(Adafruit_WS2801 *strip,int panelsX, int panelsY,int pixelsX,int pixelsY, int mode);
		
		int 
			mode,
			orientation,
			panelsX,
			panelsY,
			pixelsX,
			pixelsY,
			total;
			
			
		uint8_t 
			getGridMode(),			
			getTotal(),
			getXY(int x, int y); // Returns Serial ID of XY position in grid.
			
		uint32_t
			getPixelColor(uint16_t n);			
			
		void
			show(),
			q(uint16_t pos, uint32_t c),
			setGridMode(uint8_t modeid),
			setPixelColor(uint16_t pos, uint32_t c);
			
		  
	private:
		
		Adafruit_WS2801 *strip;
	 

};