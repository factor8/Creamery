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
	
		void
			colorWipe(uint32_t c, uint32_t d, uint8_t wait),

			// Route(),
			// ReadJsonBytes(),
			// ConnectToSocket(),

			mirror(int pos, uint32_t color),
			q(int pos, uint32_t color),
			step(),
			render();

	private:
		
		// controller vars:
		long timer; 													// 
		unsigned const static long pduration = 900000;		// phase duration
		unsigned const static long iduration = 30000;		// interval duration
		
		unsigned long 
			interval,
			phase;

		
		int 
			total,
			test,
			debug,
			selector,
			intensity,
			division,
			panelsX,
			panelsY,
			pixelsX,
			pixelsY,		
			mode,	
			orientation,
			direction;

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


