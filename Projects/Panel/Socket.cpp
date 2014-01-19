#include "Socket.h"
#include <Ethernet.h>

// bool DEBUG = true;
/*
Socket::Socket(byte* mac,byte* ip,byte* server,uint16_t port) {	
	
	// Enter a MAC address and IP address for your controller below.
	// The IP address will be dependent on your local network:
	// this->mac = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
	this->mac = mac;

	//your arduino's IP address might need to change depending on your network
	// this->ip = { 192,168,1,9 };
	this->ip = ip;
	
	this->server = server;
	this->port = port;

	this->terminate = false;
	this->last_connect = 0;

}

// Use for generic Setter
// void Socket::setSelector(uint16_t s) {
// 	Serial.println("Calling setSelector");
// 	this->selector = s;
// }

void Socket::begin() {
	// Connect to Socket	
	Ethernet.begin(mac, ip); // start ethernetting	
	delay(1000);
	this->connectToSocket();	
}


void Socket::connectToSocket()
{
	if (this->client.connect(this->server, this->port)) 
	{
    	Serial.println("connected"); ///Serial.flush();
	} else {
		Serial.println("Connection failed, trying again in 5 seconds.");
	}
}

void Socket::readSocket(){
		
	if(client.connected()) { //if (DEBUG) Serial.print("Connected...");	
		
	  	//if you are connected and data is available
		if (client.available()) { // if (DEBUG) Serial.print(" Available...");	
					
			bite = (char)client.read();
			
			// Flag termination, happens second most often.
		  	if (bite == ';') {
				if (DEBUG) Serial.println("Reading End ';' ...");	
				terminate = true;			
				
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
*/