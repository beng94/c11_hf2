BINARY = OUT
OBJECTS = main.o link.o graph.o connector.o htmlparser.o
HEADERS = connector.hpp graph.hpp htmlparser.hpp link.hpp

CXX = g++ -g
CXXFLAGS = -std=c++11 -Wall -pedantic
DLIBS = -lcurl

.PHONY: all clean

all: $(BINARY)

clean:
	rm -f $(BINARY) $(OBJECTS)

$(BINARY): $(OBJECTS)
	$(CXX)  $^ -o $@ $(DLIBS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
