CC=gcc
CXX=g++
CPPFLAGS=-g -Wall
LDFLAGS=-g
LDLIBS=

# add any addition source files here (space seperated)
SRCS=main.cpp quicksort.cpp

OBJS=$(subst .cpp,.o,$(SRCS))

all: quicksort 

quicksort: $(OBJS)
	$(CXX) $(LDFLAGS) -o quicksort $(OBJS) $(LDLIBS)

# dependency rules go here, if needed

clean:
	$(RM) $(OBJS) quicksort
