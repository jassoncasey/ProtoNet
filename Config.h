// Written by Jasson Casey
// Copyright (C) 2011. All rights reserved.

#ifndef CONFIG_H
#define CONFIG_H

#include <vector>

namespace ProtoNet {

class ProtocolFilter {

   private:
      static std::vector<uint16_t> ethernetII_filter = { } ;

   public:

   bool Filter( const EthernetII& e ) {
   }
};

}

#endif
