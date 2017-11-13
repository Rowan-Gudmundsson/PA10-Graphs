CPP_FLAGS = -Wall -std=c++98

all: test

test: test12 WeightedGraph
	g++ $(CPP_FLAGS) -o test12 test12.o WeightedGraph.o

test12: test12.cpp
	g++ $(CPP_FLAGS) -c test12.cpp

WeightedGraph: WeightedGraph.cpp WeightedGraph.h
	g++ $(CPP_FLAGS) -c WeightedGraph.cpp
