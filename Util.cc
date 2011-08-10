#include "Util.h"

namespace ProtocolMonitor {

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
