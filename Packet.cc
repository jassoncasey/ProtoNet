#include "Packet.h"

namespace ProtocolMonitor {

int Packet::CurrentID = 1;

void packet_impl::Recieve( char* ptr, int len, struct timeval* t ) {

   // Set the length
   if ( len > MaxBufferSize ) {
      truncated = true ;
      length = MaxBufferSize ;
   }
   else
      length = len;

   // Copy the recieve time and update ID
   memcpy( &tm, obstm, sizeof(struct timeval) );
   id = CurrentID++;

   // Copy the recieved data
   memcpy( buffer, ptr, length );

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

}

