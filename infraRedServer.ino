#include <Ethernet.h>
#include <SPI.h>

#define MaxHeaderLength 16    //maximum length of http header required

#include <IRremote.h>

IRsend irsend;

// Conversion table
unsigned long source1	= 0xC02;

unsigned long source2	= 0xC05;

unsigned long source3	= 0xC03;

unsigned long source4	= 0xC01;

unsigned long source5	= 0xC04;

unsigned long sourceUSB	= 0xC00;

unsigned long volumeUp	= 0xC10;

unsigned long volumeDown	= 0xC11;

unsigned long powerOn	= 0xC0E;

unsigned long powerOff	= 0xC0F;


////////////////////////////////////////////////////////////////////////
//CONFIGURE
////////////////////////////////////////////////////////////////////////
 
  //IP manual settings
  byte ip[] = { 192, 168, 1, 50 };   //Manual setup only
  byte gateway[] = { 192, 168, 1, 254 }; //Manual setup only
  byte subnet[] = { 255, 255, 255, 0 }; //Manual setup only

  // if need to change the MAC address (Very Rare)
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

  //Ethernet Port
  EthernetServer server = EthernetServer(80); //default html port 80


// Variable declaration
  String currentState = " ";
  String HTTP_req;
  
  String HttpHeader = String(MaxHeaderLength); 
  
//Beginning of the program
void setup(){
  Serial.begin(9600);
  Serial.println("init");
  //Setting up the IP address. Comment out the one you dont need.
  //Ethernet.begin(mac); //for DHCP address. (Address will be printed to serial.)
  Ethernet.begin(mac, ip, gateway, subnet); //for manual setup. (Address is the one configured above.)

  //initialize variable
  HttpHeader="";
}

void loop(){

EthernetClient client = server.available();  // try to get client

    if (client) {  // got client?
      Serial.println("client");
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {   // client data available to read
                char c = client.read(); // read 1 byte (character) from client
                HTTP_req += c;  // save the HTTP request 1 char at a time
                // last line of client request is blank and ends with \n
                // respond to client only after last line received
                if (c == '\n' && currentLineIsBlank) {
                    // send a standard http response header
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: keep-alive");
                    client.println();
                    // AJAX request for switch state
                    if (HTTP_req.indexOf("powerOn") > -1) {
						IRTrigger(powerOn);
						Serial.println("powerOn");
						client.println("powerOn from arduino");
					}                    
                    else if (HTTP_req.indexOf("powerOff") > -1) {
                        IRTrigger(powerOff);
						Serial.println("powerOff");
						client.println("powerOff");
                    }
                    else if (HTTP_req.indexOf("volumeUp") > -1) {
                        IRTrigger(volumeUp);
						Serial.println("volumeUp");
						client.println("volumeUp");
                    }
					else if (HTTP_req.indexOf("volumeDown") > -1) {
                        IRTrigger(volumeDown);
						Serial.println("volumeDown");
						client.println("volumeDown");
                    }
					else if (HTTP_req.indexOf("source1") > -1) {
                        IRTrigger(source1);
						Serial.println("source1");
						client.println("source1");
                    }
					else if (HTTP_req.indexOf("source2") > -1) {
                        IRTrigger(source2);
						Serial.println("source2");
						client.println("source2");
                    }
					else if (HTTP_req.indexOf("source3") > -1) {
                        IRTrigger(source3);
						Serial.println("source3");
						client.println("source3");
                    }
					else if (HTTP_req.indexOf("source4") > -1) {
                        IRTrigger(source4);
						Serial.println("source4");
						client.println("source4");
                    }
					else if (HTTP_req.indexOf("source5") > -1) {
                        IRTrigger(source5);
						Serial.println("source5");
						client.println("source5");
                    }
					else if (HTTP_req.indexOf("sourceUSB") > -1) {
                        IRTrigger(sourceUSB);
						Serial.println("sourceUSB");
						client.println("sourceUSB");
                    }
                    else {  
                        client.println("no argument received");                        
                    }
                    // display received HTTP request on serial port
                    Serial.print(HTTP_req);
                    HTTP_req = "";            // finished with request, empty string
                    break;
                }
                // every line of text received from the client ends with \r\n
                if (c == '\n') {
                    // last character on line of received text
                    // starting new line with next character read
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') {
                    // a text character was received from client
                    currentLineIsBlank = false;
                }
            } // end if (client.available())
        } // end while (client.connected())
        delay(1);      // give the web browser time to receive the data
        client.stop(); // close the connection
    } // end if (client)
}

void IRTrigger(unsigned long command) {
	for (int i = 0; i < 3; i++) {
		irsend.sendRC5(command, 12);
		delay(114);
	}
	delay(400); //1 second delay between each signal burst
	return;
}
