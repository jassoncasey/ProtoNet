#include "Sniffer.h"

Sniffer::Sniffer( const std::string& i, int to, int mcs,
                  void (*p)( const Packet& ) ) : interface(i),
                  timeout(to), maxcapturesize(mcs), process(p) {

   char errbuf[PCAP_ERRBUF_SIZE];

   // Find the network address and mask of the listening device
   if ( pcap_lookupnet( interface.c_str(), &net, &mask, errbuf) == -1 ) {
      Error error( "Failed to get network and mask of device: " );
      error << interface ;
      throw error ; 
   }

   // Open the device for recording
   handle = pcap_open_live(interface.c_str(), maxcapturesize, 1, timeout, errbuf);
   if ( handle == 0 ) {
      Error error( "Could not open device: " ) ;
      error << interface << std::endl << "Error: " << errbuf << std::endl;
      throw error ;
   }
   
}

Sniffer::~Sniffer() {
   pcap_close( signal_handle ) ;
}

void Sniffer::Callback( u_char *args, const struct pcap_pkthdr *hdr, const u_char *pkt ) {
   // Is this a truncated packet 
   if ( hdr->caplen < hdr->len )
      process( Packet( (uint8_t*)pkt, (int)hdr->caplen, Time( hdr->ts )), true ) ;
   else
      process( Packet( (uint8_t*)pkt, (int)hdr->caplen, Time( hdr->ts )) ) ;
}

void Run( const std::string& f ) {
   filter = f ;

   struct bpf_program fp;
   if ( pcap_compile( handle, &fp, filter.c_str(), 0, net ) == -1 ) {
      Error error( " Failed to compile packet filter" ) ;
      error << std::endl << "Filter: " << filter << std::endl;
      error << "Error: " << pcap_geterr( handle ) << std::endl;

      throw error ;
   }

   // Apply the filter
   if ( pcap_setfilter( handle, &fp ) == -1 ) {
      Error error( "Failed to install packet filter" ) ;

      throw error ;
   }
  
   // Put recorder into a dispatch loop
   if ( pcap_loop( handle, 0, Callback, 0 ) == -1 ) {
      Error error( "Failed to dispatch callback" );
      error << std::endl << "Error: " << pcap_geterr( handle ) << std::endl;

      throw error ;
   }
   

}
