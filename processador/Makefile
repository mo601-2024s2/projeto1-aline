CC=gcc
CXX=g++
CPPFLAGS=
LDFLAGS=
LDLIBS=
RM=rm -f

SRCS=processor.cpp fetch.cpp decode.cpp execute.cpp log.cpp
OBJS=$(subst .cc,.o,$(SRCS))

build:
	$(CXX) $(LDFLAGS) -o processor $(OBJS) $(LDLIBS)

processor.o: processor.cpp processor.hpp
	$(CXX) $(CPPFLAGS) -c processor.cpp

log.o: log.cpp log.hpp
	$(CXX) $(CPPFLAGS) -c log.cpp

execute.o: execute.cpp execute.hpp
	$(CXX) $(CPPFLAGS) -c execute.cpp

decode.o: decode.cpp decode.hpp
	$(CXX) $(CPPFLAGS) -c decode.cpp

fetch.o: fetch.cpp fetch.hpp
	$(CXX) $(CPPFLAGS) -c fetch.cpp 

clean:
	$(RM) *.o processor