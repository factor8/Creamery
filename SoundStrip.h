#include <Arduino.h>
#include <Creamery.h>
#include <Easing.h>

/*
 * The color wipe effect changes each pixel in turn
 * to the given color.
 */

// Defined elswhere:
// class Grid;

class SoundStrip : public Creamery {
  public:
	
		// Alignment,Direction,Pattern Enumeration
		enum {asc,desc,	horizontal,vertical,	strand,panel,mirrored};			// Belongs in Controller or Pattern
		
    	SoundStrip(uint16_t n, uint8_t dpin, uint8_t cpin, uint8_t order=WS2801_RGB);
		
		int pixels[];
	
		void
			colorWipe(uint32_t c, uint32_t d, uint8_t wait),
			
			mirror(int pos, uint32_t color),
			grid(),
			q(int pos, uint32_t color),
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
			
};


