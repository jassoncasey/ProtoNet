#ifndef IPV4_H
#define IPV4_H

#include "Protocol.h"

namespace ProtocolMonitor {

extern "C" {
   struct IPv4Hdr {
      #ifdef NETBYTE
         uint16_t  version:4;
         uint16_t  ihl:4;
      #else
         uint16_t  ihl:4;
         uint16_t  version:4;
      #endif
      uint16_t  tos_pres:3;
      uint16_t  tos_delay:1;
      uint16_t  tos_throughput:1;
      uint16_t  tos_reliability:1;
      uint16_t  pad1:2;
      uint16_t length;
      
      uint16_t identification;
      uint16_t  pad2:1;
      uint16_t  dontfrag:1;
      uint16_t  morefrag:1;
      uint16_t frag_offset:13;
      
      uint16_t  ttl:8;
      uint16_t  protocol:8;
      uint16_t checksum;
      
      uint32_t src;
      uint32_t dst;
      
   } __attribute__((__packed__));;
}

class IPv4 : public Protocol<IPv4> {
   public:
   private:
};

}

#endif
