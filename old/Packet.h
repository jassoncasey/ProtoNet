// Written by Jasson Casey
// Copyright (C) 2011. All rights reserved.

#ifndef PACKET_H
#define PACKET_H

#include <vector>
#include <memory>
#include "Util.h"

namespace ProtoNet {

class Protocol; 
class Packet {

   public:
      static int CurrentID;

   public:
      Packet( int len ) : plength(0), bsize(len), offset(0), id(0), truncated(false) {
         bzero( &tm, sizeof( struct timeval ) ) ;
         buffer.reset( new uint8_t[ bsize ] ) ;
         bzero( buffer.get(), bsize ) ;
      }
      Packet( const Packet& p ) : plength(p.plength), bsize(p.bsize), offset(p.offset),
                                    id(p.id), truncated(p.truncated) {
         memcpy( &tm, &p.tm, sizeof( struct timeval ) ) ;
         buffer.reset( new uint8_t[ bsize ] ) ;
         memcpy( buffer.get(), p.buffer.get(), bsize ) ;
      }
      Packet& operator=( const Packet& p ) {
         plength = p.plength ;
         bsize = p.bsize ;
         offset = p.offset ;
         id = p.id ;
         truncated = p.truncated ;

         memcpy( &tm, &p.tm, sizeof( struct timeval ) ) ;
         buffer.reset( new uint8_t[ bsize ] ) ;
         memcpy( buffer.get(), p.buffer.get(), bsize ) ;

         return *this ;
      }

      void Recieve( uint8_t* ptr, int len, struct timeval* t ) ;

      int GetOffset() const { return offset ; } 
      uint8_t* GetPtr( int os ) const { return buffer.get() + os ; }
      uint8_t* GetPosition() const { return buffer.get() + offset ; }
      int GetRemainingBytes() const {
         return plength - offset ;
      }
      void IncrementOffset( int o ) {
         if ( offset + o > plength )
            throw 1; 
         offset += o ;
      }

      void AddProtocol( Protocol* p ) { 
         protocols.push_back( p ) ; 
      }

   protected:
      int plength ;
      int bsize ;
      int offset ;
      int id ;
      bool truncated ;

      struct timeval tm ;
      std::auto_ptr<uint8_t> buffer ;
      std::vector<Protocol*> protocols;
} ;

}

#endif
