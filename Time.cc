#include "Time.h"

namespace ProtoNet {

std::ostream& operator<<( std::ostream& out, const Time& t ) {
   t.Print( out ) ;
   return out ;
}

}
