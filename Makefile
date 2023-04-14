cflags = -g -pedantic -Wall -Wextra -std=c++11
targets = wavegen sine.o generator.o plot.o tui
aquilapath = aquila-src/aquila
rtaudiopath = rtaudio-src/
generatorpath = $(aquilapath)/source/generator

all: $(targets)
	
clean: 
	rm -f $(targets)

wavegen: generator.o plot.o sine.o rtaudio.o wavegen.cpp
	g++ $(cflags) sine.o generator.o plot.o wavegen.cpp -o wavegen
	
sine.o: generator.o $(aquilapath)/source/generator/SineGenerator.cpp
	g++ $(cflags) $(generatorpath)/SineGenerator.cpp -c -o sine.o

generator.o: $(aquilapath)/source/generator/Generator.cpp
	g++ $(cflags) $(generatorpath)/Generator.cpp -c -o generator.o 

plot.o: $(aquilapath)/tools/TextPlot.cpp
	g++ $(cflags) $(aquilapath)/tools/TextPlot.cpp -c -o plot.o

rtaudio.o: $(rtaudiopath)/RtAudio.cpp
	g++ $(cflags) -c -o $@ $^

tui: tui.c
	gcc -Wall -pedantic -Wextra -o $@ $< -lncurses
