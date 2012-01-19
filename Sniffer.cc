#include "Sniffer.h"

#include <sstream>

namespace ProtoNet {

Sniffer::Sniffer( const std::string& i, int to, int mcs,
                  void (*p)( Sniffer *hdl, const Packet& ) ) : interface(i),
                  timeout(to), maxcapturesize(mcs) {

   char errbuf[PCAP_ERRBUF_SIZE];

   Sniffer::process = p ;

   // Find the network address and mask of the listening device
   if ( pcap_lookupnet( interface.c_str(), &net, &mask, errbuf ) == -1 ) {
      // Error error( "Failed to get network and mask of device: " );
      Error error( errbuf );
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
  
   std::stringstream ss;
   ss << handle ;
   char_id.reset( (u_char*) strdup( ss.str().c_str() ) ) ;
}

Sniffer::~Sniffer() {
   pcap_close( handle ) ;
}

void Sniffer::Callback( u_char *args, const struct pcap_pkthdr *hdr, const u_char *pkt ) {
   std::tr1::unordered_map<u_char*,Sniffer*>::iterator itr;
   itr = sniffers.find( args );
   if ( itr == sniffers.end() )
      return;

   Sniffer* sniffer = (*itr).second ;

   // Is this a truncated packet 
   if ( hdr->caplen < hdr->len )
      sniffer->Process( Packet( (uint8_t*)pkt, (int)hdr->caplen, Time( hdr->ts ), true ) ) ;
   else
      sniffer->Process( Packet( (uint8_t*)pkt, (int)hdr->caplen, Time( hdr->ts )) ) ;
}

void Sniffer::Process( const Packet& p ) {
   process( this, p ) ;
}

void Sniffer::StopAll() {
   std::tr1::unordered_map<u_char*,Sniffer*>::iterator itr;
   for( itr = sniffers.begin(); itr != sniffers.end(); ++itr ) {
      (*itr).second->Stop() ;
   }
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

   // Set self into the map
   sniffers[ char_id.get() ] = this ;
   if ( pcap_loop( handle, 0, Sniffer::Callback, char_id.get() ) == -1 ) {
      Error error( "Failed to dispatch callback" );
      error << "\n" << "Error: " << pcap_geterr( handle ) << "\n";

      throw error ;
   }
   

}

}
