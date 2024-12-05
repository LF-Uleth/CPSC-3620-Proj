# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall

# Targets
PROGRAMS = create bruteforce divideconquer

# Rules
all: $(PROGRAMS)

create: create.cc
	$(CXX) $(CXXFLAGS) -o create create.cc

bruteforce: bruteforce.cc
	$(CXX) $(CXXFLAGS) -o bruteforce bruteforce.cc

divideconquer: divideconquer.cc
	$(CXX) $(CXXFLAGS) -o divideconquer divideconquer.cc

clean:
	rm -f $(PROGRAMS) *.o

.PHONY: all clean
