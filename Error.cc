#include "Error.h"

#include <sstream>

namespace ProtoNet {

std::ostream& operator<<( std::ostream& out, const Error& e ) {
   e.Print( out ) ;
   return out ;
}

Error& operator<<( Error& error, const std::string& s ) {
   std::stringstream ss;
   ss << error << s ;
   error = ss.str() ;
   return error ;
}

}
