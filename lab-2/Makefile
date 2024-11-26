TARGET = dijkstra

CXX = g++

CXXFLAGS = -Wall -std=c++17

SRCS = main.cpp graph.cpp dijkstra.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean