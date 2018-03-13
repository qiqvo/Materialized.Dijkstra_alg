appname=main
CXX=g++-6
parse_stl_DIR=./parse_stl

RM=rm -f
CPPFLAGS= -g -Wall -std=c++11 -I$(parse_stl_DIR)

SRCS=$(shell find . -maxdepth 2 -name "*.cpp") 
OBJS=$(subst .cpp,.o,$(SRCS))

all: $(appname)

$(appname): $(OBJS)
	$(CXX) -o main $(OBJS)

$(OBJS): $(SRCS)
# parse_stl.o: $(parse_stl_DIR)/parse_stl.cpp

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) $(appname)