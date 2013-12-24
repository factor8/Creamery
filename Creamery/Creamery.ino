#include <SPI.h>
#include <Adafruit_WS2801.h>
#include <TrueRandom.h>

#define	DATAPIN		2 // Data pin for serial communication to shift registers
#define	CLOCKPIN	3 // Clock pin for serial communication to shift registers

// Grid DEF & Vars
#define panelsX 1
#define panelsY 18
#define pixelsX 1
#define pixelsY 1
#define pixelsTotal 18

// Instantiate Controller. Num Pix Automatically Generated.
Adafruit_WS2801* strip = new Adafruit_WS2801(pixelsTotal, DATAPIN, CLOCKPIN);

// Alignment,Direction,Pattern Enumeration
enum {asc,desc,		horizontal,vertical,	strand,panel,mirrored};

uint16_t orientation = vertical;
uint16_t direction = desc;

// nodeTimeStamps becomes colorPallette
uint32_t colors[pixelsTotal];
uint32_t colors_future[pixelsTotal];
uint8_t color_start[pixelsTotal][3]; // transition arrays. /// super testing
uint8_t color_end[pixelsTotal][3];
char increments[pixelsTotal][3];

boolean DEBUG = 0; // Flag for debugging.
uint8_t verbose = 0; // Flag for verbose debugging.
boolean eflag = 1; // flag so that we can trigger only once per effect.
boolean will_transition = 1;
boolean transitioning = 0;
boolean updateInterval = 1;

// CTRL Vars 
long 
	now,
	then,
	iduration,
	pduration;

uint16_t /// set defaults
	iter,
	itermax,
	interval,
	intervalCount,
	frequency,
	sustain,
	density,
	decay,
	phase,
	selector,
	mode;

uint16_t transition_steps = 32;

uint32_t 
	primary,
 	secondary,
 	tertiary;


// fill the dots one after the other with said color
// good for testing purposes
void flavorWipe() {

	if (DEBUG && eflag) {Serial.println("Beginning Effect flavorWipe...");eflag=0;}

	itermax = pixelsTotal;

	q(iter, primary);

}
void flavorFill() {
	if (DEBUG && eflag) {Serial.println("Beginning Effect flavorFill...");eflag=0;}
	for (int i=0; i < pixelsTotal; i++) {
		q(i, primary);
  }
}
void rainbow() {
	if (DEBUG && eflag) {Serial.println("Beginning Effect rainbow...");eflag=0;}
	frequency = 200; /// unhardcode
	itermax = 255;

  for (int i=0; i < pixelsTotal; i++) {
		q(i, Wheel( (iter) % 255));
  }  
}

void rainbowCycle() {
	if (DEBUG && eflag) {Serial.println("Beginning Effect rainbowCycle...");eflag=0;}

	frequency = 20; /// unhardcode
	itermax = 255;

	for (int i=0; i < pixelsTotal; i++) {
		// tricky math! we use each pixel as a fraction of the full 96-color wheel
		// (thats the i / strip.numPixels() part)
		// Then add in j which makes the color go around per pixel
		// the % 96 is to make the wheel cycle around
		q(i, Wheel( ((i * 256 / pixelsTotal) + iter) % 256) );
	}
}

void sparkle(){
	if (DEBUG && eflag) {Serial.println("Beginning Effect sparkle...");eflag=0;}

	uint32_t bg = secondary;
	
	/*//// We need to account for sustain and frequency for this...
		frequency would need to be short short and then checked inside this loop
		then decay is used to determine the overall division of fade out...

		setup an array for the pixels that are 'active'?
	*/
	
	int pos; 

	//Set all pixels to bg
	for(int i=0; i < pixelsTotal; i++ ) {
		//Set color
		q(i, bg);
	}
  
  //Pick at random x number of times (x = density)
  for(int r=0; r < density; r++ )  {
    //Pick pixel
   pos = R(0,pixelsTotal);
   q(pos, primary);
  }
}

void (*menu[])() = {flavorWipe,flavorFill,rainbow,rainbowCycle,sparkle};
uint8_t menu_count = sizeof(menu)/2;

void decompose(uint16_t p) {
	if (p<pixelsTotal) {
		color_start[p][0] = extractRed(colors[p]);
		color_start[p][1] = extractGreen(colors[p]);
		color_start[p][2] = extractBlue(colors[p]);

		color_end[p][0] = extractRed(colors_future[p]);
		color_end[p][1] = extractGreen(colors_future[p]);
		color_end[p][2] = extractBlue(colors_future[p]);

		// if (color_start[p][0] < color_start[p][0]) 
		// if (color_start[p][0] < color_start[p][0]) 
		// if (color_start[p][0] < color_start[p][0]) 
		increments[p][0] = (color_end[p][0] - color_start[p][0]) / transition_steps; //// 32 is the magic transition step number
		increments[p][1] = (color_end[p][1] - color_start[p][1]) / transition_steps; 
		increments[p][2] = (color_end[p][2] - color_start[p][2]) / transition_steps; 
	}
}
void recompose(uint16_t p) {
	if (p<pixelsTotal) {
		colors[p] = color(color_start[p][0],color_start[p][1],color_start[p][2]);
	}
}
void transition() {
	
	if (will_transition) {	
		for(int i=0; i<pixelsTotal; i++){
		// Serial.print(i);
		// Serial.println(" ------");
			decompose(i);

		}
		will_transition = 0;	
	}	

	for(int i=0; i<pixelsTotal; i++){

		color_start[i][0] += increments[i][0];
		color_start[i][1] += increments[i][1];
		color_start[i][2] += increments[i][2];

		colors[i] = color(color_start[i][0],color_start[i][1],color_start[i][2]);	


		Serial.print(i);
		Serial.println(" ------");
		for(int j=0; j<3; j++){					
		  Serial.println(increments[i][j]);
		}    				
		
	}

}


void setup()
{
	Serial.begin(9600);
	
	updatePrimary(color(255,255,255));
	secondary = color(255,255,255);
	tertiary = color(255,255,255);

	strip->begin();
	strip->show();

	frequency = 260;
	intervalCount = 1;
	interval = 0;
	iter = 0;
	itermax = pixelsTotal;


	DEBUG = 1;
	verbose = 0;

	if (DEBUG) statusUpdate();


}


void loop() {

	now = millis();		// This moment is beautiful.
	
	if (now >= then+frequency) {

		then = now;

		crank();			// Select mode based on information.

		churn(); 			// Sustains flame based on each pin's last timestamp and current frameDuration	

	  pour();				// Send the 1011 and let the people have some fun.	

	  taste();

	}

  	// We are polling the serial connection.
	while(Serial.available() > 0) {
    char x = Serial.read();
		serialRouting(x);
	}
}	

void rest() {

	
}
void crank() {
	// this is where things change.
	// update mode, interval, phase etc.

	if (iter < itermax) {
		iter += 1;
	} else {
		iter = 0;
		interval++;		
	}
}

void churn() {
	// this is where things change.
	// Update based on interval and phase.

	// This is where we switch on interval.
	if (interval >= intervalCount) {
		interval = 0;
		
		selector = R(0,menu_count-1);
		// selector = 4; ///hardcoding.	
		
		/// Really we are supposed to have selector choose the 
		/// settings for the effect and then declare the effect 
		/// identifier within the selector statement 

		switch (selector) {
	    case 0:
	    	// flavorWipe()
	    	intervalCount = 1;
	    	itermax = pixelsTotal;
	    	updatePrimary(RandomWheel());

	    	break;
	    case 1:
	    // flavorFill()
	    	intervalCount = 1;
		    itermax = pixelsTotal;
	    	updatePrimary(RandomWheel());

	      // itermax = 
	      // intervalCount = 3;
	      break;
	    case 2:
	    	// rainbow()
	    	intervalCount = 1;
	    	itermax = 255;
	    	// updatePrimary(RandomWheel());

    		break;
    	case 3:
    		// rainbowCycle()
    		intervalCount = 3;
    		itermax = 255;	    	

    		break;
			case 4:
				// will_transition = 1;
				intervalCount = 1;
				// sparkle()
				itermax = 30;
				density = R(1,pixelsTotal);
				decay = 20;
				updatePrimary(RandomWheel());
				updateSecondary(color(0,0,0));
				break;
	    default:
	      // do something... Reset probably. //This is a hack for not knowing why selector is going out of bounds
	      updateAssorted();
	      // selector = R(0,sizeof(menu)-1);
	      interval = 100;
		}

		if (DEBUG) {eflag=1;statusUpdate();}
	}
	(*menu[selector])();
	// if (transitioning) transition();	
	// else (*menu[selector])(); // Magic array function call.

	// if (will_transition) {		
	// 		transitioning = 1;
	// }	

}

void pour() {	
	// this is where we lay the goods.

	/// foreach set pixel based on colors array[];
	for(int i=0; i<pixelsTotal; i++){
	    strip->setPixelColor(i,colors[i]);
	}
}

void taste() {
	// this is where the magic happens.

	// if (VERBOSE && DEBUG) {
		// Serial.println("Pouring deliciousness ...");
	// }

	// this is where we actually go live!
	strip->show();
}



// for(int i = 0; i < n; i++) // larger values of 'n' will give a smoother/slower transition.
// {
//    Rnew = Rstart + (Rend - Rstart) * i / n;
//    Gnew = Gstart + (Gend - Gstart) * i / n;
//    Bnew = Bstart + (Bend - Bstart) * i / n;
//  // set pixel color here
// }

// 
void q(uint16_t pos, uint32_t c) {		
	
	int p;

	// In here we need to be able to check the orientation, mode, and then check to see if we are compositing two effects.
	// flag for overlay / transition.

	if (mode == strand) {
		/// Still need orientation and direction statements here
		p = pos;
	} else 
	if (mode == mirrored) {
		// left/right mirror mode.
		// p = mirror(pos);
	} else 
	if  (mode == panel) { // Make each panel do the same thing.
			
		// Serial.println(orientation);
		// Serial.print("--- ");Serial.println(pos);
		if (orientation == horizontal) {
			for (int i=0;i<pixelsTotal/panelsX;i++) {				
				p = pixelsY*pos+i;
				
				// p = pixelsY*pos+i;
				// strip->setPixelColor(p, c);
				// Serial.println(p);
			}
		} else if (orientation == vertical) {
	
			for (int i=0;i<pixelsTotal/pixelsY;i++) {
				// p = (i%2) ? (panelsX*i)+(pixelsY-1)-(pos) : (i*panelsX)+(pos);
				// This one might be better....
				p = (i%2) ? (pixelsY*i)+(pixelsY-1)-(pos) : (i*pixelsY)+(pos);
				
				// strip->setPixelColor(p,c);		
				// Serial.println(p);
			}
			
		}
		
	} else {
		p = pos;
	}

	if (transitioning) {
		/// -- This defintiely goes somewhere else. Pour()?
		// change C based on some color maths.
		// compare color array 1 against color array 2
		// should we do this somewhere else? like pour() or churn()?
		// then we would always load up a color array here 
		// and then setPixelColor() in a foreach later
		colors_future[p] = c;
	} else {
		colors[p] = c;
	}

	
	// strip->setPixelColor(p,c);
}

// Serial Functions
void serialRouting(char x) {

}

void statusUpdate() {
	// Serial.print("Is Dave there?");
	Serial.println("<=== Creamery Status Update ===>"); 
	Serial.print("Selector: ");
	Serial.println(selector); 
	Serial.print("Interval: ");
	Serial.println(interval); 
	Serial.print("Primary Color: ");
	Serial.println(primary); 
	Serial.print("Frequency: ");
	Serial.println(frequency);
	Serial.print("Density: ");
	Serial.println(density);
	Serial.print("Decay: ");
	Serial.println(decay);

	Serial.print("Phase: ");
	Serial.println(phase);


	Serial.print("DEBUG: ");
	Serial.println(DEBUG);
	Serial.print("VERBOSE: ");
	Serial.println(verbose);
	
	Serial.println("<===========>");
	
	for (int j=0;j<menu_count;j++) {
		Serial.println(j);	
	}
	// resetMessageBuffer();
}

/* Helper functions */

void updatePrimary(uint32_t c) {primary = c;}
void updateSecondary(uint32_t c) {secondary = c;}
void updateTertiary(uint32_t c) {tertiary = c;}

// Update a specific flavor.
void updateFlavor(uint8_t flavor, uint32_t c) {
	switch (flavor) {
	    case 1:
	    	primary = c;
	      // do something
	      break;
	    case 2:
	    	secondary = c;
	      // do something
	      break;
      case 3:
    	tertiary = c;
      // do something
      break;
	    default:
	    	primary = c;
	      // do something
	}
}
// Update all flavors randomly.
void updateAssorted() {
	primary = RandomWheel();
	secondary = RandomWheel();
	tertiary = RandomWheel();
}

//Shorter random function, static helper. 
uint8_t R(uint8_t from, uint8_t to){ return TrueRandom.random(from, to); } 
uint32_t RandomColor(){ return color(TrueRandom.random(0,255), TrueRandom.random(0,255), TrueRandom.random(0,255)); }
uint32_t RandomWheel() { return Wheel(TrueRandom.random(0,255)%255); }

uint32_t rgba(byte r, byte g, byte b, double a) {
	int rr = r*a;
	int gg = g*a;
	int bb = b*a;

	return color(rr,gg,bb);
}

// Create a 24 bit color value from R,G,B
uint32_t color(byte r, byte g, byte b, double a) {
	int rr = r*a;
	int gg = g*a;
	int bb = b*a;

	return color(rr,gg,bb);
}

// Create a 24 bit color value from R,G,B
uint32_t color(byte r, byte g, byte b) {
	uint32_t c;
	c = r;
	c <<= 8;
	c |= g;
	c <<= 8;  
	c |= b;
	
  	return c;
}

uint32_t color(uint32_t c, double a) {
	
	uint8_t r = extractRed(c);
	uint8_t g = extractGreen(c);
	uint8_t b = extractBlue(c);
		
	return rgba(r,g,b,a);
}

uint32_t alpha(uint32_t c, double a) {
	
	uint8_t r = extractRed(c);
	uint8_t g = extractGreen(c);
	uint8_t b = extractBlue(c);
		
	return rgba(r,g,b,a);
}

// Helpers to extract RGB from 32bit color. (/// This could be MACRO...)
uint8_t extractRed(uint32_t c) { return (( c >> 16 ) & 0xFF); } 
uint8_t extractGreen(uint32_t c) { return ( (c >> 8) & 0xFF ); } 
uint8_t extractBlue(uint32_t c) { return ( c & 0xFF ); }

//Input a value 0 to 255 to get a color value.
//The colours are a transition r - g -b - back to r
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
   return color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
   WheelPos -= 85;
   return color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170; 
   return color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
// This is Wheel with alpha.
uint32_t Wheel(byte WheelPos, double alpha) {
  if (WheelPos < 85) {
   return rgba(WheelPos * 3, 255 - WheelPos * 3, 0,alpha);
  } else if (WheelPos < 170) {
   WheelPos -= 85;
   return rgba(255 - WheelPos * 3, 0, WheelPos * 3,alpha);
  } else {
   WheelPos -= 170; 
   return rgba(0, WheelPos * 3, 255 - WheelPos * 3,alpha);
  }
}


// 
// 
// void singlePulseWipe(uint32_t c, uint16_t dir, uint16_t f, uint16_t wait) {
// 	int i;
// 		
// 	for(i=0; i<strip.numPixels();i++)
// 	{
// 		singlePulse(i,c,f,wait);
// 	}
// 	
// }
// 
// // We need an effect that hits just one panel
// // Pixel, Color, Freq, Sust
// void singlePulse(uint8_t n,uint32_t c, uint16_t f, uint16_t wait) {
// 	// Make sure if you are trying to hit a whole panel, you set the orientation and mode of grid.	
// 	
// 	int i;
//   	double alpha;
//   
// 	for(alpha=0;alpha<1;alpha=alpha+0.01) {
// 		q(n, Color(c,alpha));
// 		 strip.show();
// 	    delay(wait);	   
// 	}
//   	// strip.show();
// 	
// 	delay(f);	
// 	
// 	// FadeOut(wait);
// 	
// }
// 
// //Nuff said, only duration, not speed can be set (made this 15 minutes before you took my balls.)
// void strobe(uint8_t runs){
//   int i;
//   int r;
//   int total = strip.numPixels();
//   for(r=0;r<runs;r++) {
//      for(i=0;i<total;i++){
//        q(i, rgba(255,255,255,0.2));
//      }
//      strip.show();
//      delay(25);
//      
//      for(i=0;i<total;i++){
//        q(i, Color(0,0,0));
//      }
//      strip.show();
//      delay(100);
//   }
// }
// 
// // Butterfly Effect 
// void ButterflyEffect() {
// 	int i;
// 	for (i=1;i<255;i++) {
// 		Sparkle(Color(0,0,0), 1, 10, 50, Wheel(i));
// 	}
// }
// 
// // Malfunction-like effect with blanks and color;
// void Malfunction() {
// 	int i;
// 	for (i=1;i<255;i++) {
// 		if (i%2) {
// 			Sparkle(Color(0,0,0), 10, 10, 100, Wheel(i));
// 		} else {	
// 			Sparkle(RandomWheel(), 10, 10, 10, Wheel(i));
// 		}	
// 	}
// }
// 
// 
// void PolkadotCycle(uint32_t c, uint32_t d, uint32_t wait) {
// 
//   for (int j=0; j < 256 * 5; j++) {     // 5 cycles of all 25 colors in the wheel
//     for (int i=0; i < strip.numPixels(); i++) {
// 
// 			if ((i%2)==0) {
// 	        	q(i, c);
// 	      	} else {
// 	        	q(i, d);      
// 	      	}
// 	    }
// 			
//       // q(i, Wheel( ((i * 256 / strip.numPixels()) + j) % 256) );
//     }  
//     strip.show();   // write all the pixels out
//     delay(wait);
// 	
// }
// 
// // Usage:
// // polkadots(Color(255,0,255),Color(0,255,255), 50);
// void polkadotFill(uint32_t c, uint32_t d, uint32_t wait) {
//   int i;
//   
//   for (i=0; i < strip.numPixels(); i++) {
//       
//       if ((i%2)==0) {
//         q(i, c);
//       } else {
//         q(i, d);      
//       }
//   }
//   strip.show();
//   delay(wait);  
// }  
// 
// void PolkadotPulse(uint32_t c, uint32_t d, uint32_t wait, uint8_t sustain) {
//   
//   	int i;
//   	double alpha;
//   	int total = strip.numPixels();
//   
// 	for(alpha=0;alpha<1;alpha=alpha+0.01) {
// 	    for(i=0;i<total;i++)  {
// 			if ((i%2)==0) {
// 	        	q(i, Color(c,alpha));
// 	      	} else {
// 	        	q(i, Color(d,alpha));      
// 	      	}
// 	    }
// 	    strip.show();
// 	    delay(wait);
//   	}
//   	// strip.show();
// 	
// 	delay(sustain);	
// 	FadeOut(wait);
// 	// for(alpha=1;alpha>0;alpha=alpha-0.01) {
// 	//       	if ((i%2)==0) {
// 	//        		q(i, Color(c,alpha));
// 	//      	} else {
// 	//        		q(i, Color(d,alpha));      
// 	//      	}
// 	//     	strip.show();
// 	//     	delay(wait);
// 	//   	}
//   	// strip.show();
// 
// }
// 
// //Builds up a white sparkle, and then does a random sparkle for colors. 
// void SparkleChaos1(){
//   int go = 0;
//   int density = 1;
//   for(go=0;go<255;go++) { 
//     if(go>50) { density = 2; }
//     else if(go>100) {density = 3; }
//     else if(go>150) {density = 4; }
//     else if(go > 200) {density = 5; }
//     else if(go > 225) { density = 7; }
//     Sparkle(Color(go,go,go), density, 0); 
//     delay(10);
//   }
//   	for(go=0;go<100;go++) { SparkleRandom(); } 
//   	
// 	FadeOut(10);
// }
// 
// /// /Builds a sparkle faster and then slows it down./
// // void FasterSlower(){
// //   SparkleFaster(500);
// //   SparkleSlower(500);
// // }
// 
// void RainbowPulse(uint32_t wait) {
// 	
// 	int i;
// 	for(i=0;i<255;i+=23) { 	
// 		ColorPulse(Wheel(i),wait);				
// 	}
// }
// 
// void ColorPulse(uint32_t color,uint32_t wait) {
//    	FadeInAll(color, wait);	
//    	FadeOutAll(color, wait);
// 	// delay(wait);
// }
// 
// //
// // THIS STUFF IS USEFUL!!!!!
// //
// 
// void FadeInOutWhite(uint32_t wait){
//    FadeInAll(Color(255,255,255), wait);
//    FadeOutAll(Color(255,255,255), wait);
// }
// 
// void FadeInOutRandom(uint32_t wait){
// 	uint32_t color = RandomColor();
//    	FadeInAll(color, wait);
//     FadeOutAll(color, wait);
// }
// 
// void FadeInAll(uint32_t color, uint32_t wait){
//   int i;
//   double alpha;
//   int total = strip.numPixels();
//   
//   for(alpha=0;alpha<1;alpha=alpha+0.01) {
//     for(i=0;i<total;i++)  {
//        q(i, Color(color,alpha)); 
//     }
//     strip.show();
//     delay(wait);
//   }
//   strip.show();
// }
// 
// void FadeOutAll(uint32_t color, uint32_t wait){
//   int i;
//   double alpha;
//   int total = strip.numPixels();
//   
//   for(alpha=1;alpha>0;alpha=alpha-0.01) {
//     for(i=0;i<total;i++)  {
//        q(i,Color(color,alpha)); 
//     }
//     strip.show();
//     delay(wait);
//   }
//   strip.show();
// }
// 
// void FadeInSparkles(uint32_t color, uint32_t wait){
//   int i;
//   double alpha;
//   int total = strip.numPixels();
//   
//   for(alpha=0;alpha<0.25;alpha=alpha+0.01) {
//     for(i=0;i<total;i++)  {
//       Sparkle(Wheel(color,alpha), TrueRandom.random(1,25), 25);
//     }
//     strip.show();
//     delay(wait);
//   }
//   strip.show();
// }
// 
// void FadeOutSparkles(uint8_t r, uint8_t g, uint8_t b, uint32_t wait){
//   int i;
//   double alpha;
//   int total = strip.numPixels();
//   
//   for(alpha=0.25;alpha>0;alpha=alpha-0.01) {
//     for(i=0;i<total;i++)  {
//        Sparkle(rgba(r,g,b,alpha), TrueRandom.random(1,25), 25);
//     }
//     strip.show();
//     delay(wait);
//   }
//   strip.show();
// }
// 
// //This is the exact same thing as Sparkle except with random colors.
// 
// void SparkleRainbow(uint8_t density, uint32_t wait){
//     int total=strip.numPixels();
//     int r; 
//     int i;
//     int pixel; 
// 
//   //Set all pixels to bg
//   for(i=0; i < strip.numPixels(); i++ ) {
//     //Set color
//     q(i, Color(0,0,0));
//   }
// //  update Lights
//   strip.show();
//   
//   //Pick at random x number of times (x = density)
//   for( r=0; r < density; r++ )  {
//     //Pick pixel
//    pixel = TrueRandom.random(1,total);
// 	q(pixel, RandomWheel());
//    // q(pixel, Color(this->R(0,255), this->R(0,255), this->R(0,255)));
//   }
//   //Update lights
//   strip.show();
//   
//   delay(wait);
//  //
// }
// 
// void DoubleRainbowSparkle(uint8_t density, uint32_t wait, uint8_t sustain){
// 	int i;
// 
// 	for (i=1;i<255;i++) {
// 		Sparkle(RandomWheel(), density, wait, sustain, Wheel(i));
// 	}
// }
// 
// //3 Parameter SPARKLE
// void Sparkle(uint32_t color, uint8_t density, uint32_t wait){
// 	Serial.println("Running Sparkle");
//     int total=strip.numPixels();
//     int r;
//     int i;
//     int pixel; 
// 
//   //Set all pixels to bg
//   for(i=0; i < strip.numPixels(); i++ ) {
//     //Set color
//     q(i, Color(0,0,0));
//   }
// //  update Lights
//   strip.show();
//   
//   //Pick at random x number of times (x = density)
//   for( r=0; r < density; r++ )  {
//     //Pick pixel
//    pixel = TrueRandom.random(1,total);
//    q(pixel, color);
//   }
//   //Update lights
//   strip.show();
//   
//   delay(wait);
//  //
// }
// 
// //5 Parameter SPARKLE
// void Sparkle(uint32_t color, uint8_t density, uint32_t wait, uint8_t sustain, uint32_t bg){
// 	int total=strip.numPixels();
// 	int r; 
// 	int i;
// 	int pixel; 
// 
//   	//Set all pixels to bg
//   	for(i=0; i < strip.numPixels(); i++ ) {
//     	//Set color
//     	q(i, bg);
//   	}
//   	delay(wait);
//   //  update Lights
//   strip.show();
//   
//   //Pick at random x number of times (x = density)
//   for( r=0; r < density; r++ )  {
//     //Pick pixel
//    pixel = TrueRandom.random(1,total);
//    q(pixel, color);
//   }
//   //Update lights
//   strip.show();
//   
//   delay(sustain);
//  //
// }
// 
// void SparkleFill(uint32_t color, uint8_t density, uint32_t wait){
//   int total=strip.numPixels();
//   int r; 
//   int i;
//   int pixel; 
//   
//   //Pick at random x number of times (x = density)
//   for( r=0; r < density; r++ )  {
//     // Pick pixel
//    pixel = TrueRandom.random(1,total);
//    q(pixel, color);
//   }
//   //Update lights
//   strip.show();
//   
//   delay(wait);
// }
// 
// // void SparkleFaster(uint8_t duration){
// //   int go;
// //   for(go=0;go<100;go++) {
// //     SinglePixel( Easing::easeOutSine(go, 80, 0, duration) );
// //   }
// // }
// 
// // void SparkleSlower(uint8_t duration){
// //   int go;
// //   for(go=0;go<100;go++) {
// //     SinglePixel( Easing::easeInSine(go, 0, 80, duration) );
// //   }
// // }
// 
// void SinglePixel(uint8_t DELAY){
//  Sparkle(Color(255,255,255), 1, DELAY);
// }
// 
// void CrazyPixel(uint32_t COLOR){
//   Sparkle(COLOR, 4, 1);
// }
// 
// void SparkleRandom(){  
//   int COLOR = Color(TrueRandom.random(0,255), TrueRandom.random(0,255), TrueRandom.random(0,255));
//   int DENSITY = TrueRandom.random(1,30);
//   int DELAY = TrueRandom.random(25,160);
//   
//   Sparkle(COLOR, DENSITY, DELAY);  
// }
// 
// void ColorJump(uint8_t DELAY){
//   int i;
//   uint32_t COLOR;
//   COLOR = RandomColor();
//   for(i=0;i<strip.numPixels();i++) { q(i, COLOR); }
//   strip.show();
//   delay(DELAY/2);
//   for(i=0;i<strip.numPixels();i++) { q(i, Color(0,0,0)); }
//   strip.show();
//   delay(DELAY/2);
// }
// 
// void rainbow(uint32_t wait) {
//   int i, j;
//    
//   for (j=0; j < 256; j++) {     // 3 cycles of all 256 colors in the wheel
//     for (i=0; i < strip.numPixels(); i++) {
//       q(i, Wheel( (i + j) % 255));
//     }  
//     strip.show();   // write all the pixels out
//     delay(wait);
//   }
// }
// 
// void rainbowStrobe(uint32_t wait) {
//   	int i, j;
//    
//     for (i=0; i < strip.numPixels(); i++) {
//       q(i, RandomWheel());
//     }  
//     strip.show();   // write all the pixels out
//     delay(wait);
// }
// 
// 
// // Slightly different, this one makes the rainbow wheel equally distributed 
// // along the chain
// void rainbowCycle(uint32_t wait) {
//   int i, j;
//   
//   for (j=0; j < 256 * 5; j++) {     // 5 cycles of all 25 colors in the wheel
//     for (i=0; i < strip.numPixels(); i++) {
//       // tricky math! we use each pixel as a fraction of the full 96-color wheel
//       // (thats the i / strip.numPixels() part)
//       // Then add in j which makes the colors go around per pixel
//       // the % 96 is to make the wheel cycle around
//       q(i, Wheel( ((i * 256 / strip.numPixels()) + j) % 256) );
//     }  
//     strip.show();   // write all the pixels out
//     delay(wait);
//   }
// 	// FadeOut(20);
// }
// 
// // fill the dots one after the other with said color
// // good for testing purposes
// void colorWipe(uint32_t c,uint32_t d,uint32_t wait) {
//   	int i;  
// 
// 	// Serial.println("Beginning Effect ColorWipe...");
// 
// 	// Serial.print("--- ");Serial.println(wait);
// 
// 	if (d == desc) {
// 		// Descending
// 		for (i=0; i<strip.numPixels(); i++) {		
// 			q(i, c);
// 			strip.show();
// 			delay(wait);
// 	  	}
// 			
// 	} else {
// 		// Ascending
// 		for (i=strip.numPixels();i>=0;i--) {			
// 			q(i, c);
// 			strip.show();
// 			delay(wait);
// 	  	}
// 	  	
// 	}
// 
// 	
// 	
// }
// // // fill the dots one after the other with said color
// // // good for testing purposes
// // void colorWipe(uint32_t c, uint32_t wait) {
// //   int i;
// //   
// //   for (i=0; i < strip.numPixels(); i++) {
// //       q(i, c);
// //       strip.show();
// //       delay(wait);
// //   }
// // }
// 
// // fill the entire strip with said color
// // good for testing purposes
// void colorFill(uint32_t c) {
//   int i;
//   
//   for (i=0; i < strip.numPixels(); i++) {
//       q(i, c);
//   }
//   strip.show();
// }
// 
// /* Transition functions */
// bool trans(uint16_t i, uint32_t newcolor, uint32_t wait) {
// 	
// 	// rgb = current, nrgb = new, trgb = transition.
// 	bool rflag,gflag,bflag=false;
// 	uint8_t r,g,b,nr,ng,nb;
// 	uint32_t c = strip.getPixelColor(i);	
// 	r = extractRed(c);
// 	g = extractGreen(c);
// 	b = extractBlue(c);
// 
// 	nr = extractRed(newcolor);
// 	ng = extractGreen(newcolor);
// 	nb = extractBlue(newcolor);
// 	
// 	Serial.print("Current:");Serial.print(r);Serial.print(" ");Serial.print(g);Serial.print(" ");Serial.println(b);
// 	Serial.print("    New:");Serial.print(nr);Serial.print(" ");Serial.print(ng);Serial.print(" ");Serial.println(nb);
// 	Serial.print("  Flags:");Serial.print(rflag);Serial.print(" ");Serial.print(gflag);Serial.print(" ");Serial.println(bflag);
// 	
// 	if (nr < r) {
// 		r--;
// 	} else if (nr > r) {
// 		r++;
// 	} else {
// 		rflag = true;
// 	}
// 	if (ng < g) {
// 		g--;
// 	} else if (ng > g) {
// 		g++;
// 	} else {
// 		gflag = true;
// 	}
// 	if (nb < b) {
// 		b--;
// 	} else if (nb > b) {
// 		b++;
// 	} else {
// 		bflag = true;
// 	}
// 	
// 	if (rflag && gflag && bflag) { return true; }
// 	
// 	q(i,Color(r,g,b));
// 	strip.show();
// 	
// 	return false;
// 	
// }	
// void FadeOut(uint32_t wait) {
//   int i;
//   double alpha;
//   int total = strip.numPixels();
// 
//   for(alpha=1;alpha>0;alpha=alpha-0.01) {
//     for(i=0;i<total;i++)  {
//        q(i,Color(strip.getPixelColor(i),alpha)); 
//     }
//     strip.show();
//     delay(wait);
//   }
//   strip.show();
// 
// }
// 
// /* Helper functions */
// 
// //Shorter random function, static helper. 
// uint8_t R(uint8_t from, uint8_t to){
//  return TrueRandom.random(from, to);
// } 
// 
// uint32_t RandomColor(){
//    return Color(TrueRandom.random(0,255), TrueRandom.random(0,255), TrueRandom.random(0,255));
// }
// 
// uint32_t RandomWheel() {	
// 	return Wheel(TrueRandom.random(0,255)%255);		
// }
// 
// uint32_t rgba(byte r, byte g, byte b, double a) {
// 	int rr = r*a;
// 	int gg = g*a;
// 	int bb = b*a;
// 
// 	return Color(rr,gg,bb);
// }
// 
// // Create a 24 bit color value from R,G,B
// uint32_t Color(byte r, byte g, byte b, double a) {
// 	int rr = r*a;
// 	int gg = g*a;
// 	int bb = b*a;
// 
// 	return Color(rr,gg,bb);
// }
// 
// // Create a 24 bit color value from R,G,B
// uint32_t Color(byte r, byte g, byte b) {
// 	uint32_t c;
// 	c = r;
// 	c <<= 8;
// 	c |= g;
// 	c <<= 8;  
// 	c |= b;
// 	
//   	return c;
// }
// 
// uint32_t Color(uint32_t c, double a) {
// 	
// 	uint8_t r = extractRed(c);
// 	uint8_t g = extractGreen(c);
// 	uint8_t b = extractBlue(c);
// 		
// 	return rgba(r,g,b,a);
// }
// 
// uint32_t alpha(uint32_t c, double a) {
// 	
// 	uint8_t r = extractRed(c);
// 	uint8_t g = extractGreen(c);
// 	uint8_t b = extractBlue(c);
// 		
// 	return rgba(r,g,b,a);
// }
// 
// // Helpers to extract RGB from 32bit color. (Woohoo!!)
// uint8_t extractRed(uint32_t c) { return (( c >> 16 ) & 0xFF); } 
// uint8_t extractGreen(uint32_t c) { return ( (c >> 8) & 0xFF ); } 
// uint8_t extractBlue(uint32_t c) { return ( c & 0xFF ); }
// 
// //Input a value 0 to 255 to get a color value.
// //The colours are a transition r - g -b - back to r
// uint32_t Wheel(byte WheelPos) {
//   if (WheelPos < 85) {
//    return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
//   } else if (WheelPos < 170) {
//    WheelPos -= 85;
//    return Color(255 - WheelPos * 3, 0, WheelPos * 3);
//   } else {
//    WheelPos -= 170; 
//    return Color(0, WheelPos * 3, 255 - WheelPos * 3);
//   }
// }
// // This is Wheel with alpha.
// uint32_t Wheel(byte WheelPos, double alpha) {
//   if (WheelPos < 85) {
//    return rgba(WheelPos * 3, 255 - WheelPos * 3, 0,alpha);
//   } else if (WheelPos < 170) {
//    WheelPos -= 85;
//    return rgba(255 - WheelPos * 3, 0, WheelPos * 3,alpha);
//   } else {
//    WheelPos -= 170; 
//    return rgba(0, WheelPos * 3, 255 - WheelPos * 3,alpha);
//   }
// }


