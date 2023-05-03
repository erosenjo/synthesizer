cflags = -g -pedantic -Wall -Wextra -std=c++11
targets = tui samplegenerator.o sine.o square.o triangle.o generator.o rtaudio.o
aquilapath = aquila-src/aquila
rtaudiopath = rtaudio-src
generatorpath = $(aquilapath)/source/generator

all: $(targets)
	
clean: 
	rm -rf $(targets) *.dSYM/

# Is there a more efficient way to link all generator files?
tui: tui.cpp samplegenerator.o
	g++ $(cflags) -o $@ $^ -lncurses

samplegenerator.o: samplegenerator.cpp $(aquilapath)/aquila.h
	g++ $(cflags) -c -o $@ $^

sine.o: $(generatorpath)/SineGenerator.cpp
	g++ $(cflags) -c -o $@ $^

square.o: $(generatorpath)/SquareGenerator.cpp
	g++ $(cflags) -c -o $@ $^

triangle.o: $(generatorpath)/TriangleGenerator.cpp
	g++ $(cflags) -c -o $@ $^

generator.o: $(generatorpath)/Generator.cpp	
	g++ $(cflags) -c -o $@ $^

rtaudio.o: $(rtaudiopath)/RtAudio.cpp
	g++ $(cflags) -c -o $@ $^
