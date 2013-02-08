#include "Adafruit_WS2801.h"
#include "CTRL.h"
#include <aJSON.h>
#include "Grid.h"
// #include "TrueRandom.h"
// #include <Easing.h>

CTRL::CTRL(Adafruit_WS2801 *strip,int panelsX, int panelsY,int pixelsX,int pixelsY) {	
	
	this->total = strip->numPixels();
	this->strip = strip;

	Grid *g = new Grid(strip,panelsX,panelsY,pixelsX,pixelsY,panel);
	this->grid = g;

	this->creamery = new Creamery(g);
	
	Serial.println("Constructing... ");	
		
	// === Controller vars ===
	this->timer = 0;
	this->phase = 0;
	this->interval = 0;

	// This will become the current effect parameter.
	this->selector = 0;
	
	// === Pattern vars ===
	
	
	
	// === Grid / Pattern vars === 
	// Division sets the strand mode. 1 is regular, 2 is Mirror, 3 is Triangle (not added yet), 4 is Radial.
	this->mode = panel;
	this->orientation = vertical;
	this->direction = asc;
			
	// this->panelsX = 12;
	// this->panelsY = 1;
	// this->pixelsX = 1;
	// this->pixelsY = 12;
	// this->division = 12;


	// Colors:
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
	
}
void CTRL::render() {   

	this->timer = millis();
	
	Serial.print("Render: ");
	Serial.println(this->timer);	
	
	if (test == 1) {
		Serial.println("Test Mode Engaged");
		
		// PolkadotCycle(RandomWheel(),RandomWheel(),100);
		// FadeOut(10);
		colorWipe(this->creamery->RandomWheel(),asc,600);
	} else {

	  	if (this->timer > this->iduration*this->interval) {
			if (debug) {
				Serial.print("=== Interval "); Serial.print(this->interval); Serial.println(" ===");			
				Serial.print("Timer: ");
				Serial.println(this->timer);
				Serial.print("interval * iduration: ");
				Serial.println(this->interval*this->iduration);		
			}
			
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
		
			// This speeds us up as time goes on.
			if (timer < 3*(60*(60*1000))) {
				intensity = (iduration / interval) / selector;
			} else {
				intensity = (iduration / interval / selector) %10 + (phase/2);
			}

			// Increment Selector
	     	this->selector = random(0,10);
			// this->selector = 8;
		
			// Check audio and other factors here...
			// 	Primary Color, Secondary Color, Delay, Odd/Even Interval
		
			primary = this->creamery->Wheel(random(0,255));
			secondary = this->creamery->Wheel(random(0,255));		
		
			Serial.print("Phase: ");
			Serial.println(phase);
		
			Serial.print("Intensity: ");
			Serial.println(intensity);
		
			Serial.print("Selector: "); 	
		 	Serial.println(this->selector);

		}
		
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
	
		if (phase < 4) {		
			if (selector == 0) { Serial.println("Effect: Sparkle"); this->creamery->Malfunction(); }
			if (selector == 1) { Serial.println("Effect: Sparkle"); this->creamery->Sparkle(this->creamery->RandomWheel(), interval%20, 100, 100, primary); }
			if (selector == 2) { Serial.println("Effect: Strobe"); this->creamery->DoubleRainbowSparkle(20,20,100); }
			if (selector == 3) { Serial.println("Effect: RainbowPulse"); this->creamery->RainbowPulse(1); }	
			if (selector == 4) { Serial.println("Effect: ButterflyEffect"); this->creamery->ButterflyEffect(); }
			if (selector == 5) { Serial.println("Effect: SparkleRandom"); this->creamery->SparkleRandom(); }
			if (selector == 6) { Serial.println("Effect: ColorPulseRainbow"); this->creamery->ColorPulse(this->creamery->RandomWheel(),10); }
			if (selector == 7) { Serial.println("Effect: PolkaDots"); this->creamery->PolkadotPulse(this->creamery->Wheel(random(0,255)),this->creamery->Wheel(random(0,255)),50,1000); }				
			if (selector == 8) { Serial.println("Effect: SparkleRainbow Bubblegum IceCream"); this->creamery->SparkleRainbow(20,intensity*10); }
			if (selector == 9) { Serial.println("Effect: Rainbow Strobe"); this->creamery->rainbowStrobe(500); }
			if (selector == 10) { Serial.println("Effect: SparkleRainbow Bubblegum IceCream"); this->creamery->SparkleRainbow(20,intensity*10); }
		
		} else if (phase < 8) {
			if (selector == 0) { Serial.println("Effect: Sparkle"); this->creamery->Malfunction(); }
			if (selector == 1) { Serial.println("Effect: Sparkle"); this->creamery->Sparkle(this->creamery->RandomWheel(), interval%20, 100, 100, primary); }
			if (selector == 2) { Serial.println("Effect: Strobe"); this->creamery->DoubleRainbowSparkle(20,20,100); }
			if (selector == 3) { Serial.println("Effect: RainbowPulse"); this->creamery->RainbowPulse(1); }	
			if (selector == 4) { Serial.println("Effect: SinglePixel"); this->creamery->SinglePixel(1); }
			if (selector == 5) { Serial.println("Effect: SparkleRandom"); this->creamery->SparkleRandom(); }
			if (selector == 6) { Serial.println("Effect: ColorPulseRainbow"); this->creamery->ColorPulse(this->creamery->RandomWheel(),1); }
			if (selector == 7) { Serial.println("Effect: PolkaDots"); this->creamery->PolkadotPulse(this->creamery->Wheel(random(0,255)),this->creamery->Wheel(random(0,255)),50,1000); }				
			if (selector == 8) { Serial.println("Effect: SparkleRainbow Bubblegum IceCream"); this->creamery->SparkleRainbow(20,10); }
			if (selector == 9) { Serial.println("Effect: Rainbow Strobe"); this->creamery->rainbowStrobe(500); }
			if (selector == 10) { Serial.println("Effect: SparkleChaos1"); this->creamery->SparkleChaos1(); }
		
		} else if (phase < 16) {
			if (selector == 0) { Serial.println("Effect: Sparkle"); this->creamery->Malfunction(); }
			if (selector == 1) { Serial.println("Effect: Sparkle"); this->creamery->Sparkle(this->creamery->RandomWheel(), interval%20, 100, 100, primary); }
			if (selector == 2) { Serial.println("Effect: Strobe"); this->creamery->DoubleRainbowSparkle(20,20,100); }
			if (selector == 3) { Serial.println("Effect: RainbowPulse"); this->creamery->RainbowPulse(1); }	
			if (selector == 4) { Serial.println("Effect: SinglePixel"); this->creamery->SinglePixel(1); }
			if (selector == 5) { Serial.println("Effect: SparkleRandom"); this->creamery->SparkleRandom(); }		
			if (selector == 6) { Serial.println("Effect: FadeInOutRandom"); this->creamery->FadeInOutRandom(10); }
			if (selector == 7) { Serial.println("Effect: PolkaDotStrobe"); this->creamery->polkadotFill(this->creamery->Wheel(random(0,255)),this->creamery->Wheel(random(0,255)),intensity*10); }	
			if (selector == 8) { Serial.println("Effect: SparkleRainbow Bubblegum IceCream"); this->creamery->SparkleRainbow(20,10); }
			if (selector == 9) { Serial.println("Effect: Rainbow Strobe"); this->creamery->rainbowStrobe(500); }
			if (selector == 10) { Serial.println("Effect: SparkleChaos1"); this->creamery->SparkleChaos1(); }
		
		} else if (phase < 32) {	
			// if (selector == 0) { Serial.println("Effect: Sparkle"); this->creamery->Malfunction(); }
			if (selector == 1) { Serial.println("Effect: Sparkle"); this->creamery->Sparkle(this->creamery->RandomWheel(), interval%20, 100, 100, primary); }
			if (selector == 2) { Serial.println("Effect: Strobe"); this->creamery->DoubleRainbowSparkle(20,20,100); }
			if (selector == 3) { Serial.println("Effect: RainbowPulse"); this->creamery->RainbowPulse(1); }	
			if (selector == 4) { Serial.println("Effect: SinglePixel"); this->creamery->SinglePixel(1); }
			if (selector == 5) { Serial.println("Effect: SparkleRandom"); this->creamery->SparkleRandom(); }
			if (selector == 6) { Serial.println("Effect: FadeInOutRandom"); this->creamery->FadeInOutRandom(10); }
			if (selector == 7) { Serial.println("Effect: PolkaDots"); this->creamery->polkadotFill(this->creamery->Wheel(random(0,255)),this->creamery->Wheel(random(0,255)),500); }	
			if (selector == 8) { Serial.println("Effect: SparkleRainbow Bubblegum IceCream"); this->creamery->SparkleRainbow(20,10); }
			if (selector == 9) { Serial.println("Effect: Rainbow Strobe"); this->creamery->rainbowStrobe(500); }
			if (selector == 10) { Serial.println("Effect: SparkleChaos1"); this->creamery->SparkleChaos1(); }
		
		} else { phase = 1; }
			
		// DoubleRainbowSparkle(20,20,100);
		// Malfunction
		// Butterfly
		// strobe white over rainbow bg
	}
}



// fill the dots one after the other with said color
// good for testing purposes
void CTRL::colorWipe(uint32_t c, uint32_t d,uint8_t wait) {
  	int i;  

	Serial.println("Beginning Effect ColorWipe...");
	// We do this at the start....
	// if (grid->orientation() == horizontal) {
	// 	int division = grid->panelY();
	// } else {
	// 	int division = panelX or panelY
	// }

	// /HARDCODE
	// division = 5;

	if (direction == desc) {
		// Descending
		for (i=0; i<this->grid->getTotal()/this->grid->pixelsY; i++) {		
			this->grid->q(i, c);
			this->grid->show();
			delay(wait);
	  	}
			
	} else {
		// Ascending
		for (i=this->grid->getTotal()/this->grid->panelsX;i>=0;i--) {
			
			this->grid->q(i, c);
			this->grid->show();
			delay(wait);
	  	}
	  	
	}

	
	
}

// Translate the LED position to Mirror the strand output. This is a custom mapping for a DJ Booth
void CTRL::mirror(int pos, uint32_t color) {
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
// void CTRL::q(int pos, uint32_t color) {		
// 
// 	if (this->mode == strand) {
// 		this->setPixelColor(pos,color);
// 	} else if (this->mode == mirrored) {
// 		// left/right mirror mode.
// 		// mirror(pos,color);
// 	} else if (division == 4) {
// 		// Radial Mode
// 		// radial(pos,color);
// 	}	
// 	if (this->mode == panel) { // Make each panel do the same thing.
// 		int p;	
// 		// Serial.println(this->orientation);
// 		
// 		if (this->orientation == horizontal) {
// 			for (int i=0;i<this->numPixels()/this->grid->panelsX;i++) {				
// 				p = this->pixelsY*pos+i;
// 				this->setPixelColor(p, color);
// 				Serial.println(p);				
// 			}
// 		} else if (this->orientation == vertical) {
// 		
// 			for (int i=0;i<this->numPixels()/this->grid-pixelsY;i++) {
// 				p = (i%2) ? (this->panelsX*i)+(this->pixelsY-1)-(pos) : (i*this->panelsX)+(pos);
// 				this->setPixelColor(p, color);		
// 			}
// 		}	
// 	}
// 				 
// }

// /======/


// void CTRL::Route()
// {
//         int spd;
//         int selected;
// 		  int intensity;
// 		  int direction;
// 		// if(DEBUG) {Serial.println(" Routing. ");Serial.println(METHOD);}
//       
//         // if(!METHOD) {return;}
// 		  if(METHOD == "chiller")
//         {
// 			// Serial.println("In Chiller Method.");
// 			spd = parseOptionNumber(root, "speed");
// 			Serial.println(spd);
//         }
//         else  if(METHOD == "chill")
//         {
//           spd = parseOptionNumber(root, "speed");
//           // mode = parseOptionString("mode");
//         }
//         else if(METHOD == "manual")
//         {
//           selected = parseOptionNumber(root, "selected"); 
//         }
// 		 else if(METHOD == "manual")
//         {
//           selected = parseOptionNumber(root, "selected"); 
//         }
// 		 
// 		  else if(!METHOD) {
// 			Serial.println(F("No method supplied ... Wait, how the hell did you get here?"));
// 		  } else {
// 			Serial.println(F("Method does not exist "));
// 			Serial.print(METHOD);
// 	  	  }
// 
// }
// 
// void CTRL::ConnectToSocket()
// {
// 	if (client.connect(server, 1337)) 
// 	{
//     	Serial.println("connected"); Serial.flush();
// 	} 
// 	else 
// 	{
//       Serial.println("Connection failed, trying again in 5 seconds.");
//       delay(5000); ConnectToSocket();
//   } 
// }
// 
// void CTRL::ReadJsonBytes()
// {
// 	while(client.connected()) {
// 	  //if you are connected and data is available
// 	  if (client.available()) {
// 	   
//             char incomingByte = (char) client.read();
//             
//             if(incomingByte == '!')  //JSON is fully loaded
//             {
// 					newJsonRequest = true;
// //					 getJson(json);
//                 root = aJson.parse(json);
// 					 //client.print(json);
// 					 memset(json, 0, BUFFER_SIZE); 
// 					 if(root) { 
// 						METHOD = parseMethod(root);
// 						parseOptions(root);
// 						
// 						/**/
// 						Route();
// 						/**/
// 					
// 					} 
//                 return;
//             }
//             else if (incomingByte == '@' || jsonBufferIndex==BUFFER_SIZE || jsonBufferIndex > BUFFER_SIZE )
//             {
// 					//@ Starts a json string, so it is a command.
// 					//Otherwise, the buffer is too big, stop now, optimize your JSON!
// 				  newJsonRequest = false;
//               if(incomingByte=='@'){ isCommand=true; } else { isCommand=false; }
//                memset(json, 0, BUFFER_SIZE); 
//                jsonBufferIndex = 0; 
//                return;
//             }
//             else if (isCommand) //Append bytes onto JSON
//             {
//               json[jsonBufferIndex] = incomingByte;
// 	      	  jsonBufferIndex++;
//               return;
//             }
// 
// 	  }
// 	}
//    if(!client.connected()) { ConnectToSocket(); }
// }
// 
// 
// 
// //void getJson(json){
// //	aJsonObject* root = aJson.parse(json);
// //}
// 
// /**
//  * Parse the Method
//  * 
//  * Refer to http://hardwarefun.com/tutorials/parsing-json-in-arduino
//  */
// String CTRL::parseMethod(aJsonObject* root) 
// {
//     //Check for method
//     if (root != NULL) {
//         //Serial.println("Parsed successfully 1 " );
//         method = aJson.getObjectItem(root, "method"); 
//         if(DEBUG) { Serial.println(method->valuestring); }
//         if(method) { return method->valuestring;  }
//     }
// 	 else {
// 		Serial.println("No root json object");
// 	  }
// }
// 
// char* CTRL::parseOptions(aJsonObject* root) 
// {
//     //Check for method
//     if (root != NULL) {
//         //Serial.println("Parsed successfully 1 " );
//         options = aJson.getObjectItem(root, "options"); 
//     }
// 	 else {
// 		Serial.println("No root json object");
// 	  }
// }
// 
// 
// /**
//  * Parse the Client ID
//  * 
//  * Refer to http://hardwarefun.com/tutorials/parsing-json-in-arduino
//  */
// int CTRL::parseClientId(aJsonObject* root) 
// {
//     //Check for client id
//     if (root != NULL) {
//         aJsonObject* id = aJson.getObjectItem(root, "id"); 
//         if(DEBUG) { Serial.println(id->valueint); }
//         if(id) {return id->valueint; }
//     }	else {
// 		Serial.println("No root json object");
// 	}
// }
// 
// /**
//  * Parse An Option String
//  * 
//  * Refer to http://hardwarefun.com/tutorials/parsing-json-in-arduino
//  */
// char* CTRL::parseOptionString(aJsonObject* root, char* target) 
// {
//     // if(DEBUG) {Serial.println("");}
//     // aJsonObject* options;
//     if (root != NULL) {
// 	
// 	    if( options == NULL ) { options = aJson.getObjectItem(root, "options"); }
// 
// 	    //Check for method
// 	    if (options != NULL) {
// 	        //Serial.println("Parsed successfully 1 " );
// 	        aJsonObject* option = aJson.getObjectItem(options, target); 
// 	        if(DEBUG) {Serial.println(option->valuestring);}
// 	        if(option) {return option->valuestring;}
// 	    }
// 
// 	} else {
// 		Serial.println("No root json object");
// 	}
// }
// 
// /**
//  * Parse An Option Int
//  * 
//  * Refer to http://hardwarefun.com/tutorials/parsing-json-in-arduino
//  */
// uint8_t CTRL::parseOptionNumber(aJsonObject* root, char* target) 
// {
//     // aJsonObject* options;
// 	
// 	if (root != NULL) {
// 	    // options = aJson.getObjectItem(root, "options");
// 	    //Check for method
// 	    if (options != NULL) {
// 	      //Serial.println("Parsed successfully 1 " );
// 	      aJsonObject* option = aJson.getObjectItem(options, target); 
// 			if(option) {return option->valueint; }
// 	    }
// 
// 	} else {
// 		Serial.println("No root json object");
// 	}
// }
// 
// 
