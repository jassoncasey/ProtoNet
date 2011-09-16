#ifndef PACKET_H
#define PACKET_H

#include <memory>
#include "Time.h"

extern "C" {
   #include <stdint.h>
   #include <stdlib.h>
}

namespace ProtoNet {
   
class Packet {
  
   public:
      Packet( uint8_t* ptr, int size, const Time& tm, bool trunc = false ) :
                  buffsize(size), time(tm), truncated(trunc) {
         buffer.reset( new uint8_t[ buffsize ] ) ;
         memcpy( buffer.get(), ptr, buffsize ) ;
         
      }
      Packet( const Packet& p ) : buffsize( p.buffsize ), time(p.time), truncated( p.truncated ) {
         buffer.reset( new uint8_t[ buffsize ] ) ;
         memcpy( buffer.get(), p.buffer.get(), buffsize ) ;
      }
      Packet& operator=( const Packet& p ) {
         buffsize = p.buffsize ;
         truncated = p.truncated ;
         memcpy( &time, &p.time, sizeof(struct timeval) ) ;
         buffer.reset( new uint8_t[ buffsize ] ) ;
         memcpy( buffer.get(), p.buffer.get(), buffsize ) ;
         return *this ;
      }
      
      bool operator<( const Packet& p ) const {
         return time < p.time ;
      }
      
      void Print( std::ostream& out ) const {
      }
      
   private:
      std::auto_ptr<uint8_t> buffer ;
      int buffsize ;
      Time time ;
      bool truncated ;
   };

std::ostream& operator<<( std::ostream& out, const Packet& p ) ;

}

#endif
