#ifndef TIME_H
#define TIME_H

extern "C" {
   #include <string.h>
   #include <sys/time.h>
}

#include <string>

namespace ProtoNet {

   class Time {
      public:
         Time() {
            gettimeofday( &time, 0 ) ;
         }
         Time( const struct timeval& tm ) {
            memcpy( &time, &tm, sizeof( struct timeval ) );
         }
         Time( const Time& t ) {
            memcpy( &time, &t, sizeof( struct timeval ) );
         }
         Time& operator=( const Time& t ) {
            memcpy( &time, &t, sizeof( struct timeval ) );
            return *this ;
         }
         bool operator<( const Time& t ) const {
            if ( time.tv_sec < t.time.tv_sec )
               return true ;
            else if ( time.tv_sec == t.time.tv_sec ) {
               return time.tv_usec < t.time.tv_usec ;
            }  
            else
               return false;
         }
         
         void Print( std::ostream& out ) const {
         }
         
      private:
         struct timeval time;
   };
   
   std::ostream& operator<<( std::ostream& out, const Time& t ) ;
}

#endif
