#ifndef NTPTime_h
#define NTPTime_h

#include <WiFiUdp.h>
#include <ESP8266WiFi.h>

class NTPTimeClass {
private:
	unsigned int localPort = 2390;      // local port to listen for UDP packets
  const char* ntpServerName = "time.nist.gov";
    
	/* Don't hardwire the IP address or we won't get the benefits of the pool.
	 *  Lookup the IP address for the host name instead */
	//IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server
	IPAddress timeServerIP; // time.nist.gov NTP server address

	// A UDP instance to let us send and receive packets over UDP
	WiFiUDP udp;
	unsigned long sendNTPpacket(IPAddress&);
	
public:
	unsigned long SecsSince1900();
	
};

extern NTPTimeClass NTPTime;

#endif
