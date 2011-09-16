// Written by Jasson Casey
// // Copyright (C) 2011. All rights reserved.

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "Packet.h"

namespace ProtoNet {

class Protocol {

   public:
      class Visitor;

   public:
      Protocol() : packet(0), offset(0), prev(0), next(0), bytes(0) {}

      virtual void Recieve( Packet& p ) = 0 ;
      virtual int GetMTU() const = 0 ;
      virtual Protocol* MakeCarriedType() const = 0 ; 
      virtual bool UnknownPayload()  const = 0 ;
      virtual bool FilteredPayload() const = 0 ;
      virtual void Print( std::ostream& out ) const = 0 ;

      virtual int GetBytes() const { return bytes ; }
      void SetPrev( const Protocol* p ) { prev = p ; }
      void SetNext( const Protocol* p ) { next = p ; }

   protected:

      const Packet* packet;
      int offset;

      const Protocol* prev;
      const Protocol* next;

      int bytes ;
};

class Protocol::Visitor {
   virtual void visit( Protocol& p ) {}
};

std::ostream& operator<<( std::ostream& out, const Protocol& p );

class ProtocolFilter {

};

}

#endif
