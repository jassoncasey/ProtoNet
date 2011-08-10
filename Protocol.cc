#include "Protocol.h"

namespace ProtocolMonitor {

std::ostream& operator<<( std::ostream& out, const Protocol& p ) {
   p.Print( out );
   return out;
}

}
