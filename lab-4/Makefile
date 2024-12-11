CXX = g++
CXXFLAGS = -Wall -std=c++17

all: graph_coloring

graph_coloring: main.o Graph.o
	$(CXX) $(CXXFLAGS) -o graph_coloring main.o Graph.o

main.o: main.cpp Graph.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Graph.o: Graph.cpp Graph.h
	$(CXX) $(CXXFLAGS) -c Graph.cpp

clean:
	rm -f *.o graph_coloring