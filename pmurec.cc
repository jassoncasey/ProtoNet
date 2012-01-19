#include "Sniffer.h"
#include "Phasor.h"

extern "C" {
   #include <signal.h>
   #include <string.h>
}

void terminate(int signum) {
   ProtoNet::Sniffer::StopAll();
}
const char* usage_error = "pmurec <interface>";

static uint32_t soc = 0, frac_sec = 0;
static struct timeval start_time, end_time;
static uint32_t state = 0;

void callback( ProtoNet::Sniffer *hdl, const ProtoNet::Packet& pkt ) {
   ProtoNet::PhasorHdr *hdr;
   struct timezone tz;

   if (*(uint16_t*)(pkt.GetBuffer() + 0x10) <= 0x28 || *(pkt.GetBuffer() + 0x36) != 0xAA)
   {
      return;
   }

   if ((*(uint16_t*)(pkt.GetBuffer() + 0x22) == 4712 && state != 0) || (*(uint16_t*)(pkt.GetBuffer() + 0x24) == 4712 && state != 1))
   {
      return;
   }

   hdr = (ProtoNet::PhasorHdr*)(pkt.GetBuffer() + 0x36);
   
   if (state == 0)
   {
      soc = hdr->soc;
      frac_sec = hdr->frac_sec;
      gettimeofday(&start_time, &tz);
      state = 1;
   }
   else
   {
      if (soc == hdr->soc && frac_sec == hdr->frac_sec)
      {
         gettimeofday(&end_time, &tz);
         std::cout << ((end_time.tv_sec - start_time.tv_sec) * 1000
               + end_time.tv_usec) - start_time.tv_usec << "\n" ;
         state = 0;
         return;
      }
      gettimeofday(&end_time, &tz);
      if ((end_time.tv_sec - start_time.tv_sec) * 1000 + end_time.tv_usec - start_time.tv_usec > 100)
      {
         state = 0;
      }
   }
}

void callback2( ProtoNet::Sniffer *hdl, const ProtoNet::Packet &pkt )
{
   ProtoNet::PhasorHdr *hdr;
   struct timezone tz;

   if (*(uint16_t*)(pkt.GetBuffer() + 0x10) <= 0x28 || *(pkt.GetBuffer() + 0x36) != 0xAA)
   {
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
   if ((end_time.tv_sec - start_time.tv_sec) * 1000 + end_time.tv_usec - start_time.tv_usec > 100)
   {
      hdl->Stop();
   }
}

int main( int argc, char** argv ) {
   pcap_if *pif;
   char err[255];

   if ( argc != 2 ) {
      std::cerr << usage_error << std::endl;
      exit(-1);
   }

   try {
      ProtoNet::Sniffer sniffer( argv[1], 0, 1500, callback );
//      ProtoNet::Sniffer sniffer2( argv[2], 0, 1500, callback2 ); 
      /* std::cout << "Listening for C37.118.2 on: " << argv[1] << std::endl; */
      signal(SIGINT, terminate);
      /* sniffer.Run("udp"); */
      
      while(1)
      {
         sniffer.Run("port 4712");
//         sniffer2.Run("dst port 4712");
      }  

   }
   catch ( ProtoNet::Error& e ) {
      std::cerr << "Error: " << e << std::endl;
   }
}
