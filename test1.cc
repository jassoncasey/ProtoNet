#include "Sniffer.h"

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
      sniffer.Run(argv[2]);
   }
   catch ( ProtoNet::Error& e ) {
      std::cout << e << std::endl;
   }
}
