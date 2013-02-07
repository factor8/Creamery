#include "Adafruit_WS2801.h"
#include "SoundStrip.h"
#include "TrueRandom.h"
#include <Easing.h>

SoundStrip::SoundStrip(uint16_t n, uint8_t dpin, uint8_t cpin, uint8_t order) : Creamery(n, dpin, cpin, order) {
	
	this->total = this->numPixels();

	Serial.println("Constructing... ");	
		
	// === Controller vars ===
	this->timer = 0;
	this->phase = 0;
	this->interval = 0;
	// iduration = 15000;	
	// pduration = 900000; 15 Minutes
	this->selector = 0;
	
	// === Pattern vars ===
	
	// === Grid / Pattern vars === 
	// Division sets the strand mode. 1 is regular, 2 is Mirror, 3 is Triangle (not added yet), 4 is Radial.
	this->mode = panel;
	this->panelsX = 12;
	this->panelsY = 1;
	this->pixelsX = 1;
	this->pixelsY = 12;
	this->division = 12;
	this->orientation = 1;	


	// Colors:
	this->primary = this->RandomWheel();
	this->secondary = this->RandomWheel();
	

	// Phase modifier = phase * 
	// %10
	
	this->debug = 1;
	this->test = 1;
	
	if (this->test == 1) {
		Serial.println("Test Mode Engaged");
	}
	if (this->debug == 1) {
		Serial.println("Debug Mode Engaged");
	}
}
///Do we need deconstructor?

// Ignore this.
void SoundStrip::grid() {
	int pix[this->total];
	int panels[12];
	int i,j;
	for (i;i<this->total/this->division;i++) {
		for (j;j<this->division;j++) {
			// pix[i] = l
		}
		// pix[i] = (i%2) ? (division*i)+(division-1)-i : (i*division)+(i);		


		// Serial.print(i);Serial.print(" - ");Serial.println(pix[i]);
	}
	// for each panel set pixels
}

void SoundStrip::render() {   

	this->timer = millis();
	
	Serial.print("Render: ");
	Serial.println(this->timer);	
	
	if (test == 1) {
		Serial.println("Test Mode Engaged");
		
		// PolkadotCycle(RandomWheel(),RandomWheel(),100);
		// FadeOut(10);
		colorWipe(RandomWheel(),600);
	} else {

	  	if (this->timer > this->iduration*this->interval) {
			if (debug) {
				Serial.print("=== Interval "); Serial.print(this->interval); Serial.println(" ===");			
				Serial.print("Timer: ");
				Serial.println(this->timer);
				Serial.print("interval * iduration: ");
				Serial.println(this->interval*this->iduration);		
			}
			// Check for Phase
			if (this->timer > phase * pduration) {
				phase++;
			}
		
			// Increment interval
	     	this->interval++;		
		
			// This speeds us up as time goes on.
			if (timer < 3*(60*(60*1000))) {
				intensity = (iduration / interval) / selector;
			} else {
				intensity = (iduration / interval / selector) %10 + (phase/2);
			}

			// Increment Selector
	     	this->selector = TrueRandom.random(0,10);
			// this->selector = 8;
		
			// Check audio and other factors here...
			// 	Primary Color, Secondary Color, Delay, Odd/Even Interval
		
			primary = this->Wheel(TrueRandom.random(0,255));
			secondary = this->Wheel(TrueRandom.random(0,255));		
		
			Serial.print("Phase: ");
			Serial.println(phase);
		
			Serial.print("Intensity: ");
			Serial.println(intensity);
		
			Serial.print("Selector: "); 	
		 	Serial.println(this->selector);

		}

	
		if (phase < 4) {		
			if (selector == 0) { Serial.println("Effect: Sparkle"); this->Malfunction(); }
			if (selector == 1) { Serial.println("Effect: Sparkle"); this->Sparkle(RandomWheel(), interval%20, 100, 100, primary); }
			if (selector == 2) { Serial.println("Effect: Strobe"); this->DoubleRainbowSparkle(20,20,100); }
			if (selector == 3) { Serial.println("Effect: RainbowPulse"); this->RainbowPulse(1); }	
			if (selector == 4) { Serial.println("Effect: ButterflyEffect"); this->ButterflyEffect(); }
			if (selector == 5) { Serial.println("Effect: SparkleRandom"); this->SparkleRandom(); }
			if (selector == 6) { Serial.println("Effect: ColorPulseRainbow"); this->ColorPulse(RandomWheel(),10); }
			if (selector == 7) { Serial.println("Effect: PolkaDots"); this->PolkadotPulse(this->Wheel(TrueRandom.random(0,255)),this->Wheel(TrueRandom.random(0,255)),50,1000); }				
			if (selector == 8) { Serial.println("Effect: SparkleRainbow Bubblegum IceCream"); this->SparkleRainbow(20,intensity*10); }
			if (selector == 9) { Serial.println("Effect: Rainbow Strobe"); this->rainbowStrobe(500); }
			if (selector == 10) { Serial.println("Effect: FasterSlower"); this->FasterSlower(); }
		
		} else if (phase < 8) {
			if (selector == 0) { Serial.println("Effect: Sparkle"); this->Malfunction(); }
			if (selector == 1) { Serial.println("Effect: Sparkle"); this->Sparkle(RandomWheel(), interval%20, 100, 100, primary); }
			if (selector == 2) { Serial.println("Effect: Strobe"); this->DoubleRainbowSparkle(20,20,100); }
			if (selector == 3) { Serial.println("Effect: RainbowPulse"); this->RainbowPulse(1); }	
			if (selector == 4) { Serial.println("Effect: SinglePixel"); this->SinglePixel(1); }
			if (selector == 5) { Serial.println("Effect: SparkleRandom"); this->SparkleRandom(); }
			if (selector == 6) { Serial.println("Effect: ColorPulseRainbow"); this->ColorPulse(RandomWheel(),1); }
			if (selector == 7) { Serial.println("Effect: PolkaDots"); this->PolkadotPulse(this->Wheel(TrueRandom.random(0,255)),this->Wheel(TrueRandom.random(0,255)),50,1000); }				
			if (selector == 8) { Serial.println("Effect: SparkleRainbow Bubblegum IceCream"); this->SparkleRainbow(20,10); }
			if (selector == 9) { Serial.println("Effect: Rainbow Strobe"); this->rainbowStrobe(500); }
			if (selector == 10) { Serial.println("Effect: SparkleChaos1"); this->SparkleChaos1(); }
		
		} else if (phase < 16) {
			if (selector == 0) { Serial.println("Effect: Sparkle"); this->Malfunction(); }
			if (selector == 1) { Serial.println("Effect: Sparkle"); this->Sparkle(RandomWheel(), interval%20, 100, 100, primary); }
			if (selector == 2) { Serial.println("Effect: Strobe"); this->DoubleRainbowSparkle(20,20,100); }
			if (selector == 3) { Serial.println("Effect: RainbowPulse"); this->RainbowPulse(1); }	
			if (selector == 4) { Serial.println("Effect: SinglePixel"); this->SinglePixel(1); }
			if (selector == 5) { Serial.println("Effect: SparkleRandom"); this->SparkleRandom(); }		
			if (selector == 6) { Serial.println("Effect: FadeInOutRandom"); this->FadeInOutRandom(10); }
			if (selector == 7) { Serial.println("Effect: PolkaDotStrobe"); this->polkadotFill(this->Wheel(TrueRandom.random(0,255)),this->Wheel(TrueRandom.random(0,255)),intensity*10); }	
			if (selector == 8) { Serial.println("Effect: SparkleRainbow Bubblegum IceCream"); this->SparkleRainbow(20,10); }
			if (selector == 9) { Serial.println("Effect: Rainbow Strobe"); this->rainbowStrobe(500); }
			if (selector == 10) { Serial.println("Effect: SparkleChaos1"); this->SparkleChaos1(); }
		
		} else if (phase < 32) {	
			// if (selector == 0) { Serial.println("Effect: Sparkle"); this->Malfunction(); }
			if (selector == 1) { Serial.println("Effect: Sparkle"); this->Sparkle(RandomWheel(), interval%20, 100, 100, primary); }
			if (selector == 2) { Serial.println("Effect: Strobe"); this->DoubleRainbowSparkle(20,20,100); }
			if (selector == 3) { Serial.println("Effect: RainbowPulse"); this->RainbowPulse(1); }	
			if (selector == 4) { Serial.println("Effect: SinglePixel"); this->SinglePixel(1); }
			if (selector == 5) { Serial.println("Effect: SparkleRandom"); this->SparkleRandom(); }
			if (selector == 6) { Serial.println("Effect: FadeInOutRandom"); this->FadeInOutRandom(10); }
			if (selector == 7) { Serial.println("Effect: PolkaDots"); this->polkadotFill(this->Wheel(TrueRandom.random(0,255)),this->Wheel(TrueRandom.random(0,255)),500); }	
			if (selector == 8) { Serial.println("Effect: SparkleRainbow Bubblegum IceCream"); this->SparkleRainbow(20,10); }
			if (selector == 9) { Serial.println("Effect: Rainbow Strobe"); this->rainbowStrobe(500); }
			if (selector == 10) { Serial.println("Effect: SparkleChaos1"); this->SparkleChaos1(); }
		
		} else { phase = 1; }
			
		// DoubleRainbowSparkle(20,20,100);
		// Malfunction
		// Butterfly
		// strobe white over rainbow bg
	}
}



// fill the dots one after the other with said color
// good for testing purposes
void SoundStrip::colorWipe(uint32_t c, uint8_t wait) {
  	int i;  
	
	// if (orientation == horizontal) {
	// 	division = panelX or panelY
	// }
	// if (direction == horizontal) {
	// 	division = panelX or panelY
	// }
	
	this->division = 3;
	Serial.println(this->numPixels());
	
	Serial.println("Beginning ColorWipe...");
  	for (i=0; i<this->numPixels()/this->division; i++) {		
		q(i, c);
		this->show();
		delay(wait);
  	}
}

// Translate the LED position to Mirror the strand output. This is a custom mapping for a DJ Booth
void SoundStrip::mirror(int pos, uint32_t color) {
// 
// 	int left,right;
//  	
// 	if (pos >= 0 && pos <= 10) {
// 		left = 11 - pos;
// 		right = 12 + pos;
// 		if (pos == 10) { right = 0; }
// 	}	
// 
// 	if (pos >= 11 && pos <= 17) {
// 		left = 40 - pos;
// 		right = 19 + pos;
// 	}	
// 	
//   if (pos >= 18 && pos <= 23) {
// 		left = 90 - pos;
// 		right = 19 + pos;
// 	}
// 	
// 	if (pos >= 24 && pos <= 26) {
// 		// 	left = 41 - pos;
// 		// 	right = 21 + pos;				
// 		// if (pos == 25) { left = 49; }
// 		return;
// 	}
// 	
// 	if (pos >= 27 && pos <= 35) {
// 		// R = 56 - 9  47 = 27
// 		left = 20 + pos;
// 		right = 91 - pos;
// 				
// 		// if (pos == 25) { left = 49; }
// 	}	
// 	
//   this->setPixelColor(left, color);
//   this->setPixelColor(right, color);
}


// "Queue" method to translate pixel positions for standard, mirrored, and radial modes.
void SoundStrip::q(int pos, uint32_t color) {		

	if (this->mode == strand) {
		this->setPixelColor(pos,color);
	} else if (this->mode == mirrored) {
		// left/right mirror mode.
		// mirror(pos,color);
	} else if (division == 4) {
		// Radial Mode
		// radial(pos,color);
	}	
	if (this->mode == panel) { // Make each panel do the same thing.
		int p;
		
		//HARDCODE!///
		this->orientation = horizontal; ///
		// Serial.println(this->orientation);
		
		if (this->orientation == horizontal) {
			for (int i=0;i<this->numPixels()/this->panelsX;i++) {				
				p = this->pixelsY*pos+i;
				this->setPixelColor(p, color);
				Serial.println(p);				
			}
		} else if (this->orientation == vertical) {
		
			for (int i=0;i<this->numPixels()/this->pixelsY;i++) {
				p = (i%2) ? (this->panelsX*i)+(this->pixelsY-1)-(pos) : (i*this->panelsX)+(pos);
				this->setPixelColor(p, color);		
			}
		}	
	}
				 
}
