#include "Sniffer.h"

extern "C" {
   #include <signal.h>
}

ProtoNet::Sniffer* ptr = 0;

void handle_signal(int signum ) {
   ptr->Stop();
}

void process( const ProtoNet::Packet& packet ) {
   std::cout << "I just recieved a packet packet" << std::endl;
}

int main( int argc, char** argv ) {
   if (argc != 3) {
      std::cout<<"usage error: " << argv[0] << " <interface name> <filter rule>" << std::endl ; 
      exit(-1);
   }

   std::cout << "listening on interface: " << argv[1] << std::endl;
   std::cout << "using filter: " << argv[2] << std::endl;

   try {
      ProtoNet::Sniffer sniffer(argv[1], 0, 1500, process );

      signal(SIGINT, handle_signal);

      ptr = & sniffer ;
      sniffer.Run(argv[2]);
   }
   catch ( ProtoNet::Error& e ) {
      std::cout << e << std::endl;
   }
   std::cout << "Done" << std::endl;
}
