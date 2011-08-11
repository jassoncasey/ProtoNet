# Written by Jasson Casey
# Copyright (C) 2011. All rights reserved.

COMPILER=g++
CLFLAGS=-Wall 
TARGET=pmurec
LIBS=-lpcap

OBJS=Driver.o Packet.o Protocol.o Device.o Util.o \
	  EthernetII.o #IPv4.o #TCP.o #UDP.o \
	  ARP.o ICMP.o DHCP.o

$(TARGET) : $(OBJS)
	$(COMPILER) -o $@ $^ $(LIBS)

%.o:%.cc
	$(COMPILER) $(CLFAGS) -c $^

clean:
	rm -f $(TARGET)
	rm -f $(OBJS)
