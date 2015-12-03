BINARY = OUT
OBJECTS = main.o link.o graph.o connector.o
HEADERS = connector.hpp graph.hpp link.hpp

CXX = clang++-3.5 -g
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
