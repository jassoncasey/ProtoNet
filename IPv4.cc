#include "IPv4.h"

namespace ProtocolMonitor {

void IPv4::Print( std::ostream& out ) {
   out << "-----------IPv4 Header---------" << std::endl;
   out << "IP Version : " << hdr->version << " ";

   out << "IHL : " << hdr->ihl << std::endl;
   out << "TosP: " << hdr->tos_pres << " ";
   out << "TosD: " << hdr->tos_delay << " ";
   out << "TosT: " << hdr->tos_throughput << " ";
   out << "TosR: " << hdr->tos_reliability << std::endl;

   out << "Length : " << hdr->length << std::endl;

   out << "Identification : " << HexU16( hdr->identification ) << std::endl ;
   out << "DontFrag: "        << hdr->dontfrag << " ";
   out << "MoreFrag: "        << hdr->morefrag << " ";
   out << "Frag Offset : "    << hdr->frag_offset << std::endl;

   out << "TTL : "      << ipv4_hdr->ttl << " ";
   out << "Protocol : " << hdr->protocol << std::endl;
   out << "Checksum : " << HexU16( hdr->checksum ) << std::endl;

   out << "Src Addr: " << IPv4Addr( hdr->src ) << std::endl ;
   out << "Dst Addr: " << IPv4Addr( hdr->dst ) << std::endl ;
}

}
