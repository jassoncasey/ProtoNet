#ifndef ERROR_H
#define ERROR_H

#include "Time.h"

namespace ProtoNet {

class Error {

   public :
      Error() {}
      Error( const std::string& str ) : message(str) {}
      Error( const Error& e ) : message(e.message), time(e.time) {}
      Error& operator=( const Error& e ) {
         message = e.message ; 
         time = e.time ;
         return *this ;
      }  
      
      std::string Msg() const { return message ; }
      
      void Print( std::ostream& out ) const {
         out << message ;
      }  
      
   private:
      std::string message ;
      Time time;
} ;

std::ostream& operator<<( std::ostream& out, const Error& e ) ;

Error& operator<<( Error& e, const std::string& s ) ;

}

#endif
