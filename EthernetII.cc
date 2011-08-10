// Written by Jasson Casey
// Copyright (C) 2011. All rights reserved.

#include "EthernetII.h"
#include "Util.h"

namespace ProtoNet {
 
void EthernetII::Recieve( Packet<MTU>& p ) {

   // Establish header and payload
   hdr = ( EthernetIIHdr* ) p.GetPosition();
   hdr->typelen = ntohs( hdr->typelen );
   bytes = sizeof(struct EthernetIIHdr)
   payload = (char*)hdr + bytes;

   // Advance the Packet offset
   p.IncrementOffset( bytes );
}

Protocol* EthernetII::MakeCarriedType() const {
}

bool EthernetII::UnknownPayload() const {
}

bool EthernetII::FilteredPayload() const {
}

void EthernetII::Print( std::iostream& out ) const {
   out << "---------Ethernet II Header---------" << std::endl;
   out << "Dst Addr: "     << EthernetAddr(dst) << std::endl;
   out << "Src Addr: "     << EthernetAddr(src) << std::endl;
   out << "Type/Length: "  << HexU16( ether_hdr->typelen ) << std::endl;
}

}
