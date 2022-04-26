# CC = gcc
# CXX = g++
CC = g++
INCLUDES =
CXXFLAGS = -g -Wall $(INCLUDES) -std=c++20 -O3

# -g for debugging info
LDFLAGS = -g
LDLIBS =

main: main.o Graph.o PathFinder.o
main.o: main.cpp Graph.h PathFinder.h

Graph.o: Graph.cpp Graph.h

PathFinder.o: PathFinder.cpp PathFinder.h

test-concepts: test-concepts.o
test-concepts.o: test-concepts.cpp

# clean removes intermediate files
# PHONY = not a file
.PHONY: clean
clean:
	rm -rf *.o a.out core main

# all builds multiple programs if needed, and cleans first
.PHONY: all
all: clean main
