#include "Sniffer.h"
#include "Phasor.h"

extern "C" {
   #include <signal.h>
   #include <string.h>
   #include <stdio.h>
}

#define data_8(x) (*(uint8_t*)(x))
#define data_16(x) (((uint16_t)data_8(x) << 8) + data_8((uint8_t*)(x) + 1))
#define data_32(x) (((uint32_t)data_16(x) << 16) + data_16((uint8_t*)(x) + 2))

const uint32_t max_count = 10000;
const uint32_t bin_num = 60;
uint32_t bin_count[bin_num] = {0};
FILE *fo;

void terminate(int signum) {
   ProtoNet::Sniffer::StopAll();
}
const char* usage_error = "pmurec <interface>";

void callback( ProtoNet::Sniffer *hdl, const ProtoNet::Packet& pkt ) {
   ProtoNet::PhasorHdr *hdr;
   static ProtoNet::Time time;
   static uint32_t state = 0;
   static uint32_t count = 0;
   static uint32_t tot = 0;
   static uint32_t max = 0;

/*   // tcp packet has payload (not pure tcp ack packet)
   if ( data_16(pkt.GetBuffer() + 0x10) <= 0x0028 ) {
      std::cout << "return 1\n";
      return;
   }
 
   // is C37.118 packet
   if ( data_8(pkt.GetBuffer() + 0x36) != 0xAA) {
      std::cout << "return 2\n";
      return;
   }*/

   // at state 0: interested in packet from 192.168.0.30:4712 -> 192.168.0.200:1082
   // at state 1: interested in packet from 192.168.0.200:1082 -> 192.168.0.10:4712
   // filter already helped with 'port 1082'
   if (!(( data_32(pkt.GetBuffer() + 0x1a) == 0xc0a8001e && data_32(pkt.GetBuffer() + 0x1e) == 0xc0a800c8 && state == 0) 
         || (data_32(pkt.GetBuffer() + 0x1a) == 0xc0a800c8 && data_32(pkt.GetBuffer() + 0x1e) == 0xc0a8000a && state == 1))) {
//      uint32_t a = data_32(pkt.GetBuffer() + 0x1a), b = data_32(pkt.GetBuffer() + 0x1e);
//      std::cout << "return 3  " << std::hex << a << "->" << b << "  " << state << "\n" << std::dec;
      state = 0;
      return;
   }

   hdr = (ProtoNet::PhasorHdr*)(pkt.GetBuffer() + 0x36);
   
   if (state == 0) {
      time = pkt.GetTimeStamp();

      state = 1;
   }
   else {
      uint32_t diff = (pkt.GetTimeStamp() - time);

      fprintf(fo, "%ld\n", diff);

      count++;
      if (count % 100 == 0)
         std::cout << count / 100 << "\n";
      tot += diff;
      if (diff > max) 
         max = diff;
      if (diff / 1000 < 50)
         bin_count[diff / 1000]++;

      if (count >= max_count){
         std::cout << tot / count << "\n";
         std::cout << max << "\n";
         for (int i = 0; i < bin_num; i++) {
            if (i % 10 == 0)
               std::cout << "\n";
            std::cout << (double)bin_count[i] / count << ' ';
         }

         hdl->Stop();
      }
      state = 0;
      return;
   }
}

/* not in use */
/* void callback2( ProtoNet::Sniffer *hdl, const ProtoNet::Packet &pkt )
{
   ProtoNet::PhasorHdr *hdr;
   struct timezone tz;

   if ( *(uint16_t*)(pkt.GetBuffer() + 0x10) <= 0x28 
         || *(pkt.GetBuffer() + 0x36) != 0xAA ) {
      return;
   }
   
   hdr = (ProtoNet::PhasorHdr*)(pkt.GetBuffer() + 0x36);
   
   if (soc == hdr->soc && frac_sec == hdr->frac_sec)
   {
      gettimeofday(&end_time, &tz);
      std::cout << ((end_time.tv_sec - start_time.tv_sec) * 1000
               + end_time.tv_usec) - start_time.tv_usec << "\n" ;
      hdl->Stop();
   }
   gettimeofday(&end_time, &tz);
   if ( (end_time.tv_sec - start_time.tv_sec) * 1000 
         + end_time.tv_usec - start_time.tv_usec > 100 ) {
      hdl->Stop();
   }
} */

int main( int argc, char** argv ) {
   pcap_if *pif;
   char err[255];

   if ( argc != 2 ) {
      std::cerr << usage_error << std::endl;
      exit(-1);
   }

   try {
      fo = fopen("data.txt", "w");
      ProtoNet::Sniffer sniffer( argv[1], 0, 1500, callback );
      /* std::cout << "Listening for C37.118.2 on: " << argv[1] << std::endl; */
      signal(SIGINT, terminate);
      /* sniffer.Run("udp"); */
      
      sniffer.Run("port 4712");

      fclose(fo);
   }
   catch ( ProtoNet::Error& e ) {
      std::cerr << "Error: " << e << std::endl;
   }
}
