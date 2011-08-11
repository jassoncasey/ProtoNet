// Written by Jasson Casey
// Copyright (C) 2011. All rights reserved.

#ifndef DEVICE_H
#define DEVICE_H

#include <vector>
#include "Protocol.h"

namespace ProtoNet {

class Device {

   public:
      Device( Protocol* p ) : protocol(p) {}
      Device( const Device& d ) : protocol( d.protocol.get() ) {}
      Device& operator=( const Device& d ) {
         protocol.reset( d.protocol.get() ) ;
      }

      void Recieve( uint8_t* ptr, int len, struct timeval* t ) ;

   private:
      std::auto_ptr<Protocol> protocol ;
      std::vector<Packet> queue ;
};

}

#endif
