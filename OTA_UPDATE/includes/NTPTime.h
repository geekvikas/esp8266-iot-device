#ifndef NTPTime_h
#define NTPTime_h

#include <WiFiUdp.h>

class NTPTimeClass {
private:
	unsigned int localPort = 2390;      // local port to listen for UDP packets

	/* Don't hardwire the IP address or we won't get the benefits of the pool.
	 *  Lookup the IP address for the host name instead */
	//IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server
	IPAddress timeServerIP; // time.nist.gov NTP server address

	const char* ntpServerName = "time.nist.gov";

	static const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

	byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

	// A UDP instance to let us send and receive packets over UDP
	WiFiUDP udp;
	unsigned long sendNTPpacket(IPAddress&);
	
public:
	unsigned long  SecsSince1900();
	
};

extern NTPTimeClass NTPTime;

#endif