#include <Arduino.h>
#include <Creamery.h>

/*
 * The color wipe effect changes each pixel in turn
 * to the given color.
 */

// Defined elswhere:
class Adafruit_WS2801;
class Grid;
class Creamery;

class CTRL {
  	public:
	
		// Alignment,Direction,Pattern Enumeration
		enum {asc,desc,	horizontal,vertical,	strand,panel,mirrored};			// Belongs in Controller or Pattern
		
		CTRL(Adafruit_WS2801 *strip,int panelsX, int panelsY,int pixelsX,int pixelsY);
    	// CTRL(uint16_t n, uint8_t dpin, uint8_t cpin, uint8_t order=WS2801_RGB);
		
		Adafruit_WS2801 *strip;
		Grid *grid;
		Creamery *creamery;
		
		char* 
			method;
		
		int 
			total,
			test,
			debug,
			selector,			
			intensity,
			frequency,
			sustain,
			density,
			division,
			panelsX,
			panelsY,
			pixelsX,
			pixelsY,
			r,g,b,a,
			index,					
			mode,	
			orientation,
			direction;
		
		
		void
			colorWipe(uint32_t c, uint32_t d, uint32_t wait),
			setSelector(uint16_t s),
			
			// Route(),
			// ReadJsonBytes(),
			// ConnectToSocket(),

			mirror(int pos, uint32_t color),
			q(int pos, uint32_t color),
			step(),
			render();

	private:
		
		// controller vars:
		long timer; 													// timer clock
		unsigned const static long pduration = 900000;		// phase duration ///MAGIC NUMBERS MUST DIE!!
		unsigned long iduration;									// interval duration
		
		unsigned long 
			interval,
			phase;

		uint32_t 
			primary,
			secondary;

		// This is for when we merge in the controller	//		
		// String 
		// 	parseMethod(aJsonObject* root);
		// uint8_t 
		// 	parseOptionNumber(aJsonObject* root, char* target);
		// char* 
		// 	parseOptionString(aJsonObject* root, char* target),
		// 	parseOptions(aJsonObject* root);
		// 	
		// int 
		// 	parseClientId(aJsonObject* root);
			
};


