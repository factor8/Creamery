/* Original Code by Tom Igoe :: edited John Schimmel */

#include <SPI.h>
#include <Ethernet.h>
#include "Adafruit_WS2801.h"
#include "CTRL.h"
#include "Grid.h"
#include "TrueRandom.h"
//#include "Easing.h"

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

//your arduino's IP address might need to change depending on your network
byte ip[] = { 
  192,168,1,9 };

// IMPORTANT
// CHANGE THE SERVER IP ADDRESS
byte server[] = {
  192,168,1,69 };

int dataPin  = 2;    // White wire on Adafruit Pixels
int clockPin = 3;    // Green wire on Adafruit Pixels

// Initialize the Ethernet client library
// with the IP address and port of the server 
// EthernetClient client;

#define STRING_SIZE 30

//Cache Variables for building data
char 
	method[STRING_SIZE], key[STRING_SIZE], value[STRING_SIZE];
String k;
uint8_t 
	vType,reading,sindex;
enum 
	{mthd,ky,vlu,bln,intr,flt,str};
bool 
	terminate = false;
char bite;

int last_connect = 0;

// ====

// Grid Vars
int panelsX = 9;
int panelsY = 1;
int pixelsX = 1;
int pixelsY = 9;
int pixelsTotal = panelsX*panelsY*pixelsX*pixelsY;

// Instantiate Controller. Num Pix Automatically Generated.
Adafruit_WS2801 *strip = new Adafruit_WS2801(pixelsTotal, dataPin, clockPin);
CTRL ctrl = CTRL(strip,panelsX,panelsY,pixelsX,pixelsY);


uint8_t r,g,b;
uint32_t color;

boolean DEBUG = true;

// ====

void setup() {
  	// memset(json, 0, BUFFER_SIZE); // paranoia

  	Serial.begin(9600); //start serializing
	Serial.println("Setting Up");

  	// Ethernet.begin(mac, ip); // start ethernetting	
  	// delay(1000); // So we don't scare away the EthernetClient
  	// ConnectToSocket();

	// Initialize Controller and turn off LEDS.
	strip->begin();
	strip->show();
	
	Serial.println("Ending Setup...");	
}

void loop()
{
	// Serial.println("Starting Loop...");
	// readSocket();
	
	Serial.println(TrueRandom.random(0,255));
	
	// ctrl.step();
			
	// We need this here too so that we can work without the connection
	Serial.println("running....");
}

/*
void Route()
{
	int spd;
	int selected;
 	int intensity;
 	int direction;
	// if(DEBUG) {Serial.println(" Routing. ");Serial.println(METHOD);}
   
     // if(!METHOD) {return;}
 	if(METHOD == "ColorChange")
	{
		Serial.println("In ColorChange Method.");
		spd = parseOptionNumber(root, "speed");
		
		Serial.println(spd);
    }
     else if(METHOD == "chill")
     {
	spd = parseOptionNumber(root, "speed");
       	// mode = parseOptionString("mode");
     }
     	else if(METHOD == "manual")
     {
       selected = parseOptionNumber(root, "selected"); 
     }
else if(METHOD == "manual")
     {
       selected = parseOptionNumber(root, "selected"); 
     }

 else if(!METHOD) {
Serial.println(F("No method supplied ... Wait, how the hell did you get here?"));
 } else {
Serial.println(F("Method does not exist "));
Serial.print(METHOD);
	  }

}

void ConnectToSocket()
{
	if (client.connect(server, 1337)) 
	{
    	Serial.println("--+++== Connected! ==+++--"); ///Serial.flush();
	} else {
		Serial.println("--- Connection failed, trying again in 5 seconds.");
	}
}


void readSocket() {
	
	while(client.connected()) { //if (DEBUG) Serial.print("Connected...");	
		
	  	//if you are connected and data is available
		if (client.available()) { 				
			// if (DEBUG) Serial.print(" Available...");	
			
			bite = (char)client.read();
			
			// if (DEBUG) Serial.println(bite);
			
			// Flag termination, happens second most often.
		  	if (bite == ';') {
				if (DEBUG) Serial.println("Reading End ';' ...");	
				terminate = true;
				// return;
				
		   // Keys happen Often
			} else if(bite=='$') {
				if (DEBUG) Serial.println("Reading Key '$' ...");	
				if (reading == mthd || reading == ky) {
					reading = ky; 
				}
		 	}
		  //So do Values
		  //I've replaced the following rubbish line with the following uncommented lines.
		  //They only make sense if you look at the closely. Search vType.
			//If it is a value.
		   else if (bite == '^') {
				if (DEBUG) Serial.println("Reading Value '^' ...");	
				//flag 
				reading = vlu;
				if (DEBUG) Serial.println("Reading is set to 'vlu' ...");	

			} else if (bite == '!' || bite == '#' || bite == '~' || bite == '%') {	
				// @method;$num;^#int

				if (bite == '!') vType = bln;
				if (bite == '#') vType = intr;
				if (bite == '~') vType = str;
				if (bite == '%') vType = flt;

		    //Methods happen first but least often
		   } else if (bite=='@') {
				if (DEBUG) Serial.println("Reading Method '@' ...");	
				reading = mthd;        

			//END: FLAGS AND MODIFIERS

			//BEGIN : READING / WRITING

			} else if (reading) { // We are presently reading data between two flags.
				if (DEBUG) Serial.print(bite);		
				if (reading == mthd) {
					method[sindex] = bite;
				} else if (reading == ky) {
					key[sindex] = bite;
				} else if (reading == vlu) {
					value[sindex] = bite;
				}					
				sindex++;				
			}
			
			//
			// @Terminate, 
			// lets transfer data from cache into effect scope.
			//		   
			
			if (terminate) {
				if (DEBUG) Serial.println("=== Terminating === ");	
				
				//This is still reading something.
								
				if (reading != 0) {
						
					if (reading == mthd) {
						if (DEBUG) Serial.println("== Updating Method ==");
						ctrl.method = method; //Set current method. 

						memset(method,0, STRING_SIZE); // Clear method cache
						// method = ''; 

			 		} else if(reading == ky) { // Do nothing, wait for value;
						if (DEBUG) Serial.println("== Key Seen ==");
						k = key;
						

					} else if(reading == vlu) {
						if (DEBUG) Serial.println("== VALUE SEEN =="); Serial.println("Key is: "); Serial.println(key);
						if (k == "freq") { ctrl.frequency = atoi(value); if (DEBUG) Serial.println("== Updating CTRL Freq ==");
						} else if (k == "sust") {ctrl.sustain = atoi(value); if (DEBUG) Serial.println("== Updating CTRL Sust ==");
						} else if (k == "r") { ctrl.r = atoi(value); if (DEBUG) Serial.println("== Updating CTRL R ==");
						} else if (k == "g") { ctrl.g = atoi(value); if (DEBUG) Serial.println("== Updating CTRL G ==");
						} else if (k == "b") { ctrl.b = atoi(value); if (DEBUG) Serial.println("== Updating CTRL B =="); } 
						
						
						
								
						//Reset the key and value caches.
						// We want to reset this now, because a key will always have a value.
						memset(key,0, STRING_SIZE);
						memset(value,0, STRING_SIZE);

						vType = 0; // So now on next run no longer setting 'reading' to value;
						reading = 0; // ?
		 			}
					
				} else {
					if (DEBUG) Serial.println("For some reason READING is 0 inside Terminate loop...");	
				} 
				
				terminate = false;
				// Reset the string index.
				sindex = 0;	
			}
		}	
		ctrl.step();		
	}
	if (!client.connected()) { 
		if (millis() > last_connect+5000) {
			// Serial.println(millis());
			// Serial.println(last_connect+5000);
   		ConnectToSocket(); 	
			last_connect = millis();
		}
  	}
}

/*
void ReadJsonBytes(){
	
	while(client.connected()) {
		if (DEBUG) Serial.print("Connected...");	
	  	//if you are connected and data is available
		if (client.available()) {
			if (DEBUG) Serial.print(" Available...");	
			char incomingByte = (char) client.read();
            
			if(incomingByte == '!') {
					// JSON is fully loaded 
				if (DEBUG) Serial.print(" Exclaim!...");		
				newJsonRequest = true;
				// getJson(json);
				root = aJson.parse(json);
					
				client.print(json);
				memset(json, 0, BUFFER_SIZE);
				
				if(root) { 
					if (DEBUG) Serial.print(" Root!...");		
					METHOD = parseMethod(root);
					parseOptions(root);
				
					if (DEBUG) Serial.println("-- We doin it! ->");
					if (DEBUG) Serial.println(METHOD);
					
					resetflag = true;

				} 
				return;
			} else if (incomingByte == '@' || jsonBufferIndex==BUFFER_SIZE || jsonBufferIndex > BUFFER_SIZE ) {
				
				if (DEBUG) Serial.print(" @JSON STRING@...");	
			
				//@ Starts a json string, so it is a command.
				//Otherwise, the buffer is too big, stop now, optimize your JSON!
				newJsonRequest = false;
				
				if(incomingByte=='@'){ isCommand=true; } else { isCommand=false; }

				memset(json, 0, BUFFER_SIZE); 
				jsonBufferIndex = 0; 
				return;
			} else if (isCommand) { //Append bytes onto JSON
				if (DEBUG) Serial.print(" ... Reading: ");
				if (DEBUG) Serial.println(incomingByte);	
				json[jsonBufferIndex] = incomingByte;
				jsonBufferIndex++;
				return;
			} else {
				if (resetflag) {					
					/// reset the vars here.
					Serial.flush();
					resetflag = false;					
				};
			}
	  	}
		ctrl.step();
	}
	if (!client.connected()) { 
		if (millis() > last_connect+5000) {
			// Serial.println(millis());
			// Serial.println(last_connect+5000);
   		ConnectToSocket(); 	
			last_connect = millis();
		}
  	}
}



//void getJson(json){
//	aJsonObject* root = aJson.parse(json);
//}

/**
 * Parse the Method
 * 
 * Refer to http://hardwarefun.com/tutorials/parsing-json-in-arduino
 */
// String parseMethod(aJsonObject* root) 
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
// char* parseOptions(aJsonObject* root) 
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


/**
 * Parse the Client ID
 * 
 * Refer to http://hardwarefun.com/tutorials/parsing-json-in-arduino
 *
int parseClientId(aJsonObject* root) 
{
    //Check for client id
    if (root != NULL) {
        aJsonObject* id = aJson.getObjectItem(root, "id"); 
        if(DEBUG) { Serial.println(id->valueint); }
        if(id) {return id->valueint; }
    }	else {
		Serial.println("No root json object");
	}
}

/**
 * Parse An Option String
 * 
 * Refer to http://hardwarefun.com/tutorials/parsing-json-in-arduino
 *
char* parseOptionString(aJsonObject* root, char* target) 
{
    // if(DEBUG) {Serial.println("");}
    // aJsonObject* options;
    if (root != NULL) {
	
	    if( options == NULL ) { options = aJson.getObjectItem(root, "options"); }

	    //Check for method
	    if (options != NULL) {
	        //Serial.println("Parsed successfully 1 " );
	        aJsonObject* option = aJson.getObjectItem(options, target); 
	        if(DEBUG) {Serial.println(option->valuestring);}
	        if(option) {return option->valuestring;}
	    }

	} else {
		Serial.println("No root json object");
	}
}

/**
 * Parse An Option Int
 * 
 * Refer to http://hardwarefun.com/tutorials/parsing-json-in-arduino
 *
uint8_t parseOptionNumber(aJsonObject* root, char* target) 
{
    aJsonObject* options;
	
	if (root != NULL) {
	    options = aJson.getObjectItem(root, "options");
	    //Check for method
	    if (options != NULL) {
	      // Serial.println("Parsed successfully" );
	      aJsonObject* option = aJson.getObjectItem(options, target); 
			if(option) {return option->valueint; }
	    }

	} else {
		Serial.println("No root json object");
	}
}


/**
 * Parse An Option Boolean
 * 
 * Refer to http://hardwarefun.com/tutorials/parsing-json-in-arduino
* if(option) {return option->valuebool; }
 */


/**
 * Parse An Option Float
 * 
 * Refer to http://hardwarefun.com/tutorials/parsing-json-in-arduino
* if(option) {return option->valuefloat; }
 */