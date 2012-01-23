#include "Sniffer.h"

extern "C" {
   #include <signal.h>
}

void handle_signal(int signum ) {
   ProtoNet::Sniffer::StopAll();
}

void process( ProtoNet::Sniffer* snif, const ProtoNet::Packet& packet ) {
   
   std::cout << "I just recieved a packet packet" << std::endl;
}

int main( int argc, char** argv ) {
   if (argc != 3) {
      std::cout <<"usage error: " << argv[0] ;
      std::cout << " <interface name> <filter rule>" << std::endl ; 
      exit(-1);
   }

   std::cout << "listening on interface: " << argv[1] << std::endl;
   std::cout << "using filter: " << argv[2] << std::endl;

   try {
      ProtoNet::Sniffer sniffer(argv[1], 0, 1500, process );
      ProtoNet::Sniffer snif2("eth4", 0, 1500, process ) ;

      signal(SIGINT, handle_signal);

      // Run a second sniffer
      sniffer.Run(argv[2]);

      // This isn't a great idea ... to run more than one interface will
      // require the pcap_next method or threads ... this just creates 
      // two serial sniffers
      snif2.Run("tcp");
   }
   catch ( ProtoNet::Error& e ) {
      std::cout << e << std::endl;
   }
   std::cout << "Done" << std::endl;
}
