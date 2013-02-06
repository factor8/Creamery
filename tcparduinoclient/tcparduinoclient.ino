/*
Original Code by Tom Igoe
edited John Schimmel
 
 */

#include <SPI.h>
#include <Ethernet.h>
#include <Adafruit_WS2801.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

//your arduino's IP address might need to change depending on your network
byte ip[] = { 
  192,168,1,9	 };

// IMPORTANT
// CHANGE THE SERVER IP ADDRESS
byte server[] = {
  192,168,1,69 };

int dataPin  = 2;     // Yellow wire on Adafruit Pixels
int clockPin = 3;    // Green wire on Adafruit Pixels



// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
Adafruit_WS2801 strip = Adafruit_WS2801(144, dataPin, clockPin);

// int pin = 9; //pin on arduino you want to toggle
int pinVal = 0;

// Initialize the Ethernet client library
// with the IP address and port of the server 
EthernetClient client;

void setup() {
  // start the Ethernet connection:
  Ethernet.begin(mac, ip);
  // start the serial library:
  Serial.begin(9600);

	strip.begin();
	
	int i;
	for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Color(0,0,0));
  }
	strip.show();

  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 1337)) {
    Serial.println("connected");	
  } 
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }

  // pinMode(pin, OUTPUT);
}

void loop()
{
  
  //if you are connected and data is available
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
		
    // '1' was received, return '1' for HIGH
    if (c == '1') {
      // pinVal = HIGH;
      client.print('1');
			int i;
			for (i=0; i < strip.numPixels(); i++) {
		      strip.setPixelColor(i, Color(255,255,255));
		  }
			strip.show();
			Serial.println("Lights on");
    } 
    else if (c == '0') {
      // pinVal = LOW;
      client.print('0'); 
			int i;
			for (i=0; i < strip.numPixels(); i++) {
		      strip.setPixelColor(i, Color(0,0,0));
		  }
			strip.show();
			Serial.println("Lights off");
    }
    
    //turn led pin to new position
    // digitalWrite(pin, pinVal);

    
  } else {
	
	}

}


void ColorWipe(uint32_t c, uint8_t wait) {
  int i;

  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
uint32_t Color(byte r, byte g, byte b)
{
	uint32_t c;
	c = r;
	c <<= 8;
	c |= g;
	c <<= 8;  
	c |= b;
	
  	return c;
}