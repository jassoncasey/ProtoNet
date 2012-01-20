#ifndef SNIFFER_H
#define SNIFFER_H

extern "C" {
   #include <pcap.h>
}

#include "Error.h"
#include "Packet.h"

namespace ProtoNet {

class Sniffer {

   public:
      /* Initialize with device name, timeout, max size of capture per packet,
       * and a callback function that can process individual packet receptions. 
       */ 
      Sniffer( const std::string&, int, int, void (*p)( Sniffer *hdl, 
               const Packet& ) ) ;
      ~Sniffer();

      /* Start capturing packets using the filter string f
       */
      void Run( const std::string& f ) ;
      static void StopAll();
      void Stop() {
         pcap_breakloop( handle ) ;
      }
      static void Callback( u_char*, const struct pcap_pkthdr*, 
                              const u_char* ) ;
      void Process( const Packet& p ) ;

   private:
      std::string interface;
      int timeout;
      int maxcapturesize;

      void (*process)( Sniffer *hdl, const Packet& p );
      
      std::string filter;

      bpf_u_int32 net, mask;
      pcap_t* handle;

      std::string char_id ;
};

}

#endif
