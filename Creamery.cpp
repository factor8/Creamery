#include "Adafruit_WS2801.h"
#include "Creamery.h"
#include "TrueRandom.h"
#include "Easing.h"

Creamery::Creamery(uint16_t n, uint8_t dpin, uint8_t cpin, uint8_t order) : Adafruit_WS2801(n, dpin, cpin, order) {
	
	// this->total = this->numPixels();
	
	// Controller vars
	this->timer = 0;
	this->phase = 0;
	this->interval = 0;
	this->selector = 0;	
	
	// Grid vars
	this->division = 12;
	
	// Setup some base colors variables to use for things like polkadot
	this->primary = this->RandomWheel();
	this->secondary = this->RandomWheel();
	this->tertiary = this->RandomWheel();
	
}
///Do we need deconstructor?

void Creamery::render() {   

	this->timer = millis();
	
	if (test == 1) {

		// ON/OFF Test
		// colorFill(Color(5,0,0));
		// colorFill(rgba(200,255,255,1));
		// delay(4000);
		// colorFill(Color(0,0,0)); 
		// delay(1200);					
		
		rainbowCycle(10);
		
		// primary = this->Wheel(TrueRandom.random(0,255));
		// secondary = this->Wheel(TrueRandom.random(0,255));
				
		// this->RainbowPulse(1);
		// this->Malfunction();
		// this->ButterflyEffect();
		
		// Attempt at Inverted Sparkle
		// uint32_t color = RandomWheel();

		// for (i=1;i<105;i++) {
		// 	// for (i=1;i<255;i++) {
		// 		this->Sparkle(Color(0,0,0), i, 10, 50, color);
		// 	// }			
		// }

		// this->rainbowStrobe(5);
		
		// FadeOut(1);
		
		// this->polkadotFill(primary,secondary,1000);
		// this->FadeInOutWhite(50);
		// this->FadeInOutRandom(40);
		// this->RainbowPulse(10);
		// this->SparkleRainbow(20,10);
		
		// this->setPixelColor(01,Color(255,255,255));
		// this->show();
		
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

//Nuff said, only duration, not speed can be set (made this 15 minutes before you took my balls.)
void Creamery::strobe(uint8_t runs){
  int i;
  int r;
  int total = this->numPixels();
  for(r=0;r<runs;r++) {
     for(i=0;i<total;i++){
       this->setPixelColor(i, this->rgba(255,255,255,0.2));
     }
     this->show();
     delay(25);
     
     for(i=0;i<total;i++){
       this->setPixelColor(i, this->Color(0,0,0));
     }
     this->show();
     delay(100);
  }
}

// Butterfly Effect 
void Creamery::ButterflyEffect() {
	int i;
	for (i=1;i<255;i++) {
		this->Sparkle(Color(0,0,0), 1, 10, 50, Wheel(i));
	}
}

// Malfunction-like effect with blanks and color;
void Creamery::Malfunction() {
	int i;
	for (i=1;i<255;i++) {
		if (i%2) {
			this->Sparkle(Color(0,0,0), 10, 10, 100, Wheel(i));
		} else {	
			this->Sparkle(RandomWheel(), 10, 10, 10, Wheel(i));
		}	
	}
}


void Creamery::PolkadotCycle(uint32_t c, uint32_t d, uint8_t wait) {

  for (int j=0; j < 256 * 5; j++) {     // 5 cycles of all 25 colors in the wheel
    for (int i=0; i < this->numPixels()/division; i++) {

			if ((i%2)==0) {
	        	this->q(i, c);
	      	} else {
	        	this->q(i, d);      
	      	}
	    }
			
      // this->q(i, this->Wheel( ((i * 256 / this->numPixels()) + j) % 256) );
    }  
    this->show();   // write all the pixels out
    delay(wait);
	
}

// Usage:
// polkadots(Color(255,0,255),Color(0,255,255), 50);
void Creamery::polkadotFill(uint32_t c, uint32_t d, uint8_t wait) {
  int i;
  
  for (i=0; i < this->numPixels(); i++) {
      
      if ((i%2)==0) {
        this->setPixelColor(i, c);
      } else {
        this->setPixelColor(i, d);      
      }
  }
  this->show();
  delay(wait);  
}  

void Creamery::PolkadotPulse(uint32_t c, uint32_t d, uint8_t wait, uint8_t sustain) {
  
  	int i;
  	double alpha;
  	int total = this->numPixels()/division;
  
	for(alpha=0;alpha<1;alpha=alpha+0.01) {
	    for(i=0;i<total;i++)  {
			if ((i%2)==0) {
	        	this->q(i, this->Color(c,alpha));
	      	} else {
	        	this->q(i, this->Color(d,alpha));      
	      	}
	    }
	    this->show();
	    delay(wait);
  	}
  	// this->show();
	
	delay(sustain);	
	FadeOut(0);
	// for(alpha=1;alpha>0;alpha=alpha-0.01) {
	//       	if ((i%2)==0) {
	//        		this->setPixelColor(i, this->Color(c,alpha));
	//      	} else {
	//        		this->setPixelColor(i, this->Color(d,alpha));      
	//      	}
	//     	this->show();
	//     	delay(wait);
	//   	}
  	// this->show();

}

//Builds up a white sparkle, and then does a random sparkle for colors. 
void Creamery::SparkleChaos1(){
  int go = 0;
  int density = 1;
  for(go=0;go<255;go++) { 
    if(go>50) { density = 2; }
    else if(go>100) {density = 3; }
    else if(go>150) {density = 4; }
    else if(go > 200) {density = 5; }
    else if(go > 225) { density = 7; }
    Sparkle(Color(go,go,go), density, 0); 
    delay(10);
  }
  	for(go=0;go<100;go++) { SparkleRandom(); } 
  	
	FadeOut(10);
}




//Builds a sparkle faster and then slows it down./
void Creamery::FasterSlower(){
  SparkleFaster(500);
  SparkleSlower(500);
}

void Creamery::RainbowPulse(uint8_t wait) {
	
	int i;
	for(i=0;i<255;i+=23) { 	
		this->ColorPulse(Wheel(i),wait);				
	}
}

void Creamery::ColorPulse(uint32_t color,uint8_t wait) {
   	FadeInAll(color, wait);	
   	FadeOutAll(color, wait);
	// delay(wait);
}

//
//
//
// THIS STUFF IS USEFUL!!!!!
//

void Creamery::FadeInOutWhite(uint8_t wait){
   FadeInAll(Color(255,255,255), wait);
   FadeOutAll(Color(255,255,255), wait);
}

void Creamery::FadeInOutRandom(uint8_t wait){
	uint32_t color = RandomColor();
   	FadeInAll(color, wait);
    FadeOutAll(color, wait);
}

void Creamery::FadeInAll(uint32_t color, uint8_t wait){
  int i;
  double alpha;
  int total = this->numPixels();
  
  for(alpha=0;alpha<1;alpha=alpha+0.01) {
    for(i=0;i<total;i++)  {
       this->setPixelColor(i, this->Color(color,alpha)); 
    }
    this->show();
    delay(wait);
  }
  this->show();
}

void Creamery::FadeOutAll(uint32_t color, uint8_t wait){
  int i;
  double alpha;
  int total = this->numPixels();
  
  for(alpha=1;alpha>0;alpha=alpha-0.01) {
    for(i=0;i<total;i++)  {
       this->setPixelColor(i,this->Color(color,alpha)); 
    }
    this->show();
    delay(wait);
  }
  this->show();
}

void Creamery::FadeInSparkles(uint32_t color, uint8_t wait){
  int i;
  double alpha;
  int total = this->numPixels();
  
  for(alpha=0;alpha<0.25;alpha=alpha+0.01) {
    for(i=0;i<total;i++)  {
      Sparkle(this->Wheel(color,alpha), TrueRandom.random(1,25), 25);
    }
    this->show();
    delay(wait);
  }
  this->show();
}

void Creamery::FadeOutSparkles(uint8_t r, uint8_t g, uint8_t b, uint8_t wait){
  int i;
  double alpha;
  int total = this->numPixels();
  
  for(alpha=0.25;alpha>0;alpha=alpha-0.01) {
    for(i=0;i<total;i++)  {
       Sparkle(this->rgba(r,g,b,alpha), TrueRandom.random(1,25), 25);
    }
    this->show();
    delay(wait);
  }
  this->show();
}

//This is the exact same thing as Sparkle except with random colors.

void Creamery::SparkleRainbow(uint8_t density, uint8_t wait){
    int total=this->numPixels();
    int r; 
    int i;
    int pixel; 

  //Set all pixels to bg
  for(i=0; i < this->numPixels(); i++ ) {
    //Set color
    this->setPixelColor(i, this->Color(0,0,0));
  }
//  update Lights
  this->show();
  
  //Pick at random x number of times (x = density)
  for( r=0; r < density; r++ )  {
    //Pick pixel
   pixel = TrueRandom.random(1,total);
	this->setPixelColor(pixel, this->RandomWheel());
   // this->setPixelColor(pixel, this->Color(this->R(0,255), this->R(0,255), this->R(0,255)));
  }
  //Update lights
  this->show();
  
  delay(wait);
 //
}

void Creamery::DoubleRainbowSparkle(uint8_t density, uint8_t wait, uint8_t sustain){
	int i;

	for (i=1;i<255;i++) {
		this->Sparkle(RandomWheel(), density, wait, sustain, Wheel(i));
	}
}

//3 Parameter SPARKLE
void Creamery::Sparkle(uint32_t color, uint8_t density, uint8_t wait){
    int total=this->numPixels();
    int r; 
    int i;
    int pixel; 

  //Set all pixels to bg
  for(i=0; i < this->numPixels(); i++ ) {
    //Set color
    this->setPixelColor(i, this->Color(0,0,0));
  }
//  update Lights
  this->show();
  
  //Pick at random x number of times (x = density)
  for( r=0; r < density; r++ )  {
    //Pick pixel
   pixel = TrueRandom.random(1,total);
   this->setPixelColor(pixel, color);
  }
  //Update lights
  this->show();
  
  delay(wait);
 //
}

//5 Parameter SPARKLE
void Creamery::Sparkle(uint32_t color, uint8_t density, uint8_t wait, uint8_t sustain, uint32_t bg){
    int total=this->numPixels();
    int r; 
    int i;
    int pixel; 

  //Set all pixels to bg
  for(i=0; i < this->numPixels(); i++ ) {
    //Set color
    this->setPixelColor(i, bg);
  }
  delay(wait);
  //  update Lights
  this->show();
  
  //Pick at random x number of times (x = density)
  for( r=0; r < density; r++ )  {
    //Pick pixel
   pixel = TrueRandom.random(1,total);
   this->setPixelColor(pixel, color);
  }
  //Update lights
  this->show();
  
  delay(sustain);
 //
}

void Creamery::SparkleFill(uint32_t color, uint8_t density, uint8_t wait){
  int total=this->numPixels();
  int r; 
  int i;
  int pixel; 
  
  //Pick at random x number of times (x = density)
  for( r=0; r < density; r++ )  {
    // Pick pixel
   pixel = TrueRandom.random(1,total);
   this->setPixelColor(pixel, color);
  }
  //Update lights
  this->show();
  
  delay(wait);
}

void Creamery::SparkleFaster(uint8_t duration){
  int go;
  for(go=0;go<100;go++) {
    this->SinglePixel( Easing::easeOutSine(go, 80, 0, duration) );
  }
}

void Creamery::SparkleSlower(uint8_t duration){
  int go;
  for(go=0;go<100;go++) {
    this->SinglePixel( Easing::easeInSine(go, 0, 80, duration) );
  }
}

void Creamery::SinglePixel(uint8_t DELAY){
 this->Sparkle(this->Color(255,255,255), 1, DELAY);
}

void Creamery::CrazyPixel(uint32_t COLOR){
  this->Sparkle(COLOR, 4, 1);
}

void Creamery::SparkleRandom(){  
  int COLOR = this->Color(TrueRandom.random(0,255), TrueRandom.random(0,255), TrueRandom.random(0,255));
  int DENSITY = TrueRandom.random(1,30);
  int DELAY = TrueRandom.random(25,160);
  
  this->Sparkle(COLOR, DENSITY, DELAY);  
}

void Creamery::ColorJump(uint8_t DELAY){
  int i;
  uint32_t COLOR;
  COLOR = this->RandomColor();
  for(i=0;i<this->numPixels();i++) { this->setPixelColor(i, COLOR); }
  this->show();
  delay(DELAY/2);
  for(i=0;i<this->numPixels();i++) { this->setPixelColor(i, this->Color(0,0,0)); }
  this->show();
  delay(DELAY/2);
}

void Creamery::rainbow(uint8_t wait) {
  int i, j;
   
  for (j=0; j < 256; j++) {     // 3 cycles of all 256 colors in the wheel
    for (i=0; i < this->numPixels()/division; i++) {
      this->q(i, this->Wheel( (i + j) % 255));
    }  
    this->show();   // write all the pixels out
    delay(wait);
  }
}

void Creamery::rainbowStrobe(uint8_t wait) {
  	int i, j;
   
    for (i=0; i < this->numPixels()/division; i++) {
      this->q(i, RandomWheel());
    }  
    this->show();   // write all the pixels out
    delay(wait);
}


// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void Creamery::rainbowCycle(uint8_t wait) {
  int i, j;
  
  for (j=0; j < 256 * 5; j++) {     // 5 cycles of all 25 colors in the wheel
    for (i=0; i < this->numPixels()/division; i++) {
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / this->numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      this->q(i, this->Wheel( ((i * 256 / this->numPixels()) + j) % 256) );
    }  
    this->show();   // write all the pixels out
    delay(wait);
  }
}

// fill the dots one after the other with said color
// good for testing purposes
void Creamery::colorWipe(uint32_t c, uint8_t wait) {
  int i;
  
  for (i=0; i < this->numPixels()/division; i++) {
      this->q(i, c);
      this->show();
      delay(wait);
  }
}

// fill the entire strip with said color
// good for testing purposes
void Creamery::colorFill(uint32_t c) {
  int i;
  
  for (i=0; i < this->numPixels(); i++) {
      this->q(i, c);
  }
  this->show();
}

/* Transition functions */
bool Creamery::trans(uint16_t i, uint32_t newcolor, uint8_t wait) {
	
	// rgb = current, nrgb = new, trgb = transition.
	bool rflag,gflag,bflag=false;
	uint8_t r,g,b,nr,ng,nb;
	uint32_t c = this->getPixelColor(i);	
	r = extractRed(c);
	g = extractGreen(c);
	b = extractBlue(c);

	nr = extractRed(newcolor);
	ng = extractGreen(newcolor);
	nb = extractBlue(newcolor);
	
	Serial.print("Current:");Serial.print(r);Serial.print(" ");Serial.print(g);Serial.print(" ");Serial.println(b);
	Serial.print("    New:");Serial.print(nr);Serial.print(" ");Serial.print(ng);Serial.print(" ");Serial.println(nb);
	Serial.print("  Flags:");Serial.print(rflag);Serial.print(" ");Serial.print(gflag);Serial.print(" ");Serial.println(bflag);
	
	if (nr < r) {
		r--;
	} else if (nr > r) {
		r++;
	} else {
		rflag = true;
	}
	if (ng < g) {
		g--;
	} else if (ng > g) {
		g++;
	} else {
		gflag = true;
	}
	if (nb < b) {
		b--;
	} else if (nb > b) {
		b++;
	} else {
		bflag = true;
	}
	
	if (rflag && gflag && bflag) { return true; }
	
	this->setPixelColor(i,Color(r,g,b));
	this->show();
	
	return false;
	
}	
void Creamery::FadeOut(uint8_t wait) {
  int i;
  double alpha;
  int total = this->numPixels();

  for(alpha=1;alpha>0;alpha=alpha-0.01) {
    for(i=0;i<total;i++)  {
       this->setPixelColor(i,this->Color(this->getPixelColor(i),alpha)); 
    }
    this->show();
    delay(wait);
  }
  this->show();

}

/* Helper functions */

// "Queue" method to translate pixel positions for standard, mirrored, and radial modes.
void Creamery::q(int pos, uint32_t color) {		
	if (division == 1) {
		this->setPixelColor(pos,color);
	} else if (division == 2) {
		// left/right mirror mode.
		// mirror(pos,color);
	} else if (division == 4) {
		// Radial Mode
		// radial(pos,color);
	} else if (division == 12) { // Make each panel do the same thing.
		int p,i;
		for (i=0 ;i<this->numPixels()/division;i++) {
			p = (i%2) ? p = (12*i)+11-(pos) : p = (i*12)+(pos);
			this->setPixelColor(p, color);		
		}
	}			 
}

//Shorter random function, static helper. 
uint8_t Creamery::R(uint8_t from, uint8_t to){
 return TrueRandom.random(from, to);
} 

uint32_t Creamery::RandomColor(){
   return this->Color(TrueRandom.random(0,255), TrueRandom.random(0,255), TrueRandom.random(0,255));
}

uint32_t Creamery::RandomWheel() {	
	return Wheel(TrueRandom.random(0,255)%255);		
}

uint32_t Creamery::rgba(byte r, byte g, byte b, double a) {
	int rr = r*a;
	int gg = g*a;
	int bb = b*a;

	return this->Color(rr,gg,bb);
}

// Create a 24 bit color value from R,G,B
uint32_t Creamery::Color(byte r, byte g, byte b, double a)
{
	int rr = r*a;
	int gg = g*a;
	int bb = b*a;

	return this->Color(rr,gg,bb);
}

// Create a 24 bit color value from R,G,B
uint32_t Creamery::Color(byte r, byte g, byte b)
{
	uint32_t c;
	c = r;
	c <<= 8;
	c |= g;
	c <<= 8;  
	c |= b;
	
  	return c;
}
uint32_t Creamery::Color(uint32_t c, double a) {
	
	uint8_t r = extractRed(c);
	uint8_t g = extractGreen(c);
	uint8_t b = extractBlue(c);
		
	return rgba(r,g,b,a);
}

uint32_t Creamery::alpha(uint32_t c, double a) {
	
	uint8_t r = extractRed(c);
	uint8_t g = extractGreen(c);
	uint8_t b = extractBlue(c);
		
	return rgba(r,g,b,a);
}

// Helpers to extract RGB from 32bit color. (Woohoo!!)
uint8_t Creamery::extractRed(uint32_t c) { return (( c >> 16 ) & 0xFF); } 
uint8_t Creamery::extractGreen(uint32_t c) { return ( (c >> 8) & 0xFF ); } 
uint8_t Creamery::extractBlue(uint32_t c) { return ( c & 0xFF ); }

//Input a value 0 to 255 to get a color value.
//The colours are a transition r - g -b - back to r
uint32_t Creamery::Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
   return this->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
   WheelPos -= 85;
   return this->Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170; 
   return this->Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
// This is Wheel with alpha.
uint32_t Creamery::Wheel(byte WheelPos, double alpha)
{
  if (WheelPos < 85) {
   return this->rgba(WheelPos * 3, 255 - WheelPos * 3, 0,alpha);
  } else if (WheelPos < 170) {
   WheelPos -= 85;
   return this->rgba(255 - WheelPos * 3, 0, WheelPos * 3,alpha);
  } else {
   WheelPos -= 170; 
   return this->rgba(0, WheelPos * 3, 255 - WheelPos * 3,alpha);
  }
}
