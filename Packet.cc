#include "Packet.h"

namespace ProtoNet {

std::ostream& operator<<( std::ostream& out, const Packet& p ) {
   p.Print( out ) ;
   return out ;
}

}
