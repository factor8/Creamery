/* Original Code by Tom Igoe :: edited John Schimmel */

#include <SPI.h>
#include <Ethernet.h>
#include <aJSON.h>
#include "Adafruit_WS2801.h"
#include "CTRL.h"
#include "Grid.h"
//#include "TrueRandom.h"
//#include "Easing.h"

//char* parseJson(char *jsonString);

char jsonString[30];

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

boolean DEBUG = true;

int dataPin  = 2;    // White wire on Adafruit Pixels
int clockPin = 3;    // Green wire on Adafruit Pixels

// int pin = 9; //pin on arduino you want to toggle
// int pinVal = 0;

String jsonOut = "";

boolean isCommand = false;
String command; // a string to hold the incoming command
boolean commandReceived = false; // whether the command has been receive

aJsonObject* root = aJson.createObject();
//aJsonObject* id = aJson.createObject();
aJsonObject* method = aJson.createObject();
aJsonObject* options = aJson.createObject();

String METHOD;

boolean newJsonRequest = false;

#define BUFFER_SIZE 100
char json[BUFFER_SIZE];

// Initialize the Ethernet client library
// with the IP address and port of the server 
EthernetClient client;

int jsonBufferIndex = 0;
int last_connect = 0;

// ====

// Grid Vars
int panelsX = 6;
int panelsY = 1;
int pixelsX = 1;
int pixelsY = 3;
int pixelsTotal = panelsX*panelsY*pixelsX*pixelsY;

// Instantiate Controller. Num Pix Automatically Generated.
Adafruit_WS2801 *strip = new Adafruit_WS2801(pixelsTotal, dataPin, clockPin);
CTRL ctrl = CTRL(strip,panelsX,panelsY,pixelsX,pixelsY);


// CTRL ctrl = CTRL(pixelsTotal, dataPin, clockPin);
// // CTRL strip = CTRL(strip,panelsX,panelsY,pixelsX,pixelsY,1);
// Adafruit_WS2801 *strip = new Adafruit_WS2801(pixelsTotal, dataPin, clockPin);
// 
// Grid *grid = new Grid(strip,panelsX,panelsY,pixelsX,pixelsY,1);

// ====

void setup() {
  	memset(json, 0, BUFFER_SIZE); // paranoia

  	Ethernet.begin(mac, ip); // start ethernetting
  	Serial.begin(9600); //start serializing

  	delay(1000); // So we don't scare away the EthernetClient
  	ConnectToSocket();

	// Initialize Controller and turn off LEDS.
	strip->begin();
	strip->show();
 
}

void loop()
{
	// ReadJsonBytes(); //On success, calls Route with method. Every effect needs some routing.
	ctrl.render();
	// We need this here too so that we can work without the connection
}


void Route()
{
	int spd;
	int selected;
 	int intensity;
 	int direction;
	// if(DEBUG) {Serial.println(" Routing. ");Serial.println(METHOD);}
   
     // if(!METHOD) {return;}
 	if(METHOD == "chiller")
	{
		// Serial.println("In Chiller Method.");
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
    	Serial.println("connected"); Serial.flush();
	} 
}

void ReadJsonBytes(){
	
	while(client.connected()) {
	  //if you are connected and data is available
	  if (client.available()) {
	   
            char incomingByte = (char) client.read();
            
            if(incomingByte == '!')  //JSON is fully loaded
            {
					newJsonRequest = true;
//					 getJson(json);
                root = aJson.parse(json);
					 //client.print(json);
					 memset(json, 0, BUFFER_SIZE); 
					 if(root) { 
						METHOD = parseMethod(root);
						parseOptions(root);
						
						/**/
						Route();
						/**/
					
					} 
                return;
            }
            else if (incomingByte == '@' || jsonBufferIndex==BUFFER_SIZE || jsonBufferIndex > BUFFER_SIZE )
            {
					//@ Starts a json string, so it is a command.
					//Otherwise, the buffer is too big, stop now, optimize your JSON!
				  newJsonRequest = false;
              if(incomingByte=='@'){ isCommand=true; } else { isCommand=false; }
               memset(json, 0, BUFFER_SIZE); 
               jsonBufferIndex = 0; 
               return;
            }
            else if (isCommand) //Append bytes onto JSON
            {
              json[jsonBufferIndex] = incomingByte;
	      	  jsonBufferIndex++;
              return;
            }

	  }
	}
   if(millis() > last_connect+5000 && !client.connected()) { 
		ConnectToSocket(); 	
	} else {	
		Serial.println("Connection failed, trying again in 5 seconds.");
		last_connect = millis();
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
String parseMethod(aJsonObject* root) 
{
    //Check for method
    if (root != NULL) {
        //Serial.println("Parsed successfully 1 " );
        method = aJson.getObjectItem(root, "method"); 
        if(DEBUG) { Serial.println(method->valuestring); }
        if(method) { return method->valuestring;  }
    }
	 else {
		Serial.println("No root json object");
	  }
}

char* parseOptions(aJsonObject* root) 
{
    //Check for method
    if (root != NULL) {
        //Serial.println("Parsed successfully 1 " );
        options = aJson.getObjectItem(root, "options"); 
    }
	 else {
		Serial.println("No root json object");
	  }
}


/**
 * Parse the Client ID
 * 
 * Refer to http://hardwarefun.com/tutorials/parsing-json-in-arduino
 */
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
 */
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
 */
uint8_t parseOptionNumber(aJsonObject* root, char* target) 
{
    // aJsonObject* options;
	
	if (root != NULL) {
	    // options = aJson.getObjectItem(root, "options");
	    //Check for method
	    if (options != NULL) {
	      //Serial.println("Parsed successfully 1 " );
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