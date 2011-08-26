#ifndef SNIFFER_H
#define SNIFFER_H

extern "C" {
   #include <pcap.h>
   #include <signal.h>
}
#include <string>
#include <iostream>

class Time {

   public:

      Time( struct timeval* tv ) {
         memcpy( &time, tv, sizeof(struct timeval) ) ;
      }
      Time( const Time& t) {
         memcpy( &time, &t.time, sizeof(struct timeval) ) ;
      }
      Time& operator=( const Time& t ) {
         memcpy( &time, &t.time, sizeof(struct timeval) ) ;
         return *this ;
      }

      bool operator<( const Time& t ) {
         if ( time.tv_sec < t.tv_sec )
            return true ;
         else if ( time.tv_usec < t.tv_usec )
            return true ;
         else
            return false ;
      }

      void Print( std::ostream& out ) const {
         out << time.tv_sec << "s : " << time.tv_usec << "us " ;
      }

   private:
      struct timeval time;
};

class Packet {

   public:

      Packet( uint8_t* b, int l, const Time& t ) : buffer(b), length(l), time(t) {} ;
      Packet( const Packet& p ) : buffer(b.buffer), length(b.length), time(b.time) {} ;
      Packet& operator=( const Packet& p ) {
         buffer = p.buffer ;
         legnth = p.length ;
         time = p.time ;
         return *this ;
      }

   void Print( std::ostream& out ) {
      out << "Packet - " << length << " bytes - " << time << " timestamp " ;
   }

   private:
      uint8_t* buffer;
      int length;
      Time time;

};

template <typename T>
std::ostream& operator<<( std::ostream& out, const T& t ) {
   t.Print( out ) ;
   return out;
}

class Sniffer {
   public:
      Sniffer( const std::string& d, int to, int ms,
               void (*)() r, void (*)() f = 0 ) ; 
      ~Sniffer();

      void UpdateFilter( const std::string& f );

   private:
      std::string device;
      int timeout;
      int maxpacketsize;

      void (*process)( const Packet& p );
      void (*finish)();
      
      std::string filter;

      bpf_u_int32 net, mask;
      pcap_t* handle;
};

#endif
