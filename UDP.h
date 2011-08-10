#ifndef UDP_H
#define UDP_H

#include "Protocol.h"

namespace ProtocolMonitor {

extern "C" {

   struct UDPHdr {
      uint16_t srcp;
      uint16_t dstp;
      uint16_t length;
      uint16_t checksum;
   } __attribute__((__packed__));

}

class UDP : public Protocol {
};

}

#endif
