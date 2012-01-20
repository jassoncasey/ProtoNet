/**
 * Copyright (c) 2012 Texas A&M University
 *
 * @file	Monitor.h
 * @author	Jasson Casey, Muxi Yan
 * @version	0.1
 *
 * @section LICENSE
 *
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission
 * notice shall be included in all copies or substantial portions of
 * the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT
 * WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef MONITOR_H
#define MONITOR_H

/*
 * 1. pcap_openlive        
 * 2. pcap_findalldevs
 * 3. pcap_freealldevs
 * 4. pcap_lookupnet
 * 5. pcap_compile
 * 6. pcap_setfiler
 * 7. pcap_freecode
 * 8. pcap_list_datalinks
 * 9. pcap_loop
 * 10. pcap_next
 * 11. pcap_next_ex
 * 12. pcap_close
 */

#include <string>
#include <vector>
#include <cstring>
#include <iostream>

extern "C" {
   #include <pcap.h>
}

#include "Error.h"

namespace ProtoNet {

class Monitor {

   public:
      typedef std::vector<std::string> result_type;
      typedef std::vector<std::string>::iterator iterator;

   private:

   public:

      static result_type ListDevices() {
         char errbuf[PCAP_ERRBUF_SIZE];
         strcpy( errbuf, "" );

         // Grab the device list or fail
         pcap_if_t* devices = 0;
         if ( pcap_findalldevs( &devices, errbuf ) == -1 ) {
            Error e( errbuf );
            throw e;
         }

         // Grab all the device names
         result_type result;
         pcap_if_t* ptr = devices;
         while( ptr != 0 ) {
            if ( ptr->name != 0 )
               result.push_back( ptr->name );
            ptr = ptr->next;
         }

         // Free memory and return
         pcap_freealldevs( devices );
         return result;
      }

      static uint32_t Address( const std::string& i ) {
         char errbuf[PCAP_ERRBUF_SIZE];
         strcpy( errbuf, "" );
         bpf_u_int32 net, mask;
         if ( pcap_lookupnet( i.c_str(), &net, &mask, errbuf ) == -1 ) {
            Error e( errbuf );
            throw e;
         }
         uint32_t address = net;
         return net;
      }
      static uint32_t Netmask( const std::string& i ) {
         char errbuf[PCAP_ERRBUF_SIZE];
         strcpy( errbuf, "" );
         bpf_u_int32 net, mask;
         if ( pcap_lookupnet( i.c_str(), &net, &mask, errbuf ) == -1 ) {
            Error e( errbuf );
            throw e;
         }
         return mask;
      }
};

}

#endif
