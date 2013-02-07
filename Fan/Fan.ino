#include "SPI.h"
#include "Adafruit_WS2801.h"
#include <Easing.h>
#include <TrueRandom.h>
// #include "Grid.h"
#include "SoundStrip.h"

// Choose which 2 pins you will use for output.
// Can be any valid output pins.
// The colors of the wires may be totally different so
// BE SURE TO CHECK YOUR PIXELS TO SEE WHICH WIRES TO USE!
int dataPin  = 2;     // Yellow wire on Adafruit Pixels
int clockPin = 3;    // Green wire on Adafruit Pixels

// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
SoundStrip strip = SoundStrip(144, dataPin, clockPin);

// This doesn't do anything yet. I'm just preparing 
// int panelsX = 12;
// int panelsY = 1;
// int pixelsX = 1;
// int pixelsY = 12;

// Grid* grid = new Grid(strip,panelsX,pixelsY,pixelsX,pixelsY);

// Optional: leave off pin numbers to use hardware SPI
// (pinout is then specific to each board and can't be changed)
//Adafruit_WS2801 strip = Adafruit_WS2801(25);

void setup() {
		
  	strip.begin();
	
	Serial.begin(9600);
	// Sparkle s = new Sparkle();
	// Serial.println(s.total);

  	// Update LED contents, to start they are all 'off'
  	strip.show();

}

void loop() {	
	
	/*
	strip.timer = millis();
	
	Serial.print("Render: ");
	Serial.println(strip.timer);	
	
	if (test == 1) {
		// PolkadotCycle(RandomWheel(),RandomWheel(),100);
		// FadeOut(10);
		colorWipe(RandomWheel(),100);
	} else {

  	if (strip.timer > strip.iduration*strip.interval) {
		
			Serial.print("=== Interval "); Serial.print(strip.interval); Serial.println(" ===");			
			Serial.print("Timer: ");
			Serial.println(strip.timer);
			Serial.print("interval * iduration: ");
			Serial.println(strip.interval*strip.iduration);		
		
			// Check for Phase
			if (strip.timer > strip.phase * strip.pduration) {
				strip.phase++;
			}
		
			// Increment interval
	     	strip.interval++;		
		
			// This speeds us up as time goes on.
			if (strip.timer < 3*(60*(60*1000))) {
				strip.intensity = (strip.iduration / strip.interval) / selector;
			} else {
				strip.intensity = (strip.iduration / strip.interval / selector) %10 + (strip.phase/2);
			}

			// Increment Selector
	     	strip.selector = TrueRandom.random(0,10);
			// strip.selector = 8;
		
			// Check audio and other factors here...
			// 	Primary Color, Secondary Color, Delay, Odd/Even Interval
		
			strip.primary = strip.Wheel(TrueRandom.random(0,255));
			strip.secondary = strip.Wheel(TrueRandom.random(0,255));		
		
			Serial.print("Phase: ");
			Serial.println(strip.phase);
		
			Serial.print("Intensity: ");
			Serial.println(intensity);
		
			Serial.print("Selector: "); 	
		 	Serial.println(strip.selector);

		}

	
		if (phase < 4) {		
			// if (selector == 0) { Serial.println("Effect: Sparkle"); strip.Malfunction(); }
			if (selector == 1) { Serial.println("Effect: Sparkle"); strip.Sparkle(RandomWheel(), interval%20, 100, 100, primary); }
			if (selector == 2) { Serial.println("Effect: Strobe"); strip.DoubleRainbowSparkle(20,20,100); }
			if (selector == 3) { Serial.println("Effect: RainbowPulse"); strip.RainbowPulse(1); }	
			if (selector == 4) { Serial.println("Effect: ButterflyEffect"); strip.ButterflyEffect(); }
			if (selector == 5) { Serial.println("Effect: SparkleRandom"); strip.SparkleRandom(); }
			if (selector == 6) { Serial.println("Effect: ColorPulseRainbow"); strip.ColorPulse(RandomWheel(),10); }
			if (selector == 7) { Serial.println("Effect: PolkaDots"); strip.PolkadotPulse(strip.Wheel(TrueRandom.random(0,255)),strip.Wheel(TrueRandom.random(0,255)),50,1000); }				
			if (selector == 8) { Serial.println("Effect: SparkleRainbow Bubblegum IceCream"); strip.SparkleRainbow(20,intensity*10); }
			if (selector == 9) { Serial.println("Effect: Rainbow Strobe"); strip.rainbowStrobe(500); }
			if (selector == 10) { Serial.println("Effect: FasterSlower"); strip.FasterSlower(); }
		
		} else if (phase < 8) {
			// if (selector == 0) { Serial.println("Effect: Sparkle"); strip.Malfunction(); }
			if (selector == 1) { Serial.println("Effect: Sparkle"); strip.Sparkle(RandomWheel(), interval%20, 100, 100, primary); }
			if (selector == 2) { Serial.println("Effect: Strobe"); strip.DoubleRainbowSparkle(20,20,100); }
			if (selector == 3) { Serial.println("Effect: RainbowPulse"); strip.RainbowPulse(1); }	
			if (selector == 4) { Serial.println("Effect: SinglePixel"); strip.SinglePixel(1); }
			if (selector == 5) { Serial.println("Effect: SparkleRandom"); strip.SparkleRandom(); }
			if (selector == 6) { Serial.println("Effect: ColorPulseRainbow"); strip.ColorPulse(RandomWheel(),1); }
			if (selector == 7) { Serial.println("Effect: PolkaDots"); strip.PolkadotPulse(strip.Wheel(TrueRandom.random(0,255)),strip.Wheel(TrueRandom.random(0,255)),50,1000); }				
			if (selector == 8) { Serial.println("Effect: SparkleRainbow Bubblegum IceCream"); strip.SparkleRainbow(20,10); }
			if (selector == 9) { Serial.println("Effect: Rainbow Strobe"); strip.rainbowStrobe(500); }
			if (selector == 10) { Serial.println("Effect: SparkleChaos1"); strip.SparkleChaos1(); }
		
		} else if (phase < 16) {
			// if (selector == 0) { Serial.println("Effect: Sparkle"); strip.Malfunction(); }
			if (selector == 1) { Serial.println("Effect: Sparkle"); strip.Sparkle(RandomWheel(), interval%20, 100, 100, primary); }
			if (selector == 2) { Serial.println("Effect: Strobe"); strip.DoubleRainbowSparkle(20,20,100); }
			if (selector == 3) { Serial.println("Effect: RainbowPulse"); strip.RainbowPulse(1); }	
			if (selector == 4) { Serial.println("Effect: SinglePixel"); strip.SinglePixel(1); }
			if (selector == 5) { Serial.println("Effect: SparkleRandom"); strip.SparkleRandom(); }		
			if (selector == 6) { Serial.println("Effect: FadeInOutRandom"); strip.FadeInOutRandom(10); }
			if (selector == 7) { Serial.println("Effect: PolkaDotStrobe"); strip.polkadotFill(strip.Wheel(TrueRandom.random(0,255)),strip.Wheel(TrueRandom.random(0,255)),intensity*10); }	
			if (selector == 8) { Serial.println("Effect: SparkleRainbow Bubblegum IceCream"); strip.SparkleRainbow(20,10); }
			if (selector == 9) { Serial.println("Effect: Rainbow Strobe"); strip.rainbowStrobe(500); }
			if (selector == 10) { Serial.println("Effect: SparkleChaos1"); strip.SparkleChaos1(); }
		
		} else if (phase < 32) {	
			// if (selector == 0) { Serial.println("Effect: Sparkle"); strip.Malfunction(); }
			if (selector == 1) { Serial.println("Effect: Sparkle"); strip.Sparkle(RandomWheel(), interval%20, 100, 100, primary); }
			if (selector == 2) { Serial.println("Effect: Strobe"); strip.DoubleRainbowSparkle(20,20,100); }
			if (selector == 3) { Serial.println("Effect: RainbowPulse"); strip.RainbowPulse(1); }	
			if (selector == 4) { Serial.println("Effect: SinglePixel"); strip.SinglePixel(1); }
			if (selector == 5) { Serial.println("Effect: SparkleRandom"); strip.SparkleRandom(); }
			if (selector == 6) { Serial.println("Effect: FadeInOutRandom"); strip.FadeInOutRandom(10); }
			if (selector == 7) { Serial.println("Effect: PolkaDots"); strip.polkadotFill(strip.Wheel(TrueRandom.random(0,255)),strip.Wheel(TrueRandom.random(0,255)),500); }	
			if (selector == 8) { Serial.println("Effect: SparkleRainbow Bubblegum IceCream"); strip.SparkleRainbow(20,10); }
			if (selector == 9) { Serial.println("Effect: Rainbow Strobe"); strip.rainbowStrobe(500); }
			if (selector == 10) { Serial.println("Effect: SparkleChaos1"); strip.SparkleChaos1(); }
		
		} else { phase = 1; }
			
		// DoubleRainbowSparkle(20,20,100);
		// Malfunction
		// Butterfly
		// strobe white over rainbow bg
	}
	*/
	strip.render();
}
