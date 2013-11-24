// 
// void q(uint16_t pos, uint32_t c) {		
// 	
// 	strip.setPixelColor(pos,c);
// 	
// 	/*
// 	if (this->mode == strand) {
// 		this->setPixelColor(pos,c);
// 	} else if (this->mode == mirrored) {
// 		// left/right mirror mode.
// 		// mirror(pos,c);
// 	}	
// 	if (this->mode == panel) { // Make each panel do the same thing.
// 		int p;	
// 		// Serial.println(this->orientation);
// 		// Serial.print("--- ");Serial.println(pos);
// 		if (this->orientation == horizontal) {
// 			for (int i=0;i<this->total/this->panelsX;i++) {				
// 				p = this->pixelsY*pos+i;
// 				
// 				// p = this->pixelsY*pos+i;
// 				this->setPixelColor(p, c);
// 				// Serial.println(p);
// 			}
// 		} else if (this->orientation == vertical) {
// 	
// 			for (int i=0;i<this->total/this->pixelsY;i++) {
// 				// p = (i%2) ? (this->panelsX*i)+(this->pixelsY-1)-(pos) : (i*this->panelsX)+(pos);
// 				// This one might be better....
// 				p = (i%2) ? (this->pixelsY*i)+(this->pixelsY-1)-(pos) : (i*this->pixelsY)+(pos);
// 				
// 				this->setPixelColor(p,c);		
// 				// Serial.println(p);
// 			}
// 			
// 		}
// 		
// 	} else {
// 		this->setPixelColor(pos,c);
// 	}
// 	
// 	*/
// }
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
