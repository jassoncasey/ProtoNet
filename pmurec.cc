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

void callback( ProtoNet::Sniffer *hdl, const ProtoNet::Packet& pkt ) {
   ProtoNet::PhasorHdr *hdr;
   struct timezone tz;

   hdr = (ProtoNet::PhasorHdr*)(pkt.GetBuffer() + 0x2A);
   
   soc = hdr->soc;
   frac_sec = hdr->frac_sec;
   gettimeofday(&start_time, &tz);
   hdl->Stop();
}

void callback2( ProtoNet::Sniffer *hdl, const ProtoNet::Packet &pkt )
{
   ProtoNet::PhasorHdr *hdr;
   struct timezone tz;

   
   hdr = (ProtoNet::PhasorHdr*)(pkt.GetBuffer() + 0x2A);
   
   if (soc == hdr->soc && frac_sec == hdr->frac_sec)
   {
      gettimeofday(&start_time, &tz);
      std::cout << ((end_time.tv_sec - start_time.tv_sec) * 1000
               + end_time.tv_usec) - start_time.tv_usec << "\n" ;
      hdl->Stop();
   }
}

int main( int argc, char** argv ) {
   pcap_if *pif;
   char err[255];

   if ( argc != 3 ) {
      std::cerr << usage_error << std::endl;
      exit(-1);
   }

   try {
      ProtoNet::Sniffer sniffer( argv[1], 0, 1500, callback );
      ProtoNet::Sniffer sniffer2( argv[2], 0, 1500, callback ); 
      /* std::cout << "Listening for C37.118.2 on: " << argv[1] << std::endl; */
      signal(SIGINT, terminate);
      /* sniffer.Run("udp"); */
      
      while(1)
      {
         sniffer.Run("port XXX");
         sniffer2.Run("port XXX");
      }  

/*      if (pcap_findalldevs(&pif, err) == 0)
      {
         std::cout << "succ" << std::endl;
      }
      else
      {
         std::cout << "fail" << std::endl;
      }
      while (pif != NULL)
      {
         std::cout << pif->name << std::endl;
         pif = pif->next;
      } 
      std::cout << "end" << std::endl; */
   }
   catch ( ProtoNet::Error& e ) {
      std::cerr << "Error: " << e << std::endl;
   }
}
