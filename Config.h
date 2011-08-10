#ifndef CONFIG_H
#define CONFIG_H

#include <vector>

namespace ProtocolMontior {


class ProtocolFilter {

   private:
      static std::vector<uint16_t> ethernetII_filter = { } ;

   public:

   bool Filter( const EthernetII& e ) {
   }
};

}

#endif
