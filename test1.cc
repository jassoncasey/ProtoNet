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

   ProtoNet::Sniffer sniffer("en0", 0, 1500, process );
   sniffer.Run("udp");
}
