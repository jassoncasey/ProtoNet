#ifndef SNIFFER_H
#define SNIFFER_H

extern "C" {
   #include <pcap.h>
   #include <signal.h>
}

#include <string>

class PCapError : public Error {} ;

class Sniffer {

   public:

      /* Initialize with device name, timeout, max size of capture per packet,
       * and a callback function that can process individual packet receptions. 
       */ 
      Sniffer( const std::string&, int, int, void (*p)( const Packet& ) ) ;
      ~Sniffer();

      void Run( const std::string& f ) ;
      void Callback( u_char*, const struct pcap_pkthdr*, const u_char* ) ;

   private:
      std::string interface;
      int timeout;
      int maxcapturesize;

      void (*process)( const Packet& p );
      
      std::string filter;

      bpf_u_int32 net, mask;
      pcap_t* handle;
};

#endif
