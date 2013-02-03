#include <Arduino.h>
#include "Creamery.h"
#include <Easing.h>

/*
 * The color wipe effect changes each pixel in turn
 * to the given color.
 */

class SoundStrip : public Creamery {
  public:
	
    SoundStrip(uint16_t n, uint8_t dpin, uint8_t cpin, uint8_t order=WS2801_RGB);
	
	int
		spectrumReset,
		spectrumStrobe,
		spectrumAnalog,  //0 for left channel, 1 for right.

		// Spectrum analyzer read values will be kept here.
		Spectrum[7],

		average,
		kickThreshold,
		snareThreshold,
		kick,
		snare,

		// Divisor for audio signal scaling ///
		// 22 ~ 80
		// 72 ~ 10
		Divisor;
		
	
	void
		colorWipe(uint32_t c, uint8_t wait),
		RainbowLevel(uint8_t wait),
		rainbowPulse(uint8_t wait),
		rainbowSpectrum(uint8_t wait),
		readSpectrum(),		
		showSpectrum(uint8_t wait),
		mirror(int pos, uint32_t color),
		q(int pos, uint32_t color),
		render();

  private:
	long timer;
	unsigned const static long pduration = 900000;
	unsigned const static long iduration = 30000;
		
	unsigned long 
		interval,
		phase;

	int test,
		selector,
		intensity,
		division;

	uint32_t 
		primary,
		secondary;
			
};


