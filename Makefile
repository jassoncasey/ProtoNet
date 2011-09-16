# Written by Jasson Casey
# Copyright (C) 2011. All rights reserved.

COMPILER=g++
CFLAGS=-Wall 
TARGET=pmurec
LIBS=-lpcap

OBJS= Time.o Error.o Packet.o Sniffer.o

$(TARGET) : $(OBJS)
	$(COMPILER) -o $@ $^ $(LIBS)

%.o:%.cc
	$(COMPILER) $(CLFAGS) -c $^

clean:
	rm -f $(TARGET)
	rm -f $(OBJS)
