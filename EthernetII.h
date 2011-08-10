#ifndef ETHERNETII_H
#define ETHERNETII_H

#include "Protocol.h"

namespace ProtocolMonitor {

extern "C" {
   struct EthernetIIHdr {
      char dst[6];
      char src[6];
      uint16_t typelen;
   } __attribute__((__packed__)) ;
}

class EthernetII : public protocol_impl<EthernetII> {
   public:
      static const int MTU = 1500 ;

   public:
      EthernetII() : hdr(0), payload(0), crc(0) {}

      void Recieve( Packet& p ) ;

      Protocol* MakeCarriedType() const ;

      bool UnknownPayload() const ;
      bool FilteredPayload() const ;

      void Print( std::iostream& out ) const ;

   private:

      struct EthernetIIHdr *hdr;
      char* payload;
      uint32_t crc;
};

}

#endif
