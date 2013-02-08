#include <Arduino.h>
#include <Adafruit_WS2801.h>

/*
 * Creamery.
 * Eventually this will be just the Effects class.
 */
class Grid;

class Creamery {
  public:
	
		// Alignment,Direction,Pattern Enumeration
		enum {asc,desc,horizontal,vertical,strand,panel,mirrored};	
		
		Creamery(Grid *g);
		
		Grid *grid;
		
		// Effects
		void 
			step(),
			strobe(uint8_t runs),
			polkadotFill(uint32_t c, uint32_t d, uint8_t wait),
			PolkadotPulse(uint32_t c, uint32_t d, uint8_t wait, uint8_t sustain),
			PolkadotCycle(uint32_t c, uint32_t d, uint8_t wait),
			RainbowPulse(uint8_t wait),
			ColorPulse(uint32_t color, uint8_t wait),
			SparkleChaos1(),
			FasterSlower(),
			FadeInOutWhite(uint8_t wait),
			FadeInOutRandom(uint8_t wait),
			FadeInAll(uint32_t color, uint8_t wait),
			FadeOutAll(uint32_t color, uint8_t wait),
		
			FadeInSparkles(uint32_t color, uint8_t wait),
			FadeOutSparkles(uint8_t r, uint8_t g, uint8_t b, uint8_t wait),
			RandomWipeWipeWipe(),
			SlowFill(uint8_t r, uint8_t g, uint8_t b),
			SparkleRainbow(uint8_t density, uint8_t wait),
			DoubleRainbowSparkle(uint8_t density, uint8_t wait, uint8_t sustain),
			Sparkle(uint32_t color, uint8_t density, uint8_t wait),
			Sparkle(uint32_t color, uint8_t density, uint8_t wait, uint8_t sustain, uint32_t bg),
			SparkleFill(uint32_t color, uint8_t density, uint8_t wait),
			SparkleFaster(uint8_t duration),
			SparkleSlower(uint8_t duration),
			SinglePixel(uint8_t DELAY),
			CrazyPixel(uint32_t COLOR),
			SparkleRandom(),
			ColorJump(uint8_t DELAY),
			ButterflyEffect(),
			Malfunction(),
			FadeOut(uint8_t wait),
		
			rainbow(uint8_t wait),
			rainbowStrobe(uint8_t wait),
			rainbowCycle(uint8_t wait),
		
			colorWipe(uint32_t c, uint32_t d, uint8_t wait),
			colorFill(uint32_t c);
	
	
		unsigned const static long pduration = 900000; // Controller
		unsigned const static long iduration = 30000;  // Controller
		
		unsigned long  	//Controller

		int
			frequency,
			sustain,
			intensity,		//Effects
			direction,
			orientation,
			last_execution,
			division;			//Grid or Effects
	
		uint32_t 	// Define some fallback colors.
			primary,
			secondary,
			tertiary;


		bool // Currently unsure about this one. Attempt at making transitions work.
			trans(uint16_t i, uint32_t newcolor, uint8_t wait);

		uint8_t 
			R(uint8_t from, uint8_t to),			// Random Number Shortcut // Util.
			extractRed(uint32_t c),						// Effects
			extractGreen(uint32_t c),					// Effects
			extractBlue(uint32_t c);		      // Effects

		void 
			extractColor();								// Effects	
		
		uint32_t 		
			RandomColor(), 															// Effects > 
			RandomWheel(), 															// Effects > 
			rgba(byte r, byte g, byte b, double a), 		// Effects > 
			Color(byte r, byte g, byte b), 							// Effects > 
			Color(byte r, byte g, byte b, double a),    // Effects > 
			Color(uint32_t c, double a),                // Effects > 
			alpha(uint32_t c, double a),                // Effects > 
			Wheel(byte WheelPos),                       // Effects > 
			Wheel(byte WheelPos,double alpha);          // Effects > 
			

};


