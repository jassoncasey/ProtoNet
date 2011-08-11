// Written by Jasson Casey
// Copyright (C) 2011. All rights reserved.

#include "EthernetII.h"
#include "Util.h"

namespace ProtoNet {
 
void EthernetII::Recieve( Packet& p ) {

   // Establish header and payload
   hdr = ( EthernetIIHdr* ) p.GetPtr( p.GetOffset() ) ; 
   hdr->typelen = ntohs( hdr->typelen ) ;
   bytes = sizeof(struct EthernetIIHdr) ;
   payload = (uint8_t*)hdr + bytes;

   // Advance the Packet offset
   p.IncrementOffset( bytes );
}

Protocol* EthernetII::MakeCarriedType() const {
}

bool EthernetII::UnknownPayload() const {
}

bool EthernetII::FilteredPayload() const {
}

void EthernetII::Print( std::ostream& out ) const {
   out << "---------Ethernet II Header---------" << std::endl;
   out << "Dst Addr: "     << EthernetAddr( hdr->dst ) << std::endl;
   out << "Src Addr: "     << EthernetAddr( hdr->src ) << std::endl;
   out << "Type/Length: "  << HexU16( hdr->typelen )   << std::endl;
}

}
