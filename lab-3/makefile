CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra -O2

EXECUTABLE = graph_checker
SOURCES = main.cpp Graph.cpp
OBJECTS = $(SOURCES:.cpp=.o)
DEPS = Graph.h

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)