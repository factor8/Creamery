// #include <SPI.h>
// #include <Adafruit_WS2801.h>
#include <Test.h>

#define	DATAPIN		2 // Data pin for serial communication to shift registers
#define	CLOCKPIN	3 // Clock pin for serial communication to shift registers

void setup() {
	Serial.begin(9600);
	Serial.println("begin");
	Serial.println(testint);
	testint = 19;
}
void loop() {



}

