#include "Adafruit_WS2801.h"
#include "CTRL.h"
#include "Grid.h"
#include "TrueRandom.h"
// #include <Easing.h>

CTRL::CTRL(Adafruit_WS2801 *strip,int panelsX, int panelsY,int pixelsX,int pixelsY) {	
	
	this->total = strip->numPixels();
	this->strip = strip;

	Grid *g = new Grid(strip,panelsX,panelsY,pixelsX,pixelsY,panel);
	this->grid = g;

	this->creamery = new Creamery(g);
		
	// === Controller vars ===
	this->timer = 0;
	this->phase = 4;
	// this->current_phase = this->starting_phase; ///
	this->interval = 0;
	
	// this->iduration = TrueRandom(20000,70000);

	// This will become the current effect parameter.
	this->selector = 0;
	
	// === Pattern vars ===
	// this->mood;
	// 
	
	
	// === Grid / Pattern vars === 
	// Division sets the strand mode. 1 is regular, 2 is Mirror, 3 is Triangle (not added yet), 4 is Radial.
	this->mode = panel;
	this->grid->orientation = vertical;
	this->direction = desc;
	this->density = 1;
	this->frequency = 200;
	this->grid->brightness = 1;
			
	// this->panelsX = 12;
	// this->panelsY = 1;
	// this->pixelsX = 1;
	// this->pixelsY = 12;
	// this->division = 12;

	// Colors:
	this->r = 1;
	this->g = 1;
	this->b = 1;
	// this->primary = this->RandomWheel();
	// this->secondary = this->RandomWheel();

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

void CTRL::step() {   
	this->timer = millis();

	Serial.print("-- Render: ");
	Serial.println(this->timer);

	// this->creamery->Sparkle(this->creamery->RandomWheel(),this->density,this->frequency);

	// this->creamery->colorWipe(creamery->Color(this->r,this->g,this->b),asc,0);
	
	// creamery->PolkadotPulse(creamery->Color(40,40,0),creamery->Color(40,0,40),1,10);
	// creamery->PolkadotPulse(creamery->Color(40,0,40),creamery->Color(0,40,40),10,10);
		
	if (selector == 0) {
		// grid->setBrightness(0.5);		
		// this->grid->orientation = vertical; this->creamery->colorWipe(this->creamery->RandomWheel(),asc,300);
		// PolkadotCycle(RandomWheel(),RandomWheel(),100);
		// this->creamery->SparkleChaos1();
		// this->creamery->RainbowPulse(10);
		// this->creamery->Sparkle(this->creamery->RandomWheel(),this->density,this->frequency);
		// this->creamery->singlePulse(1,this->creamery->RandomWheel(),300,20);
		// this->creamery->PolkadotPulse(this->creamery->Wheel(TrueRandom.random(0,80)),this->creamery->Wheel(TrueRandom.random(0,80)),50,20));
		// this->creamery->singlePulseWipe(this->creamery->Wheel(TrueRandom.random(0,255)), asc, 30,20);	
		// this->creamery->PolkadotPulse(this->creamery->Wheel(TrueRandom.random(0,255)),this->creamery->Wheel(TrueRandom.random(0,255)),10,10);
		// this->creamery->rainbowCycle(2);
		// Serial.println("Normal...");

		// this->creamery->colorWipe(creamery->Color(40,0,0),asc,160);
		// this->creamery->colorWipe(creamery->Color(0,40,0),asc,160);
	} else {
		Serial.println("Worked!");
		// this->creamery->colorWipe(creamery->Color(40,0,40),asc,160);
		// this->creamery->colorWipe(creamery->Color(0,40,40),asc,160);		
		
	}
	// delay(this->wait);
	// this->grid->show();
	
}
void CTRL::render() {   

	this->timer = millis();
	
	// Serial.print("Render: ");
	// Serial.println(this->timer);	
	
	if (test == 1) {
		
		Serial.println("Test Mode");	
		this->grid->orientation = horizontal; this->creamery->colorWipe(this->creamery->RandomWheel(),this->direction,100);
			// this->creamery->Sparkle(this->creamery->Wheel(TrueRandom.random(0,255)), intensity, 100, 300, creamery->Color(0,0,0));
			// this->creamery->rainbowCycle(10);	
		// grid->setBrightness(0.5);		
		// this->grid->orientation = vertical; this->creamery->colorWipe(this->creamery->RandomWheel(),asc,300);

		// this->creamery->colorWipe(this->creamery->RandomWheel(),asc,160);
	} else {

	  	if (this->timer > this->iduration*this->interval) {
			
			// this->mode = getMode(root)
			// this->direction = getDir(root)
			// this->orientation = getOr(root);
			// this->delay = getDelay(root);
			// this->sustain = getSust(root);
			// this->r = getR(root);
			// this->g = getG(root);
			// this->b = getB(root);
			// this->a = getA(root);
			
			
			// Check for Phase
			if (this->timer > phase * pduration) {
				phase++;
			}			
			
			// Increment interval
	     	this->interval++;
		
			this->iduration = TrueRandom.random(10,20) * 1000;
		
			// This speeds us up as time goes on.
			if (timer < 3*(60*(60*1000))) {
				intensity = (iduration / interval) / selector + 1;
			} else {
				intensity = (iduration / interval / selector) %10 + (phase/2)+1;
			}

			// Adjust directions /// Make this better
			if (this->direction == asc) { this->direction = desc;} else {this->direction = asc;}
			
			// Increment Selector
			// int max_random = 10
		     	selector = TrueRandom.random(0,13);
			// this->selector = TrueRandom.random(0,10+phase);
		
			// Check audio and other factors here...
			// 	Primary Color, Secondary Color, Delay, Odd/Even Interval
		
			primary = this->creamery->Wheel(TrueRandom.random(0,255));
			secondary = this->creamery->Wheel(TrueRandom.random(0,255));		
			this->grid->mode = panel;
		
			if (debug) {
				Serial.print("=== Interval "); Serial.print(this->interval); Serial.println(" ===");			

				Serial.print("Interval Duration: ");
				Serial.println(this->iduration / 1000);				

				Serial.print("Timer: ");
				Serial.println(this->timer);
				
				Serial.print("Interval x Iduration: ");
				Serial.println(this->interval*this->iduration);		
			
				Serial.print("Phase: ");
				Serial.println(phase);

				Serial.print("Intensity: ");
				Serial.println(intensity);

				Serial.print("Selector: "); 	
			 	Serial.println(this->selector);
				
			}
			
		}

		// -- Mood
		
		// --- Pattern
		// Color
		// Polkadot
		// Rainbow
		// Chaos
		
		// -- Action
		// Wipe
		// Cycle		
		// Sparkle 
		// Strobe
		// Pulse
		
		// -- Mood
		
		selector = 7;		 /// HARDCODED
	
	
		// if (mood == party) {		
			
			// Party CTRL Settings.
			// if (selector == 0) { Serial.println("Effect: Red Panel Pulse"); this->grid->orientation = horizontal; this->creamery->singlePulseWipe(this->creamery->Wheel(TrueRandom.random(40,80)), this->direction, 30,10);	}
			// if (selector == 0) { Serial.println("Effect: Red Panel Pulse"); this->grid->orientation = horizontal; this->creamery->singlePulseWipe(this->creamery->Wheel(TrueRandom.random(0,255)), this->direction, 30,4);	}
			// if (selector == 1) { Serial.println("Effect: Color Wipe Vertical ASC"); this->grid->orientation = vertical; this->creamery->colorWipe(this->creamery->RandomWheel(),this->direction,100); }
			// if (selector == 2) { Serial.println("Effect: Color Wipe Horizontal ASC"); this->grid->orientation = horizontal; this->creamery->colorWipe(this->creamery->RandomWheel(),this->direction,100); }
			// if (selector == 3) { Serial.println("Effect: Color Wipe Vertical DESC"); this->grid->orientation = vertical; this->creamery->colorWipe(this->creamery->RandomWheel(),desc,100); }	
			// if (selector == 4) { Serial.println("Effect: Color Wipe Horizontal DESC"); this->grid->orientation = horizontal; this->creamery->colorWipe(this->creamery->RandomWheel(),desc,100); }				
			// if (selector == 5) { Serial.println("Effect: Single Panel Pulse");this->grid->orientation = horizontal; this->creamery->singlePulseWipe(this->creamery->Wheel(TrueRandom.random(0,255)), desc, 30,4);	}
			// if (selector == 6) { Serial.println("Effect: ColorPulseRainbow"); this->creamery->ColorPulse(this->creamery->RandomWheel(),10); }
			// if (selector == 7) { Serial.println("Effect: PolkaDots"); this->creamery->PolkadotPulse(this->creamery->Wheel(TrueRandom.random(0,255)),this->creamery->Wheel(TrueRandom.random(0,255)),50,1000); }						
			// if (selector == 8) { Serial.println("Effect: Rainbow Cycle"); this->creamery->rainbowCycle(10); }			
			// if (selector == 9) { Serial.println("Effect: Color Wipe Horizontal"); this->grid->orientation = horizontal; this->creamery->colorWipe(this->creamery->RandomWheel(),this->direction,300); }		
			// if (selector == 10) { Serial.println("Effect: SparkleChaos1"); this->creamery->SparkleChaos1(); }
			// if (selector == 11) { Serial.println("Effect: SparkleChaos1"); this->creamery->SparkleChaos1(); }
			// if (selector == 12) { Serial.println("Effect: Rainbow Cycle"); this->creamery->rainbowCycle(10); }			
			// if (selector == 13) { Serial.println("Effect: RainbowPulse"); this->creamery->RainbowPulse(10); }							
			// if (selector == 14) { Serial.println("Effect: Sparkle"); this->creamery->Sparkle(this->creamery->RandomWheel(), 10, 100, 100, creamery->RandomWheel()); }
			
		// } else if (mood == mellow) {
			
			if (selector == 0) { Serial.println("Effect: Slow Sparkle Pulse"); this->grid->orientation = horizontal; this->creamery->singlePulseWipe(this->creamery->Wheel(TrueRandom.random(0,255)), this->direction, 30,4);	}
			if (selector == 1) { Serial.println("Effect: Color Wipe Vertical ASC"); this->grid->orientation = vertical; this->creamery->colorWipe(this->creamery->RandomWheel(),this->direction,100); }
			if (selector == 2) { Serial.println("Effect: Color Wipe Horizontal ASC"); this->grid->orientation = horizontal; this->creamery->colorWipe(this->creamery->RandomWheel(),this->direction,100); }
			if (selector == 3) { Serial.println("Effect: Color Wipe Vertical DESC"); this->grid->orientation = vertical; this->creamery->colorWipe(this->creamery->RandomWheel(),desc,100); }	
			if (selector == 4) { Serial.println("Effect: Color Wipe Horizontal DESC"); this->grid->orientation = horizontal; this->creamery->colorWipe(this->creamery->RandomWheel(),desc,100); }				
			if (selector == 5) { Serial.println("Effect: Single Panel Pulse");this->grid->orientation = horizontal; this->creamery->singlePulseWipe(this->creamery->Wheel(TrueRandom.random(0,255)), desc, 30,4);	}
			if (selector == 6) { Serial.println("Effect: ColorPulseRainbow"); this->creamery->ColorPulse(this->creamery->RandomWheel(),10); }
			if (selector == 7) { Serial.println("Effect: SparkleRainbow"); this->creamery->SparkleRainbow(random(1,11),100); }						
			// if (selector == 7) { Serial.println("Effect: PolkaDots"); this->creamery->PolkadotPulse(this->creamery->Wheel(TrueRandom.random(0,255)),this->creamery->Wheel(TrueRandom.random(0,255)),50,1000); }						
			if (selector == 8) { Serial.println("Effect: Rainbow Cycle"); this->creamery->rainbowCycle(10); }			
			if (selector == 9) { Serial.println("Effect: Color Wipe Horizontal"); this->grid->orientation = horizontal; this->creamery->colorWipe(this->creamery->RandomWheel(),this->direction,300); }			
			
			// if (selector == 10) { Serial.println("Effect: Slow Sparkle"); this->grid->mode = strand; this->creamery->singlePulse(TrueRandom.random(1,12),this->creamery->Wheel(TrueRandom.random(0,255)), 100, 80); }
			if (selector == 10) { Serial.println("Effect: Slow Sparkle"); this->grid->mode = strand; this->creamery->singlePulse(TrueRandom.random(1,12),this->creamery->Wheel(TrueRandom.random(0,255)), 40, 40); }
			
			
			if (selector == 11) { 
				int n = TrueRandom.random(1,12); Serial.print("Effect: nPulse(");Serial.print(n);Serial.println(")"); 
				this->grid->mode = strand; this->creamery->nPulse(n,this->creamery->Wheel(TrueRandom.random(0,255)), 40, 40); 
			}
			
			
		// }
			
			// if (selector == 15) { Serial.println("Effect: SparkleRainbow Bubblegum IceCream"); this->creamery->SparkleRainbow(20,10); }
			// if (selector == 16) { Serial.println("Effect: DoubleRainbowSparkle"); this->creamery->DoubleRainbowSparkle(20,20,100); }


			// if (phase >= 14) {phase=14;}
			
		// } else if (phase < 8) {
		// 	if (selector == 0) { Serial.println("Effect: Sparkle"); this->creamery->Malfunction(); }
		// 	if (selector == 1) { Serial.println("Effect: Sparkle"); this->creamery->Sparkle(this->creamery->RandomWheel(), interval%20, 100, 100, primary); }
		// 	if (selector == 2) { Serial.println("Effect: Strobe"); this->creamery->DoubleRainbowSparkle(20,20,100); }
		// 	if (selector == 3) { Serial.println("Effect: RainbowPulse"); this->creamery->RainbowPulse(1); }	
		// 	if (selector == 4) { Serial.println("Effect: SinglePixel"); this->creamery->SinglePixel(1); }
		// 	if (selector == 5) { Serial.println("Effect: SparkleRandom"); this->creamery->SparkleTrueRandom.random(); }
		// 	if (selector == 6) { Serial.println("Effect: ColorPulseRainbow"); this->creamery->ColorPulse(this->creamery->RandomWheel(),1); }
		// 	if (selector == 7) { Serial.println("Effect: PolkaDots"); this->creamery->PolkadotPulse(this->creamery->Wheel(TrueRandom.random(0,255)),this->creamery->Wheel(TrueRandom.random(0,255)),50,1000); }				
		// 	if (selector == 8) { Serial.println("Effect: SparkleRainbow Bubblegum IceCream"); this->creamery->SparkleRainbow(20,10); }
		// 	if (selector == 9) { Serial.println("Effect: Rainbow Strobe"); this->creamery->rainbowStrobe(500); }
		// 
		// 	if (selector == 11) { Serial.println("Effect: Red Panel Pulse"); this->creamery->singlePulseWipe(this->creamery->Wheel(TrueRandom.random(40,80)), asc, 30,20);	}			
		// 	if (selector == 12) { Serial.println("Effect: Red Panel Pulse"); this->creamery->singlePulseWipe(this->creamery->Wheel(TrueRandom.random(40,80)), asc, 30,20);	}						
		// 
		// } else if (phase < 16) {
		// 	if (selector == 0) { Serial.println("Effect: Sparkle"); this->creamery->Malfunction(); }
		// 	if (selector == 1) { Serial.println("Effect: Sparkle"); this->creamery->Sparkle(this->creamery->RandomWheel(), interval%20, 100, 100, primary); }
		// 	if (selector == 2) { Serial.println("Effect: Strobe"); this->creamery->DoubleRainbowSparkle(20,20,100); }
		// 	if (selector == 3) { Serial.println("Effect: RainbowPulse"); this->creamery->RainbowPulse(1); }	
		// 	if (selector == 4) { Serial.println("Effect: SinglePixel"); this->creamery->SinglePixel(1); }
		// 	if (selector == 5) { Serial.println("Effect: SparkleRandom"); this->creamery->SparkleTrueRandom.random(); }		
		// 	if (selector == 6) { Serial.println("Effect: FadeInOutRandom"); this->creamery->FadeInOutTrueRandom.random(10); }
		// 	if (selector == 7) { Serial.println("Effect: PolkaDotStrobe"); this->creamery->polkadotFill(this->creamery->Wheel(TrueRandom.random(0,255)),this->creamery->Wheel(TrueRandom.random(0,255)),intensity*10); }	
		// 	if (selector == 8) { Serial.println("Effect: SparkleRainbow Bubblegum IceCream"); this->creamery->SparkleRainbow(20,10); }
		// 	if (selector == 9) { Serial.println("Effect: Rainbow Strobe"); this->creamery->rainbowStrobe(500); }
		// 	if (selector == 10) { Serial.println("Effect: SparkleChaos1"); this->creamery->SparkleChaos1(); }
		// 	if (selector == 11) { Serial.println("Effect: Color Wipe Horizontal"); this->grid->orientation = horizontal; this->creamery->colorWipe(this->creamery->RandomWheel(),asc,300); }
		// 	if (selector == 12) { Serial.println("Effect: Color Wipe Horizontal"); this->grid->orientation = horizontal; this->creamery->colorWipe(this->creamery->RandomWheel(),asc,300); }			
		// 
		// } else if (phase < 32) {	
		// 	// if (selector == 0) { Serial.println("Effect: Sparkle"); this->creamery->Malfunction(); }
		// 	if (selector == 1) { Serial.println("Effect: Sparkle"); this->creamery->Sparkle(this->creamery->RandomWheel(), interval%20, 100, 100, primary); }
		// 	if (selector == 2) { Serial.println("Effect: Strobe"); this->creamery->DoubleRainbowSparkle(20,20,100); }
		// 	if (selector == 3) { Serial.println("Effect: RainbowPulse"); this->creamery->RainbowPulse(1); }	
		// 	if (selector == 4) { Serial.println("Effect: SinglePixel"); this->creamery->SinglePixel(1); }
		// 	if (selector == 5) { Serial.println("Effect: SparkleRandom"); this->creamery->SparkleTrueRandom.random(); }
		// 	if (selector == 6) { Serial.println("Effect: FadeInOutRandom"); this->creamery->FadeInOutTrueRandom.random(10); }
		// 	if (selector == 7) { Serial.println("Effect: PolkaDots"); this->creamery->polkadotFill(this->creamery->Wheel(TrueRandom.random(0,255)),this->creamery->Wheel(TrueRandom.random(0,255)),500); }	
		// 	if (selector == 8) { Serial.println("Effect: SparkleRainbow Bubblegum IceCream"); this->creamery->SparkleRainbow(20,10); }
		// 	if (selector == 9) { Serial.println("Effect: Rainbow Strobe"); this->creamery->rainbowStrobe(500); }
		// 	if (selector == 10) { Serial.println("Effect: SparkleChaos1"); this->creamery->SparkleChaos1(); }
		// 	if (selector == 11) { Serial.println("Effect: Color Wipe Horizontal"); this->grid->orientation = horizontal; this->creamery->colorWipe(this->creamery->RandomWheel(),asc,300); }
		// 	if (selector == 11) { Serial.println("Effect: Color Wipe Horizontal"); this->grid->orientation = horizontal; this->creamery->colorWipe(this->creamery->RandomWheel(),asc,300); }			
		// 
		// } else { phase = 1; }
			
		// DoubleRainbowSparkle(20,20,100);
		// Malfunction
		// Butterfly
		// strobe white over rainbow bg
	}
}

void CTRL::setSelector(uint16_t s) {
	Serial.println("Calling setSelector");
	this->selector = s;
}

// uint32_t RandomWheel() {	
// 	return Wheel(TrueRandom.random(0,255)%255);		
// }

