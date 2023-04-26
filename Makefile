cflags = -g -pedantic -Wall -Wextra -std=c++11
targets = wavegen sine.o square.o triangle.o generator.o plot.o rtaudio.o tui wavedrawtest
aquilapath = aquila-src/aquila
rtaudiopath = rtaudio-src
generatorpath = $(aquilapath)/source/generator

all: $(targets)
	
clean: 
	rm -rf $(targets) *.dSYM/

wavegen: wavegen.cpp generator.o plot.o sine.o rtaudio.o 
	g++ $(cflags) -o $@ $^ 

# Is there a more efficient way to link all generator files?
sine.o: $(generatorpath)/SineGenerator.cpp
	g++ $(cflags) -c -o $@ $^

square.o: $(generatorpath)/SquareGenerator.cpp
	g++ $(cflags) -c -o $@ $^

triangle.o: $(generatorpath)/TriangleGenerator.cpp
	g++ $(cflags) -c -o $@ $^

generator.o: $(generatorpath)/Generator.cpp	
	g++ $(cflags) -c -o $@ $^

plot.o: $(aquilapath)/tools/TextPlot.cpp
	g++ $(cflags) -c -o $@ $^

rtaudio.o: $(rtaudiopath)/RtAudio.cpp
	g++ $(cflags) -c -o $@ $^

tui: tui.c
	gcc -Wall -pedantic -Wextra -o $@ $< -lncurses

wavedrawtest: wavedrawtest.cpp generator.o sine.o square.o triangle.o
	g++ $(cflags) -o $@ $^ -lncurses
