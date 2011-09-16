#include "Sniffer.h"

extern "C" {
   #include <signal.h>
}

void terminate(int signum) {
   ProtoNet::Sniffer::StopAll();
}
const char* usage_error = "pmurec <interface>";

void callback( const ProtoNet::Packet& pkt ) {
}

int main( int argc, char** argv ) {

   if ( argc != 2 ) {
      std::cerr << usage_error << std::endl;
      exit(-1);
   }

   try {
      ProtoNet::Sniffer sniffer( argv[1], 0, 1500, callback );
      std::cout << "Listening for C37.118.2 on: " << argv[1] << std::endl;
      signal(SIGINT, terminate);
      sniffer.Run("udp");
   }
   catch ( ProtoNet::Error& e ) {
      std::cerr << "Error: " << e << std::endl;
   }
}
