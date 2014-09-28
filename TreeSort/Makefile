CC=gcc
CXX=g++
CPPFLAGS=-g -Wall
LDFLAGS=-g
LDLIBS=

# add any addition source files here (space seperated)
SRCS=main.cpp treesort.cpp

OBJS=$(subst .cpp,.o,$(SRCS))

all: treesort 

treesort: $(OBJS)
	$(CXX) $(LDFLAGS) -o treesort $(OBJS) $(LDLIBS)

# dependency rules go here, if needed

clean:
	$(RM) $(OBJS) treesort
