#include "Sniffer.h"

namespace ProtoNet {

bool Sniffer::inuse = false ;
void (*Sniffer::process)( const Packet& p ) = 0 ;

Sniffer::Sniffer( const std::string& i, int to, int mcs,
                  void (*p)( const Packet& ) ) : interface(i),
                  timeout(to), maxcapturesize(mcs) {

   char errbuf[PCAP_ERRBUF_SIZE];

   if ( Sniffer::inuse ) {
      Error error("Only one sniffer in use at a time");
      throw error ;
   }
   else
      Sniffer::inuse = true ;

   Sniffer::process = p ;

   // Find the network address and mask of the listening device
   if ( pcap_lookupnet( interface.c_str(), &net, &mask, errbuf ) == -1 ) {
      Error error( "Failed to get network and mask of device: " );
      error << interface ;
      throw error ; 
   }

   // Open the device for recording
   handle = pcap_open_live(interface.c_str(), maxcapturesize, 1, timeout, errbuf);
   if ( handle == 0 ) {
      Error error( "Could not open device: " ) ;
      error << interface << "\n" << "Error: " << errbuf << "\n" ;
      throw error ;
   }
   
}

Sniffer::~Sniffer() {
   pcap_close( handle ) ;
   Sniffer::inuse = false ;
   Sniffer::process = 0 ;
}

void Sniffer::Callback( u_char *args, const struct pcap_pkthdr *hdr, const u_char *pkt ) {
   // Is this a truncated packet 
   if ( hdr->caplen < hdr->len )
      process( Packet( (uint8_t*)pkt, (int)hdr->caplen, Time( hdr->ts ), true ) ) ;
   else
      process( Packet( (uint8_t*)pkt, (int)hdr->caplen, Time( hdr->ts )) ) ;
}

void Sniffer::Run( const std::string& f ) {
   filter = f ;

   struct bpf_program fp;
   if ( pcap_compile( handle, &fp, filter.c_str(), 0, net ) == -1 ) {
      Error error( " Failed to compile packet filter" ) ;
      error << "\n" << "Filter: " << filter << "\n" ;
      error << "Error: " << pcap_geterr( handle ) << "\n" ;

      throw error ;
   }

   // Apply the filter
   if ( pcap_setfilter(handle, &fp ) == -1 ) {
      Error error( "Failed to install packet filter" ) ;

      throw error ;
   }
  
   // Put recorder into a dispatch loop
   if ( pcap_loop( handle, 0, Sniffer::Callback, 0 ) == -1 ) {
      Error error( "Failed to dispatch callback" );
      error << "\n" << "Error: " << pcap_geterr( handle ) << "\n";

      throw error ;
   }
   

}

}
