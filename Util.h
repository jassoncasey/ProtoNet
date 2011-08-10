// Written by Jasson Casey
// Copyright (C) 2011. All rights reserved.

#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <limits>

extern "C" {
   #include <string.h>
   #include <stdint.h>
}

namespace ProtoNet {

class UInt8 {
   private:
      uint8_t value;
   public:
      UInt8( uint8_t v ) : value(v) {}
      UInt8( const UInt8& u ) : value(u.value) {}
      UInt8& operator=( const UInt8& u ) {
         value = u.value ;
         return *this ;
      }
};

template <typename PrecisionType>
class Hex {
   private:   
      PrecisionType value;
   public:
      Hex( PrecisionType c ) : value(c) {}
      void Print( std::ostream& out ) const {
         out << std::hex << (((int)value) & std::numeric_limits<PrecisionType>::max()) << std::dec ;
      }
};

typedef Hex<uint8_t>    HexU8 ;
typedef Hex<uint16_t>   HexU16 ;
typedef Hex<uint32_t>   HexU32 ;

template <typename T>
std::ostream& operator<<( std::ostream& out, const Hex<T>& h ) ;

class EthernetAddr {

   private:
      uint8_t addr[6] ;

   public:
      EthernetAddr( const uint8_t a[6] ) { memcpy( addr, a, 6 ) ; }

      void Print( std::ostream& out ) const {
         out << HexU8( addr[0] ) << "." << HexU8( addr[1] ) << "." ;
         out << HexU8( addr[2] ) << "." << HexU8( addr[3] ) << "." ;
         out << HexU8( addr[4] ) << "." << HexU8( addr[5] ) ;
      }
};

class IPv4Addr {
   private:
      uint32_t addr;
   public:
      IPv4Addr( uint32_t a ) : addr(a) {}
      void Print( std::ostream& out ) const { 
         out << ( ( addr & 0xff000000 ) >> 24 ) << "." ;
         out << ( ( addr & 0x00ff0000 ) >> 16 ) << "." ;
         out << ( ( addr & 0x0000ff00 ) >> 8 ) << "." ;
         out <<   ( addr & 0x000000ff ) ;
      }
};

std::ostream& operator<<( std::ostream& out, const EthernetAddr& e ) ;
std::ostream& operator<<( std::ostream& out, const IPv4Addr& a ) ;

}

#endif
