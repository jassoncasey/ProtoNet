# Written by Jasson Casey
# Copyright (C) 2011. All rights reserved.

COMPILER=g++
CFLAGS=-Wall -g 
TARGET=pmurec
TEST1=test1
LIBS=-lpcap

TARGETS= $(TARGET) $(TEST1)

OBJS= Time.o Error.o Packet.o Sniffer.o 

default: $(TEST1) $(TARGET)

$(TEST1) : $(OBJS) $(TEST1).o
	$(COMPILER) $(CLFAGS) -g -o $@ $^ $(LIBS)

$(TARGET) : $(OBJS) $(TARGET).o
	$(COMPILER) $(CLFAGS) -g -o $@ $^ $(LIBS)

%.o:%.cc
	$(COMPILER) $(CLFAGS) -g -c $^

clean:
	rm -f $(TARGETS)
	rm -r *.o
