cflags = -g -pedantic -Wall -Wextra -std=c++11
targets = tui samplegenerator.o sine.o square.o triangle.o generator.o

aquilapath = aquila-src/aquila
generatorpath = $(aquilapath)/source/generator

all: $(targets)

clean:
	rm -rf $(targets) *.dSYM/

tui: tui.cpp samplegenerator.o sine.o square.o triangle.o generator.o
	g++ $(cflags) -o $@ $^ -lncurses

samplegenerator.o: samplegenerator.cpp
	g++ $(cflags) -c -o $@ $^

sine.o: $(generatorpath)/SineGenerator.cpp
	g++ $(cflags) -c -o $@ $^

square.o: $(generatorpath)/SquareGenerator.cpp
	g++ $(cflags) -c -o $@ $^

triangle.o: $(generatorpath)/TriangleGenerator.cpp
	g++ $(cflags) -c -o $@ $^

generator.o: $(generatorpath)/Generator.cpp	
	g++ $(cflags) -c -o $@ $^
