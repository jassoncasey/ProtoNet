#ifndef SNIFFER_H
#define SNIFFER_H

extern "C" {
   #include <pcap.h>
}

#include "Error.h"
#include "Packet.h"

#include <tr1/unordered_map>

namespace ProtoNet {

class Sniffer;
static std::tr1::unordered_map<u_char*,Sniffer*> sniffers;

class Sniffer {

   public:

      /* Initialize with device name, timeout, max size of capture per packet,
       * and a callback function that can process individual packet receptions. 
       */ 
      Sniffer( const std::string&, int, int, void (*p)( const Packet& ) ) ;
      ~Sniffer();

      /* Start capturing packets using the filter string f
       */
      void Run( const std::string& f ) ;
      static void StopAll();
      void Stop() {
         pcap_breakloop( handle ) ;
      }
      static void Callback( u_char*, const struct pcap_pkthdr*, const u_char* ) ;
      void Process( const Packet& p ) ;

   private:
      std::string interface;
      int timeout;
      int maxcapturesize;

      void (*process)( const Packet& p );
      
      std::string filter;

      bpf_u_int32 net, mask;
      pcap_t* handle;

      std::auto_ptr<u_char> char_id ;
};

}

#endif
