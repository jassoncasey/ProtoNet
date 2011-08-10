// Written by Jasson Casey
// Copyright (C) 2011. All rights reserved.

#include "Device.h"

namespace ProtoNet {

void Device::Recieve( char* ptr, int len, struct timeval* t ) {

   // Build a packet and copy its contents
   packet_impl<proto_type::MTU> packet;
   packet.Recieve( ptr, len, timeval );
   queue.push_back( packet ) ;

   // Build the instantiating protocol and
   // intialize it with the packet contents
   proto_type protocol() ;
   protocol.Recieve( packet ) ;
}

}
