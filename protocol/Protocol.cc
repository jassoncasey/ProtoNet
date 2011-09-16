// Written by Jasson Casey
// // Copyright (C) 2011. All rights reserved.

#include "Protocol.h"

namespace ProtoNet {

std::ostream& operator<<( std::ostream& out, const Protocol& p ) {
   p.Print( out );
   return out;
}

}
