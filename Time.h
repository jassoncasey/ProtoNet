#ifndef TIME_H
#define TIME_H

#include <string>
#include <algorithm>

#include <sys/time.h>

namespace ProtoNet {

   /** Time - simple wrapper for the system supplied timeval structure
    */
   class Time {

      public:
         static const int size = sizeof( struct timeval );

      public:
         Time() {
            gettimeofday( &time, 0 ) ;
         }
         Time( const struct timeval& tm ) : time(tm) {}
         Time( const Time& t ) : time(t.time) {}
         Time& operator=( const Time& t ) {
            time = t.time;
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
         bool operator==( const Time& t ) const {
            if ( time.tv_sec != t.time.tv_sec )
               return false;
            if ( time.tv_usec != t.time.tv_usec )
               return false;
            return true;
         }
         bool operator!=( const Time& t ) const {
            return !(*this == t);
         }
         
         void Print( std::ostream& out ) const {
            //out << time.tv_sec << ":" << time.tv_usec ;
         }
         
      private:
         struct timeval time;
   };
   
   std::ostream& operator<<( std::ostream& out, const Time& t ) ;
}

#endif
