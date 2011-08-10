// Written by Jasson Casey
// Copyright (C) 2011. All rights reserved.

#include "Util.h"

namespace ProtoNet {

   template <typename T> 
   std::ostream& operator<<( std::ostream& out, const Hex<T>& h ) { 
      h.Print( out ) ; 
      return out ; 
   }

   std::ostream& operator<<( std::ostream& out, const EthernetAddr& e ) {
      e.Print( out ) ;
      return out ;
   }

   std::ostream& operator<<( std::ostream& out, const IPv4Addr& a ) {
      a.Print( out ) ;
      return out ;
   }

}
