#include "Time.h"

std::ostream& ProtoNet::operator<<( std::ostream& out, const Time& t ) {
   t.Print( out ) ;
   return out ;
}
