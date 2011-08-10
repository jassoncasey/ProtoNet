#ifndef PACKET_H
#define PACKET_H

#include <vector>
#include "Util.h"

namespace ProtocolMonitor {

class Protocol;

class Packet {
   public:
      static int CurrentID;

   public:
      Packet() : length(0), offset(0), id(0), truncated(false) {
         bzero( &tm, sizeof( struct timeval ) ) ;
      }
      Packet( const Packet& p ) : length(p.length), offset(p.offset),
                                    id(p.id), truncated(p.trunated) {
         memcpy( &tm, &p.tm, sizeof( struct timeval ) ) ;
      }
      Packet& operator=( const Packet& p ) {
         length = p.length ;
         offset = p.offset ;
         id = p.id ;
         truncated = p.truncated ;

         memcpy( &tm, &p.tm, sizeof( struct timeval ) ) ;
      }

      virtual void Recieve( char* ptr, int len, struct timeval* t ) = 0 ;
      virtual int GetOffset() const = 0 ;
      virtual char* GetPtr() const = 0 ;

      virtual int GetRemainingBytes() const {
         return length - offset ;
      }
      virtual void IncrementOffset(int) {
         if ( offset + o > length )
            throw 1; 
         offset += o ;
      }

   protected:
      int length ;
      int offset ;
      int id ;
      bool truncated ;

      struct timeval tm ;
} ;

template <int MAXBUFSIZE>
class packet_impl : public Packet {

   public:
      static const int MaxBufferSize = MAXBUFSIZE;

   public:
      explicit packet_impl() : Packet() {
         bzero( buffer, MaxBufferSize );
      }
      packet_impl( const Packet& b ) : Packet(*this) {
         memcpy( buffer, b.buffer, length );
      }
      packet_impl& operator=( const packet_impl& b ) {
         Packet::operator=( *this ) ;
         memcpy( buffer, b.buffer, length );
      }

      void Recieve( char* ptr, int len, struct timeval* t );
      char* GetPosition() const { return buffer + (char*)offset ; }
      char* GetPtr( int o ) const { return buffer + (char*)o ; }

   private:
      char buffer[MaxBufferSize];

      std::vector<Protocol> protocols;
};

}

#endif
