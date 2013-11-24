#include "Adafruit_WS2801.h"
#include "Creamery.h"
#include "TrueRandom.h"
// #include "Easing.h"
#include "Grid.h"

Creamery::Creamery(Grid *g) {
	
	this->grid = g;		

	// defaults
	this->frequency = 900;
	this->sustain = 20;
	this->intensity = 20;
	this->direction = asc;
	this->grid->orientation = horizontal;
	this->last_execution = 0;

	// // Setup some base colors variables to use for things like polkadot
	// this->primary = this->RandomWheel();
	// this->secondary = this->RandomWheel();
	// this->tertiary = this->RandomWheel();
	
}

void Creamery::step() {   
	
}

void Creamery::singlePulseWipe(uint32_t c, uint16_t dir, uint16_t f, uint16_t wait) {
	int i;
		
	for(i=0; i<this->grid->getTotal();i++)
	{
		singlePulse(i,c,f,wait);
	}
	
}

// We need an effect that hits just one panel
// Pixel, Color, Sust, Speed
void Creamery::singlePulse(uint8_t n,uint32_t c, uint16_t f, uint16_t wait) {
	// Make sure if you are trying to hit a whole panel, you set the orientation and mode of grid.	
	
	int i;
  	double alpha;
  
	for(alpha=0;alpha<1;alpha=alpha+0.01) {
		grid->q(n, this->Color(c,alpha));
		 this->grid->show();
	    delay(wait);	   
	}

	// Sustain...
	delay(f);	

	for(alpha=1;alpha>0;alpha=alpha-0.01) {
		grid->q(n, this->Color(c,alpha));
		 this->grid->show();
	    delay(wait);	   
	}
	
	// FadeOut(wait);
	
}

// Pixels, Color, Sust, Speed
void Creamery::nPulse(uint8_t n,uint32_t c, uint16_t f, uint16_t wait) {
	// Make sure if you are trying to hit a whole panel, you set the orientation and mode of grid.	
	
	int i,j,p;
  	double alpha;
	uint8_t u[n];
  	
	for(i=0;i<n;i++) {
		
		
		u[i] = TrueRandom.random(0,this->grid->getTotal()-1);
		
		Serial.print("Pixel: ");
		Serial.println(u[i]);
		// delay(1000);
			
		for (j=0;j<i;j++) {
			if (u[j] == u[i]) {

				Serial.print("Resetting from collision: ");
				Serial.println(j);
				// delay(1000);
				
				u[i] = TrueRandom.random(0,this->grid->getTotal()-1);
				j = 0;
			}			
		}
		
		for(alpha=0;alpha<1;alpha=alpha+0.01) {
			grid->q(u[i], this->Color(c,alpha));
			 this->grid->show();
		    delay(wait);	   
		}
		
		c = RandomWheel();
		Serial.print("Color: ");
		Serial.println(c);
		delay(wait);
		
		// Sustain...

	}


	delay(f);
	
	FadeOut(wait);

	// 
	// for(alpha=1;alpha>0;alpha=alpha-0.01) {
	// 	grid->q(n, this->Color(c,alpha));
	// 	 this->grid->show();
	//     delay(wait);	   
	// }	
	
	
}

//Nuff said, only duration, not speed can be set (made this 15 minutes before you took my balls.)
void Creamery::strobe(uint8_t runs){
  int i;
  int r;
  int total = this->grid->getTotal();
  for(r=0;r<runs;r++) {
     for(i=0;i<total;i++){
       this->grid->q(i, this->rgba(255,255,255,0.2));
     }
     this->grid->show();
     delay(25);
     
     for(i=0;i<total;i++){
       this->grid->q(i, this->Color(0,0,0));
     }
     this->grid->show();
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


void Creamery::PolkadotCycle(uint32_t c, uint32_t d, uint32_t wait) {

  for (int j=0; j < 256 * 5; j++) {     // 5 cycles of all 25 colors in the wheel
    for (int i=0; i < this->grid->getTotal(); i++) {

			if ((i%2)==0) {
	        	grid->q(i, c);
	      	} else {
	        	grid->q(i, d);      
	      	}
	    }
			
      // grid->q(i, this->Wheel( ((i * 256 / this->grid->getTotal()) + j) % 256) );
    }  
    this->grid->show();   // write all the pixels out
    delay(wait);
	
}

// Usage:
// polkadots(Color(255,0,255),Color(0,255,255), 50);
void Creamery::polkadotFill(uint32_t c, uint32_t d, uint32_t wait) {
  int i;
  
  for (i=0; i < this->grid->getTotal(); i++) {
      
      if ((i%2)==0) {
        this->grid->q(i, c);
      } else {
        this->grid->q(i, d);      
      }
  }
  this->grid->show();
  delay(wait);  
}  

void Creamery::PolkadotPulse(uint32_t c, uint32_t d, uint32_t wait, uint8_t sustain) {
  
  	int i;
  	double alpha;
  	int total = this->grid->getTotal();
  
	for(alpha=0;alpha<1;alpha=alpha+0.01) {
	    for(i=0;i<total;i++)  {
			if ((i%2)==0) {
	        	grid->q(i, this->Color(c,alpha));
	      	} else {
	        	grid->q(i, this->Color(d,alpha));      
	      	}
	    }
	    this->grid->show();
	    delay(wait);
  	}
  	// this->grid->show();
	
	delay(sustain);	
	FadeOut(wait);
	// for(alpha=1;alpha>0;alpha=alpha-0.01) {
	//       	if ((i%2)==0) {
	//        		this->grid->q(i, this->Color(c,alpha));
	//      	} else {
	//        		this->grid->q(i, this->Color(d,alpha));      
	//      	}
	//     	this->grid->show();
	//     	delay(wait);
	//   	}
  	// this->grid->show();

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

/// /Builds a sparkle faster and then slows it down./
// void Creamery::FasterSlower(){
//   SparkleFaster(500);
//   SparkleSlower(500);
// }

void Creamery::RainbowPulse(uint32_t wait) {
	
	int i;
	for(i=0;i<255;i+=23) { 	
		this->ColorPulse(Wheel(i),wait);				
	}
}

void Creamery::ColorPulse(uint32_t color,uint32_t wait) {
   	FadeInAll(color, wait);	
   	FadeOutAll(color, wait);
	// delay(wait);
}

//
// THIS STUFF IS USEFUL!!!!!
//

void Creamery::FadeInOutWhite(uint32_t wait){
   FadeInAll(Color(255,255,255), wait);
   FadeOutAll(Color(255,255,255), wait);
}

void Creamery::FadeInOutRandom(uint32_t wait){
	uint32_t color = RandomColor();
   	FadeInAll(color, wait);
    FadeOutAll(color, wait);
}

void Creamery::FadeInAll(uint32_t color, uint32_t wait){
  int i;
  double alpha;
  int total = this->grid->getTotal();
  
  for(alpha=0;alpha<1;alpha=alpha+0.01) {
    for(i=0;i<total;i++)  {
       this->grid->q(i, this->Color(color,alpha)); 
    }
    this->grid->show();
    delay(wait);
  }
  this->grid->show();
}

void Creamery::FadeOutAll(uint32_t color, uint32_t wait){
  int i;
  double alpha;
  int total = this->grid->getTotal();
  
  for(alpha=1;alpha>0;alpha=alpha-0.01) {
    for(i=0;i<total;i++)  {
       this->grid->q(i,this->Color(color,alpha)); 
    }
    this->grid->show();
    delay(wait);
  }
  this->grid->show();
}

void Creamery::FadeInSparkles(uint32_t color, uint32_t wait){
  int i;
  double alpha;
  int total = this->grid->getTotal();
  
  for(alpha=0;alpha<0.25;alpha=alpha+0.01) {
    for(i=0;i<total;i++)  {
      Sparkle(this->Wheel(color,alpha), TrueRandom.random(1,25), 25);
    }
    this->grid->show();
    delay(wait);
  }
  this->grid->show();
}

void Creamery::FadeOutSparkles(uint8_t r, uint8_t g, uint8_t b, uint32_t wait){
  int i;
  double alpha;
  int total = this->grid->getTotal();
  
  for(alpha=0.25;alpha>0;alpha=alpha-0.01) {
    for(i=0;i<total;i++)  {
       Sparkle(this->rgba(r,g,b,alpha), TrueRandom.random(1,25), 25);
    }
    this->grid->show();
    delay(wait);
  }
  this->grid->show();
}

//This is the exact same thing as Sparkle except with random colors.

void Creamery::SparkleRainbow(uint8_t density, uint32_t wait){
    int total=this->grid->getTotal();
    int r; 
    int i;
    int pixel; 

  //Set all pixels to bg
  for(i=0; i < this->grid->getTotal(); i++ ) {
    //Set color
    this->grid->q(i, this->Color(0,0,0));
  }
//  update Lights
  this->grid->show();
  
  //Pick at random x number of times (x = density)
  for( r=0; r < density; r++ )  {
    //Pick pixel
   pixel = TrueRandom.random(1,total);
	this->grid->q(pixel, this->RandomWheel());
   // this->grid->q(pixel, this->Color(this->R(0,255), this->R(0,255), this->R(0,255)));
  }
  //Update lights
  this->grid->show();
  
  delay(wait);
 //
}

void Creamery::DoubleRainbowSparkle(uint8_t density, uint32_t wait, uint8_t sustain){
	int i;

	for (i=1;i<255;i++) {
		this->Sparkle(RandomWheel(), density, wait, sustain, Wheel(i));
	}
}

//3 Parameter SPARKLE
void Creamery::Sparkle(uint32_t color, uint8_t density, uint32_t wait){
	// Serial.println("Running Sparkle");
    int total=this->grid->getTotal();
    int r; 
    int i;
    int pixel; 

  //Set all pixels to bg
  for(i=0; i < this->grid->getTotal(); i++ ) {
    //Set color
    this->grid->q(i, this->Color(0,0,0));
  }
//  update Lights
  this->grid->show();
  
  //Pick at random x number of times (x = density)
  for( r=0; r < density; r++ )  {
    //Pick pixel
   pixel = TrueRandom.random(1,total);
   this->grid->q(pixel, color);
  }
  //Update lights
  this->grid->show();
  
  delay(wait);
 //
}

//5 Parameter SPARKLE
void Creamery::Sparkle(uint32_t color, uint8_t density, uint32_t wait, uint8_t sustain, uint32_t bg){
	int total=this->grid->getTotal();
	int r; 
	int i;
	int pixel; 

  	//Set all pixels to bg
  	for(i=0; i < this->grid->getTotal(); i++ ) {
    	//Set color
    	this->grid->q(i, bg);
  	}
  	delay(wait);
  //  update Lights
  this->grid->show();
  
  //Pick at random x number of times (x = density)
  for( r=0; r < density; r++ )  {
    //Pick pixel
   pixel = TrueRandom.random(1,total);
   this->grid->q(pixel, color);
  }
  //Update lights
  this->grid->show();
  
  delay(sustain);
 //
}

void Creamery::SparkleFill(uint32_t color, uint8_t density, uint32_t wait){
  int total=this->grid->getTotal();
  int r; 
  int i;
  int pixel; 
  
  //Pick at random x number of times (x = density)
  for( r=0; r < density; r++ )  {
    // Pick pixel
   pixel = TrueRandom.random(1,total);
   this->grid->q(pixel, color);
  }
  //Update lights
  this->grid->show();
  
  delay(wait);
}

// void Creamery::SparkleFaster(uint8_t duration){
//   int go;
//   for(go=0;go<100;go++) {
//     this->SinglePixel( Easing::easeOutSine(go, 80, 0, duration) );
//   }
// }

// void Creamery::SparkleSlower(uint8_t duration){
//   int go;
//   for(go=0;go<100;go++) {
//     this->SinglePixel( Easing::easeInSine(go, 0, 80, duration) );
//   }
// }

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
  for(i=0;i<this->grid->getTotal();i++) { this->grid->q(i, COLOR); }
  this->grid->show();
  delay(DELAY/2);
  for(i=0;i<this->grid->getTotal();i++) { this->grid->q(i, this->Color(0,0,0)); }
  this->grid->show();
  delay(DELAY/2);
}

void Creamery::rainbow(uint32_t wait) {
  int i, j;
   
  for (j=0; j < 256; j++) {     // 3 cycles of all 256 colors in the wheel
    for (i=0; i < this->grid->getTotal(); i++) {
      grid->q(i, this->Wheel( (i + j) % 255));
    }  
    this->grid->show();   // write all the pixels out
    delay(wait);
  }
}

void Creamery::rainbowStrobe(uint32_t wait) {
  	int i, j;
   
    for (i=0; i < this->grid->getTotal(); i++) {
      grid->q(i, RandomWheel());
    }  
    this->grid->show();   // write all the pixels out
    delay(wait);
}


// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void Creamery::rainbowCycle(uint32_t wait) {
  int i, j;
  
  for (j=0; j < 256 * 5; j++) {     // 5 cycles of all 25 colors in the wheel
    for (i=0; i < this->grid->getTotal(); i++) {
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / this->grid->getTotal() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      grid->q(i, this->Wheel( ((i * 256 / this->grid->getTotal()) + j) % 256) );
    }  
    this->grid->show();   // write all the pixels out
    delay(wait);
  }
	// FadeOut(20);
}

// fill the dots one after the other with said color
// good for testing purposes
void Creamery::colorWipe(uint32_t c,uint32_t d,uint32_t wait) {
  	int i;  

	// Serial.println("Beginning Effect ColorWipe...");

	// Serial.print("--- ");Serial.println(wait);

	if (d == desc) {
		// Descending
		for (i=0; i<this->grid->getTotal(); i++) {		
			this->grid->q(i, c);
			this->grid->show();
			delay(wait);
	  	}
			
	} else {
		// Ascending
		for (i=this->grid->getTotal();i>=0;i--) {			
			this->grid->q(i, c);
			this->grid->show();
			delay(wait);
	  	}
	  	
	}

	
	
}
// // fill the dots one after the other with said color
// // good for testing purposes
// void Creamery::colorWipe(uint32_t c, uint32_t wait) {
//   int i;
//   
//   for (i=0; i < this->grid->getTotal(); i++) {
//       grid->q(i, c);
//       this->grid->show();
//       delay(wait);
//   }
// }

// fill the entire strip with said color
// good for testing purposes
void Creamery::colorFill(uint32_t c) {
  int i;
  
  for (i=0; i < this->grid->getTotal(); i++) {
      grid->q(i, c);
  }
  this->grid->show();
}

/* Transition functions */
bool Creamery::trans(uint16_t i, uint32_t newcolor, uint32_t wait) {
	
	// rgb = current, nrgb = new, trgb = transition.
	bool rflag,gflag,bflag=false;
	uint8_t r,g,b,nr,ng,nb;
	uint32_t c = this->grid->getPixelColor(i);	
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
	
	this->grid->q(i,Color(r,g,b));
	this->grid->show();
	
	return false;
	
}	
void Creamery::FadeOut(uint32_t wait) {
  int i;
  double alpha;
  int total = this->grid->getTotal();

  for(alpha=1;alpha>0;alpha=alpha-0.01) {
    for(i=0;i<total;i++)  {
       this->grid->q(i,this->Color(this->grid->getPixelColor(i),alpha)); 
    }
    this->grid->show();
    delay(wait);
  }
  this->grid->show();

}

/* Helper functions */

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
uint32_t Creamery::Color(byte r, byte g, byte b, double a) {
	int rr = r*a;
	int gg = g*a;
	int bb = b*a;

	return this->Color(rr,gg,bb);
}

// Create a 24 bit color value from R,G,B
uint32_t Creamery::Color(byte r, byte g, byte b) {
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
uint32_t Creamery::Wheel(byte WheelPos) {
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
uint32_t Creamery::Wheel(byte WheelPos, double alpha) {
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
