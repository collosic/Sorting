CC=gcc
CXX=g++
CPPFLAGS=-g -Wall
LDFLAGS=-g
LDLIBS=

# add any addition source files here (space seperated)
SRCS=main.cpp mergesort.cpp

OBJS=$(subst .cpp,.o,$(SRCS))

all: mergesort

mergesort: $(OBJS)
	$(CXX) $(LDFLAGS) -o mergesort $(OBJS) $(LDLIBS)

# dependency rules go here, if needed

clean:
	$(RM) $(OBJS) mergesort