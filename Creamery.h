#include <Arduino.h>
#include "Adafruit_WS2801.h"

/*
 * The color wipe effect changes each pixel in turn
 * to the given color.
 */

class Creamery : public Adafruit_WS2801 {
  public:
	
    Creamery(uint16_t n, uint8_t dpin, uint8_t cpin, uint8_t order=WS2801_RGB);
	
	void 
		render(),
		strobe(uint8_t runs),
		polkadotFill(uint32_t c, uint32_t d, uint8_t wait),
		PolkadotPulse(uint32_t c, uint32_t d, uint8_t wait, uint8_t sustain),
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
		
		colorWipe(uint32_t c, uint8_t wait),
		colorFill(uint32_t c);
	
	long timer;
	unsigned const static long pduration = 900000;
	unsigned const static long iduration = 30000;
		
	unsigned long 
		interval,
		phase;

	int test,
		selector,
		intensity;

	bool 
		trans(uint16_t i, uint32_t newcolor, uint8_t wait);
	
	uint32_t 
		primary,
		secondary;

    // uint16_t current_pixel;
	uint8_t 
		R(uint8_t from, uint8_t to),
		extractRed(uint32_t c),
		extractGreen(uint32_t c),
		extractBlue(uint32_t c);		

	void 
		extractColor();
		
	uint32_t 		
		RandomColor(),
		RandomWheel(),
		rgba(byte r, byte g, byte b, double a),
		Color(byte r, byte g, byte b),
		Color(byte r, byte g, byte b, double a),		
		Color(uint32_t c, double a),
		alpha(uint32_t c, double a),
		Wheel(byte WheelPos),
		Wheel(byte WheelPos,double alpha);
		
	

};


