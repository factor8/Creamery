#include "Adafruit_WS2801.h"
#include "SoundStrip.h"
#include "TrueRandom.h"
#include <Easing.h>

SoundStrip::SoundStrip(uint16_t n, uint8_t dpin, uint8_t cpin, uint8_t order) : Creamery(n, dpin, cpin, order) {
	
	// this->total = this->numPixels();
	Serial.begin(9600);
	Serial.print("Constructing... ");	
	
	// Controller vars
	this->timer = 0;
	this->phase = 0;
	this->interval = 0;
	// iduration = 15000;	
	// pduration = 900000; 15 Minutes
	this->selector = 0;	
	
	// Division sets the strand mode. 1 is regular, 2 is Mirror, 3 is Triangle (not added yet), 4 is Radial.
	this->division = 12;


	//For spectrum analyzer shield, these three pins are used.
	//You can move pinds 4 and 5, but you must cut the trace on the shield and re-route from the 2 jumpers. 
	this->spectrumReset=5;
	this->spectrumStrobe=4;
	this->spectrumAnalog=0;  //0 for left channel, 1 for right.

	// Spectrum analyzer read values will be kept here.
	this->Spectrum[7];
	this->average = 0;
	this->kickThreshold = 0;
	this->snareThreshold = 0;
	this->kick = 0;
	this->snare = 0;

	// Divisor for audio signal scaling ///
	// 22 ~ 80
	// 72 ~ 10
	this->Divisor = 10;

		// //Setup pins to drive the spectrum analyzer. 
		// 	  pinMode(spectrumReset, OUTPUT);
		// 	  pinMode(spectrumStrobe, OUTPUT);
		// 
		// 	  //Init spectrum analyzer
		// 	  digitalWrite(spectrumStrobe,LOW);
		// 	  delay(1);
		// 	  digitalWrite(spectrumReset,HIGH);
		// 	  delay(1);
		// 	  digitalWrite(spectrumStrobe,HIGH);
		// 	  delay(1);
		// 	  digitalWrite(spectrumStrobe,LOW);
		// 	  delay(1);
		// 	  digitalWrite(spectrumReset,LOW);
		// 	  delay(5);
		// 	  // Reading the analyzer now will read the lowest frequency.
	
	

	this->primary = this->RandomWheel();
	this->secondary = this->RandomWheel();
	

	// Phase modifier = phase * 
	// %10
	
	this->test = 0;
	
}
///Do we need deconstructor?

void SoundStrip::render() {   

	this->timer = millis();
	
	Serial.print("Render: ");
	Serial.println(this->timer);
	
	
	if (test == 1) {
		this->PolkadotPulse(RandomWheel(),RandomWheel(),1,100);
		// colorWipe(RandomWheel(),1);
	} else {

  	if (this->timer > this->iduration*this->interval) {
		
		Serial.print("=== Interval "); Serial.print(this->interval); Serial.println(" ===");			
		Serial.print("Timer: ");
		Serial.println(this->timer);
		Serial.print("interval * iduration: ");
		Serial.println(this->interval*this->iduration);		
		
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
		
		Serial.print("selector: "); 	
	 	Serial.println(this->selector);

	}

	
	if (phase < 4) {		
		// if (selector == 0) { Serial.println("Effect: Sparkle"); this->Malfunction(); }
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
		// if (selector == 0) { Serial.println("Effect: Sparkle"); this->Malfunction(); }
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
		// if (selector == 0) { Serial.println("Effect: Sparkle"); this->Malfunction(); }
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

void SoundStrip::rainbowPulse(uint8_t wait)
{
	this->readSpectrum();

  // static unsigned int Divisor = 20;
  unsigned int works,i,j;
	
	int alpha;
	double a;

  for (int s=0;s<7;s++) {			
  	
    for (i=0; i < this->numPixels()/division; i++) {
		  alpha = Spectrum[i%7]/Divisor;
			a = (double)alpha*.01;
      this->q(i, Wheel( ((s * 256 / this->numPixels()) + i) % 256,a) );

			// Serial.print(i%7);
			// 		  Serial.print(" - ");
			// Serial.println(a);
   		
    }  
    this->show();   // write all the pixels out
 		delay(wait);    
  }
}

void SoundStrip::showSpectrum(uint8_t wait)
{
	this->readSpectrum();
	
  	byte Band, BarSize, MaxLevel;
  	static unsigned int  Divisor = 20, ChangeTimer=0;
  	unsigned int works, Remainder;

  	int peak = Spectrum[2]/Divisor;
	int wheel = Spectrum[1]/10;

  	MaxLevel = 0; 

   for (int i=0; i < this->numPixels() / division; i++) {
     if (i <= peak) {
 				mirror(i, Wheel(wheel+(i*5),1)); 
				// this->q(i,Color(0,0,45));
   			// mirror(i, Wheel(random(0,wheel)),1); 
      } else {
		this->q(i, Color(0,0,0));
   		}
   			Serial.println(peak);
   }  
		
  // this->show();
  
  
//    //If value is 0, we don't show anything on graph
//    works = Spectrum[Band]/Divisor;	//Bands are read in as 10 bit values. Scale them down to be 0 - 5
//    if(works > MaxLevel)  //Check if this value is the largest so far.
//      MaxLevel = works;                       
  

  this->show();
  delay(wait);
}

// foreach spectrum pick a color and run an alpha intensity.
void SoundStrip::rainbowSpectrum(uint8_t wait)
{
	readSpectrum();

  // static unsigned int Divisor = 20;
  unsigned int works,i,j;
	
	int alpha;
	double a;
  int peak = Spectrum[1]/Divisor;
	int wheel = Spectrum[1]/20;

  // for (int i=0; i < this->numPixels() / division; i++) {
			

  // for (j=0; j < 256 * 5; j++) {     // 5 cycles of all 25 colors in the wheel
  // for (int s=0;s<7;s++) {  	
    for (i=0; i < this->numPixels()/division; i++) {

		alpha = Spectrum[1]/Divisor;
		a = (double)alpha*.01;

      	this->q(i, Wheel( ((i * 256 / this->numPixels())) % 256,a) );

		Serial.print((this->numPixels()/division)/7);
		Serial.print(" - ");
		Serial.println(a);
   		
    }  
    this->show();   // write all the pixels out
 	delay(wait);    
  // }

// %/100 = x/7 

// 9/18 = x/7			
		  // this->q(i, Wheel((s*5),alpha)); 				


}

void SoundStrip::RainbowLevel(uint8_t wait)
{
	readSpectrum();

  	static unsigned int  Divisor = 20;
  	unsigned int works;

  	int peak = Spectrum[1]/Divisor;
	int wheel = Spectrum[1]/10;

   	for (int i=0; i < this->numPixels() / division; i++) {
     	if (i <= peak) {
			this->q(i, Wheel(wheel+(i*5),1)); 
			// this->q(i,Color(0,0,45));
   			// mirror(i, Wheel(random(0,wheel)),1); 
      	} else {
        	this->q(i, Color(0,0,0));
   		}
   		Serial.println(peak);
   	}  

  	this->show();
  	delay(wait);
}

// fill the dots one after the other with said color
// good for testing purposes
void SoundStrip::colorWipe(uint32_t c, uint8_t wait) {
  int i;
  
  for (i=0; i < this->numPixels()/division; i++) {
      q(i, c);
      this->show();
      delay(wait);
  }
}

// Read 7 band equalizer.
void SoundStrip::readSpectrum()
{
	int display_eq = 1;
	average = 0;

  	byte Band;
  	for(Band=0;Band <7; Band++) {
    	Spectrum[Band] = (analogRead(spectrumAnalog) + analogRead(spectrumAnalog) ) >>1; //Read twice and take the average by dividing by 2
    	digitalWrite(spectrumStrobe,HIGH);
    	digitalWrite(spectrumStrobe,LOW);     
		average += Spectrum[Band];

    	// Serial.print(Spectrum[Band]/80);       
    	// Serial.print(" ");     
  	}

	average = average/7; 	
	// Serial.print(Spectrum[1]);
	// Serial.print(" - ");
	// Serial.print(Spectrum[6]);
	// Serial.print(" - ");
	// Serial.println(average);
	
	if (Spectrum[1] > average) {
		// Serial.print("Kick - "); 
		// Serial.println(Spectrum[1]); 
		kick = 1;
	} else {kick=0;}
	if (Spectrum[6] > average) {
		// Serial.print("Snare - "); 
		// Serial.println(Spectrum[1]); 
		snare = 1;
	} else {snare=0;}

  	// Serial.println(average);
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
	if (division == 1) {
		this->setPixelColor(pos,color);
	} else if (division == 2) {
		// left/right mirror mode.
		mirror(pos,color);
	} else if (division == 4) {
		// Radial Mode
		// radial(pos,color);
	} else if (division == 12) { // Make each panel do the same thing.
		int p;
		for (int i=0;i<this->numPixels()/division;i++) {
			if (i%2) { p = (12*i)+11-(pos); } else { p = (i*12)+(pos); }
			this->setPixelColor(p, color);		
		}
	}			 
}

/*

Position: 0 
0 12 24 36 48 60 72 84 96 108 120 132  
Position: 1 
12 11 36 35 60 59 84 83 108 107 132 131  
Position: 2 
24 10 48 34 72 58 96 82 120 106 144 130  
Position: 3 
36 9 60 33 84 57 108 81 132 105 156 129  
Position: 4 
48 8 72 32 96 56 120 80 144 104 168 128  
Position: 5 
60 7 84 31 108 55 132 79 156 103 180 127  
Position: 6 
72 6 96 30 120 54 144 78 168 102 192 126  
Position: 7 
84 5 108 29 132 53 156 77 180 101 204 125  
Position: 8 
96 4 120 28 144 52 168 76 192 100 216 124  
Position: 9 
108 3 132 27 156 51 180 75 204 99 228 123  
Position: 10 
120 2 144 26 168 50 192 74 216 98 240 122  
Position: 11 
132 1 156 25 180 49 204 73 228 97 252 121  


000 023 024 047 048 060 000 023 000 023 000 023  
001 022 025 046 049 0-- 001 022 001 022 001 022  
002 021 026 045 050 021 002 021 002 021 002 021  
003 020 027 044 051 020 003 020 003 020 003 020  
004 019 028 043 052 019 004 019 004 019 004 019  
005 018 029 042 053 018 005 018 005 018 005 018  
006 017 030 041 054 017 006 017 006 017 006 017  
007 016 031 040 055 016 007 016 007 016 007 016  
008 015 032 039 056 015 008 015 008 015 008 015  
009 014 033 038 057 014 009 014 009 014 009 014  
010 013 034 037 058 013 010 013 010 013 010 013 
011 012 035 036 059 012 011 012 011 012 011 012


*/
