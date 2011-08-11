// Written by Jasson Casey
// Copyright (C) 2011. All rights reserved.

#ifndef ETHERNETII_H
#define ETHERNETII_H

#include "Protocol.h"

namespace ProtoNet {

extern "C" {
   struct EthernetIIHdr {
      uint8_t dst[6];
      uint8_t src[6];
      uint16_t typelen;
   } __attribute__((__packed__)) ;
}

class EthernetII : public Protocol {
   public:
      static const int MTU = 1500 ;

   public:
      EthernetII() : hdr(0), payload(0), crc(0) {}

      void Recieve( Packet& p ) ;
      int GetMTU() const { return MTU ; }

      Protocol* MakeCarriedType() const ;

      bool UnknownPayload() const ;
      bool FilteredPayload() const ;

      void Print( std::ostream& out ) const ;

   private:

      struct EthernetIIHdr *hdr;
      uint8_t* payload;
      uint32_t crc;
};

}

#endif
