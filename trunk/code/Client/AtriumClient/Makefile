# genericish Makefile
#
# Very quickly hacked up - needs some work :-)
# A couple of minor hacks in the code, switched in with HACKY_LINUX_HACK define
#


SFML = /home/ben/speculative/SFML-2.0-rc
RAKNET = /home/ben/speculative/raknet

SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS) )

CC := g++

EXE = atrium
LIBS = `pkg-config --libs sfml-graphics` -lRakNetLibStatic
CFLAGS = -DHACKY_LINUX_HACK -std=c++0x -Wall -Isrc `pkg-config --cflags sfml-graphics` -Iinclude -I ../../Common -I$(RAKNET)/include -I$(RAKNET)/include/raknet -L$(RAKNET)/Lib/RakNetLibStatic


ifdef RELEASE
	CFLAGS += -O2 -DNDEBUG
else
	CFLAGS += -ggdb
endif


all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS) $(LIBS)
ifdef RELEASE
	strip $(EXE)
endif


%.o : %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJS)
	rm -f $(EXE)
	rm -f .depend
	rm -f tags

tags: $(SRCS)
	ctags -R /usr/include/SFML src include ../../RakNet/


depend:
	$(CC) -MM $(CFLAGS) $(SRCS) > .depend

ifeq ($(wildcard .depend),.depend)
include .depend
endif



