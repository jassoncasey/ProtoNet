// Written by Jasson Casey
// Copyright (C) 2011. All rights reserved.

#include <iostream>
extern "C" {
   #include <pcap.h>
   #include <signal.h>
}

#include "Packet.h"
#include "Protocols.h"

const char* usage_error = "usage error: ./pmurec <interface>";

static const int MaxPacketSize = 1500 ;

void pcap_callback( u_char *args, const struct pcap_pkthdr *hdr, const u_char *pkt ) {
   ProtoNet::Device dev( new ProtoNet::EthernetII() ) ;
   dev.Recieve( (uint8_t*)pkt, (int)hdr->caplen, (struct timeval*)&hdr->ts );
}

void err_close( pcap_t* handle ) {
   pcap_close( handle );
   exit(-1);
}

static pcap_t* signal_handle = 0;
void end( int sig ) {
   std::cout << "Finished recording" << std::endl;
   if ( signal_handle != 0 )
      pcap_close( signal_handle );
   exit(0);
}

void setup_sigs( pcap_t* ptr ) {
   signal_handle = ptr;
   
   signal(SIGINT, end);
   signal(SIGTERM, end);
   signal(SIGHUP, end);
   signal(SIGKILL, end);
   signal(SIGTSTP, end);
}

int main(int argc, char** argv) {

   // Check input arguments
   if ( argc != 2 ) {
      std::cerr << usage_error << std::endl;
      exit(-1);
   }

   char *dev = argv[1];
   char errbuf[PCAP_ERRBUF_SIZE];

   // Find the network address and mask of the listening device
   bpf_u_int32 net, mask;
   if ( pcap_lookupnet( dev, &net, &mask, errbuf) == -1 ) {
      std::cerr << "Failed to get network and mask of device: ";
      std::cerr << dev << std::endl;
      exit(-1);
   }

   // Open the device for recording
   pcap_t *handle = pcap_open_live(dev, MaxPacketSize, 1, 1000, errbuf);
   if ( handle == 0 ) {
      std::cerr << "Could not open device: " << dev << std::endl;
      std::cerr << "Error: " << errbuf << std::endl;
      exit(-1);
   }

   // Set the sig handler for termination
   setup_sigs( handle );

   // Compile a packet filter for 118.2 msg(s)
   struct bpf_program fp;
   // tcp port 4712
   // udp port 4713
   const char *filter = "udp";
   if ( pcap_compile( handle, &fp, filter, 0, net ) == -1 ) {
      std::cerr << "Failed to compile packet filter" << std::endl;
      std::cerr << "Filter: " << filter << std::endl;
      std::cerr << "Error: " << pcap_geterr( handle ) << std::endl;
      err_close( handle );
   }

   // Apply the filter
   if ( pcap_setfilter( handle, &fp ) == -1 ) {
      std::cerr << "Failed to install packet filter" << std::endl;
      err_close( handle );
   }

   // Put recorder into a dispatch loop
   if ( pcap_loop( handle, 0, pcap_callback, 0 ) == -1 ) {
      std::cerr << "Failed to dispatch callback" << std::endl;
      std::cerr << "Error: " << pcap_geterr( handle ) << std::endl;
      err_close( handle );
   }

   std::cout << "Finished recording" << std::endl;
   pcap_close( handle );
   return 0;
}
