BINARY = OUT
OBJECTS = main.o link.o graph.o connector.o htmlparser.o
HEADERS = connector.hpp graph.hpp htmlparser.hpp link.hpp

CXX = g++
CXXFLAGS = -std=c++11 -O0 -Wall -pedantic
LDFLAGS = 

.PHONY: all clean

all: $(BINARY)

clean:
	rm -f $(BINARY) $(OBJECTS)

$(BINARY): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
