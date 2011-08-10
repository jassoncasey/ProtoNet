#ifndef DEVICE_H
#define DEVICE_H

#include <vector>
#include "Protocol.h"

namespace ProtocolMonitor {

template <typename ProtoType>
class Device {

   public:
      typedef ProtoType proto_type ;

   public:
      void Recieve( char* ptr, int len, struct timeval* t ) ;

   private:

      std::vector<Packet> queue ;
};

}

#endif
