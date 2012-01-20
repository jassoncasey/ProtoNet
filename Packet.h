#ifndef PACKET_H
#define PACKET_H

#include <memory>
#include <cstdint>
#include "Time.h"

namespace ProtoNet {
   
class Packet {
  
   public:
      Packet( uint8_t* ptr, int size, const Time& tm, bool trunc = false ) : 
               buffsize(size), time(tm), truncated(trunc) {
         buffer.reset( new uint8_t[ buffsize ] ) ;
         std::copy( ptr, ptr + buffsize, buffer.get() ) ;
      }
      Packet( const Packet& p ) : buffsize( p.buffsize ), time(p.time), 
               truncated( p.truncated ) {
         buffer.reset( new uint8_t[ buffsize ] ) ;
         uint8_t* ptr = p.buffer.get();
         std::copy( ptr, ptr + buffsize, buffer.get() ) ;
      }
      Packet& operator=( const Packet& p ) {
         buffsize = p.buffsize ;
         truncated = p.truncated ;
         time = p.time;
         buffer.reset( new uint8_t[ buffsize ] ) ;
         uint8_t* ptr = p.buffer.get();
         std::copy( ptr, ptr + buffsize, buffer.get() ) ;
         return *this ;
      }
      
      bool operator<( const Packet& p ) const {
         return time < p.time ;
      }
      
      void Print( std::ostream& out ) const {
      }

      uint8_t* GetBuffer() const { return buffer.get() ; }
      int GetSize() const { return buffsize; }
      
   private:
      std::auto_ptr<uint8_t> buffer ;
      int buffsize ;
      Time time ;
      bool truncated ;
   };

std::ostream& operator<<( std::ostream& out, const Packet& p ) ;

}

#endif
