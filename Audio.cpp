// #include "Adafruit_WS2801.h"
// #include "CTRL.h"
// #include "TrueRandom.h"
// #include <Easing.h>
// #include "Audio.h"
// 
// Audio::Audio() {
// 
// 	// The Beginnings of the Audio CPP file.
// 
// 	// === Audio vars
// 	//For spectrum analyzer shield, these three pins are used.
// 	//You can move pinds 4 and 5, but you must cut the trace on the shield and re-route from the 2 jumpers. 
// 	this->spectrumReset=5;
// 	this->spectrumStrobe=4;
// 	this->spectrumAnalog=0;  //0 for left channel, 1 for right.
// 
// 	// Spectrum analyzer read values will be kept here.
// 	this->Spectrum[7];
// 	this->average = 0;
// 	this->kickThreshold = 0;
// 	this->snareThreshold = 0;
// 	this->kick = 0;
// 	this->snare = 0;
// 
// 	// Divisor for audio signal scaling ///
// 	// 22 ~ 80
// 	// 72 ~ 10
// 	this->Divisor = 10;
// 
// 	// //Setup pins to drive the spectrum analyzer. 
// 	// 	  pinMode(spectrumReset, OUTPUT);
// 	// 	  pinMode(spectrumStrobe, OUTPUT);
// 	// 
// 	// 	  //Init spectrum analyzer
// 	// 	  digitalWrite(spectrumStrobe,LOW);
// 	// 	  delay(1);
// 	// 	  digitalWrite(spectrumReset,HIGH);
// 	// 	  delay(1);
// 	// 	  digitalWrite(spectrumStrobe,HIGH);
// 	// 	  delay(1);
// 	// 	  digitalWrite(spectrumStrobe,LOW);
// 	// 	  delay(1);
// 	// 	  digitalWrite(spectrumReset,LOW);
// 	// 	  delay(5);
// 	// 	  // Reading the analyzer now will read the lowest frequency.
// 	
// }	
// 
// 
// void Audio::rainbowPulse(uint32_t wait)
// {
// 	this->readSpectrum();
// 
//   // static unsigned int Divisor = 20;
//   unsigned int works,i,j;
// 	
// 	int alpha;
// 	double a;
// 
//   for (int s=0;s<7;s++) {			
//   	
//     for (i=0; i < this->numPixels()/division; i++) {
// 		  alpha = Spectrum[i%7]/Divisor;
// 			a = (double)alpha*.01;
//       this->q(i, Wheel( ((s * 256 / this->numPixels()) + i) % 256,a) );
// 
// 			// Serial.print(i%7);
// 			// 		  Serial.print(" - ");
// 			// Serial.println(a);
//    		
//     }  
//     this->show();   // write all the pixels out
//  		delay(wait);    
//   }
// }
// 
// void Audio::showSpectrum(uint32_t wait)
// {
// 	this->readSpectrum();
// 	
//   	byte Band, BarSize, MaxLevel;
//   	static unsigned int  Divisor = 20, ChangeTimer=0;
//   	unsigned int works, Remainder;
// 
//   	int peak = Spectrum[2]/Divisor;
// 	int wheel = Spectrum[1]/10;
// 
//   	MaxLevel = 0; 
// 
//    for (int i=0; i < this->numPixels() / division; i++) {
//      if (i <= peak) {
//  				mirror(i, Wheel(wheel+(i*5),1)); 
// 				// this->q(i,Color(0,0,45));
//    			// mirror(i, Wheel(random(0,wheel)),1); 
//       } else {
// 		this->q(i, Color(0,0,0));
//    		}
//    			Serial.println(peak);
//    }  
// 		
//   // this->show();
//   
//   
// //    //If value is 0, we don't show anything on graph
// //    works = Spectrum[Band]/Divisor;	//Bands are read in as 10 bit values. Scale them down to be 0 - 5
// //    if(works > MaxLevel)  //Check if this value is the largest so far.
// //      MaxLevel = works;                       
//   
// 
//   this->show();
//   delay(wait);
// }
// 
// // foreach spectrum pick a color and run an alpha intensity.
// void Audio::rainbowSpectrum(uint32_t wait)
// {
// 	readSpectrum();
// 
//   // static unsigned int Divisor = 20;
//   unsigned int works,i,j;
// 	
// 	int alpha;
// 	double a;
//   int peak = Spectrum[1]/Divisor;
// 	int wheel = Spectrum[1]/20;
// 
//   // for (int i=0; i < this->numPixels() / division; i++) {
// 			
// 
//   // for (j=0; j < 256 * 5; j++) {     // 5 cycles of all 25 colors in the wheel
//   // for (int s=0;s<7;s++) {  	
//     for (i=0; i < this->numPixels()/division; i++) {
// 
// 		alpha = Spectrum[1]/Divisor;
// 		a = (double)alpha*.01;
// 
//       	this->q(i, Wheel( ((i * 256 / this->numPixels())) % 256,a) );
// 
// 		Serial.print((this->numPixels()/division)/7);
// 		Serial.print(" - ");
// 		Serial.println(a);
//    		
//     }  
//     this->show();   // write all the pixels out
//  	delay(wait);    
//   // }
// 
// // %/100 = x/7 
// 
// // 9/18 = x/7			
// 		  // this->q(i, Wheel((s*5),alpha)); 				
// 
// 
// }
// 
// void Audio::RainbowLevel(uint32_t wait)
// {
// 	readSpectrum();
// 
//   	static unsigned int  Divisor = 20;
//   	unsigned int works;
// 
//   	int peak = Spectrum[1]/Divisor;
// 	int wheel = Spectrum[1]/10;
// 
//    	for (int i=0; i < this->numPixels() / division; i++) {
//      	if (i <= peak) {
// 			this->q(i, Wheel(wheel+(i*5),1)); 
// 			// this->q(i,Color(0,0,45));
//    			// mirror(i, Wheel(random(0,wheel)),1); 
//       	} else {
//         	this->q(i, Color(0,0,0));
//    		}
//    		Serial.println(peak);
//    	}  
// 
//   	this->show();
//   	delay(wait);
// }
// // Read 7 band equalizer.
// void Audio::readSpectrum()
// {
// 	int display_eq = 1;
// 	average = 0;
// 
//   	byte Band;
//   	for(Band=0;Band <7; Band++) {
//     	Spectrum[Band] = (analogRead(spectrumAnalog) + analogRead(spectrumAnalog) ) >>1; //Read twice and take the average by dividing by 2
//     	digitalWrite(spectrumStrobe,HIGH);
//     	digitalWrite(spectrumStrobe,LOW);     
// 		average += Spectrum[Band];
// 
//     	// Serial.print(Spectrum[Band]/80);       
//     	// Serial.print(" ");     
//   	}
// 
// 	average = average/7; 	
// 	// Serial.print(Spectrum[1]);
// 	// Serial.print(" - ");
// 	// Serial.print(Spectrum[6]);
// 	// Serial.print(" - ");
// 	// Serial.println(average);
// 	
// 	if (Spectrum[1] > average) {
// 		// Serial.print("Kick - "); 
// 		// Serial.println(Spectrum[1]); 
// 		kick = 1;
// 	} else {kick=0;}
// 	if (Spectrum[6] > average) {
// 		// Serial.print("Snare - "); 
// 		// Serial.println(Spectrum[1]); 
// 		snare = 1;
// 	} else {snare=0;}
// 
//   	// Serial.println(average);
// }
// 
