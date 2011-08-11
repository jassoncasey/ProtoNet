// Written by Jasson Casey
// Copyright (C) 2011. All rights reserved.

#include "Packet.h"

namespace ProtoNet {

int Packet::CurrentID = 1;

void Packet::Recieve( uint8_t* ptr, int len, struct timeval* t ) {
   // Set the length
   if ( len > bsize ) {
      truncated = true ;
      plength = bsize ;
   }
   else
      plength = len;

   // Copy the recieve time and update ID
   memcpy( &tm, t, sizeof(struct timeval) );
   id = CurrentID++;

   // Copy the recieved data
   memcpy( buffer.get(), ptr, plength );
}

   /*

   // Update the pointer
   current_ptr += protocol.GetBytes() ;
   len = GetRemainingBytes() ;

   Protocol* proto = &protocol;
   while ( len > 0 && ! proto->UnknownPayload() ) {
      proto = proto->MakeCarriedType() ;

      proto->Capture( *this );
      protocols.push_back( *proto );

      // Update the pointer
      current_ptr += proto->GetBytes() ;
      len = GetRemainingBytes() ;
   }

   */

}

