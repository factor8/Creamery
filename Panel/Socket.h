#include <Arduino.h>
#include <Ethernet.h>

#define BUFFER_SIZE 100

class Socket {
		
	#define STRING_SIZE 30	
	enum {mthd,ky,vlu,bln,intr,flt,str};
	
  	public:
		Socket(byte* mac,byte* ip,byte* server,uint16_t port);
		
		void 
			begin(),
			readSocket();
			
		
	private:	
		EthernetClient 
			client;
		byte 
			*mac,
			*ip,
			*server;
		char 
			method[STRING_SIZE], key[STRING_SIZE], value[STRING_SIZE];
		String 
			k;
		uint8_t 
			port,vType,reading,sindex;
		bool 
			terminate;
		char 
			bite;
		int 
			last_connect;						
		void 
			connectToSocket();	
};








