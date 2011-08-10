// Written by Jasson Casey
// Copyright (C) 2011. All rights reserved.

#ifndef TCP_H
#define TCP_H

#include "Protocol.h"

namespace ProtocolMonitor {

extern "C" {
   struct TCPHdr {
      uint16_t srcp;
      uint16_t dstp;
      uint32_t seq;
      uint32_t ack;
      uint16_t data_offset:4;
      uint16_t pad:3;
      uint16_t ecn:3;
      uint16_t URG:1;
      uint16_t ACK:1;
      uint16_t PSH:1;
      uint16_t RST:1;
      uint16_t SYN:1;
      uint16_t FIN:1;
      uint16_t control:6;
      uint16_t window;
      uint16_t checksum;
      uint16_t urgent;
   } __attribute__((__packed__));
}

class TCP : public Protocol {
};

}

#endif
