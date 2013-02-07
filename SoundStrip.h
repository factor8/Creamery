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
	
		// Alignment Enumeration : Start From? /// This might not be the way to approach this
		enum {left,right,up,down,horizontal,vertical};			// Belongs in Controller or Pattern
		enum {strand,panel,mirrored};		// Belongs to Controller or Pattern
		
    	SoundStrip(uint16_t n, uint8_t dpin, uint8_t cpin, uint8_t order=WS2801_RGB);
		
		int pixels[];
	
		void
			colorWipe(uint32_t c, uint8_t wait),
			RainbowLevel(uint8_t wait),
			rainbowPulse(uint8_t wait),
			rainbowSpectrum(uint8_t wait),
			readSpectrum(),		
			showSpectrum(uint8_t wait),
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
			orientation;

		uint32_t 
			primary,
			secondary;
			
};


