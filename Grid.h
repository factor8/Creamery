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
		
		void
			setupPanelQ();
		
		int 
			mode,
			orientation,
			panelsX,
			panelsY,
			pixelsX,
			pixelsY,
			total;
		
		uint16_t
			panelsq[], // for criss-cross like the Fan or a Test Panel.
			mirroredq[],
			ceilingq[];			
		
		double 
			brightness;
			
		uint8_t 
			getGridMode(),			
			getTotal(),
			getXY(int x, int y); // Returns Serial ID of XY position in grid.
			
		uint32_t
			getPixelColor(uint16_t n),
			rgba(byte r, byte g, byte b, double a),
			Color(byte r, byte g, byte b); 			
			
		void
			show(),
			q(uint16_t pos, uint32_t c),
			setBrightness(double brightness),
			setGridMode(uint8_t modeid),
			setPixelColor(uint16_t pos, uint32_t c);
			
		  
	private:
		
		Adafruit_WS2801 *strip;
	 

};