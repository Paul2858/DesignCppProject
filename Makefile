CC  = gcc
CXX = g++-11
INCLUDES =
CFLAGS   = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES) -std=c++20 -O3
LDFLAGS  = -g
LDLIBS   =

main: main.o
main.o: main.cpp

test-concepts: test-concepts.o
test-concepts.o: test-concepts.cpp

# clean removes intermediate files
# PHONY = not a file
.PHONY: clean
clean:
	rm -rf *.o a.out core main test-concepts *.dSYM .vscode

# all builds multiple programs if needed, and cleans first
.PHONY: all
all: clean main
