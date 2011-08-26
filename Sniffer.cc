#include "Sniffer.h"

Sniffer::Sniffer( const std::string& d, int to, int ms,
                  void (*)() r, void (*)() f ) : device(d),
                  timeout(to), maxpacketsize(ms),recieve(r), 
                  finish(f) {

   char errbuf[PCAP_ERRBUF_SIZE];

   // Find the network address and mask of the listening device
   if ( pcap_lookupnet( dev, &net, &mask, errbuf) == -1 ) {
      std::cerr << "Failed to get network and mask of device: ";
      std::cerr << dev << std::endl;
      throw 1;
   }

   // Open the device for recording
   handle = pcap_open_live(dev, MaxPacketSize, 1, 1000, errbuf);
   if ( handle == 0 ) {
      std::cerr << "Could not open device: " << dev << std::endl;
      std::cerr << "Error: " << errbuf << std::endl;
      throw 1;
   }
   
}

Sniffer::~Sniffer() {
   pcap_close( signal_handle ) ;
   // Possibly a terrible idea
   finish() ;
}

void UpdateFilter( const std::string& f ) {
}
