#ifndef TIME_H
#define TIME_H

#include <string>
#include <algorithm>

#include <sys/time.h>

namespace ProtoNet {

   class Time {

      public:
         static const int size = sizeof( struct timeval );

      public:
         Time() {
            gettimeofday( &time, 0 ) ;
         }
         Time( const struct timeval& tm ) {
            time = tm;
//            std::copy( &tm, &tm+size, &time);
         } 
         Time( const Time& t ) {
 //           std::copy( &t, &t+size, &time );
         }
         Time& operator=( const Time& t ) {
  //          std::copy( &t, &t+size, &t.time );
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
