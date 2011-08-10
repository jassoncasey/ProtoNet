#include "Device.h"

namespace ProtoNet {

void Device::Recieve( uint8_t* ptr, int len, struct timeval* t ) {
   // Build a packet and copy its contents
   Packet packet( protocol->GetMTU() ) ;
   packet.Recieve( ptr, len, t );
   queue.push_back( packet ) ;

   // Build the instantiating protocol and
   // intialize it with the packet contents
   protocol->Recieve( packet ) ;
   packet.AddProtocol( protocol.get() ) ;
}

}
