cflags = -g -pedantic -Wall -Wextra -std=c++11
targets = synth tui.o samplegenerator.o sine.o square.o triangle.o generator.o
aquilapath = aquila-src/aquila
generatorpath = $(aquilapath)/source/generator
all: $(targets)
	
clean: 
	rm -rf *.dSYM $(targets) 

soundgen: soundgen.cpp generator.o sine.o 
	g++ $(cflags) -D'__LINUX_ALSA__' -I/usr/include/rtaudio -o $@ $^ $(rtaudiopath)/RtAudio.cpp -lasound -lpthread
	
wavedrawtest: wavedrawtest.cpp generator.o sine.o square.o triangle.o
	g++ $(cflags) -o $@ $^ -lncurses

plot.o: $(aquilapath)/tools/TextPlot.cpp
	g++ $(cflags) -c -o $@ $^

synth: tui.o samplegenerator.o sine.o square.o triangle.o generator.o
	g++ $(cflags) -o $@ $^ -lncurses

tui.o: tui.cpp tui.hpp samplegenerator.hpp
	g++ $(cflags) -c -o $@ tui.cpp

samplegenerator.o: samplegenerator.cpp samplegenerator.hpp
	g++ $(cflags) -c -o $@ samplegenerator.cpp

sine.o: $(generatorpath)/SineGenerator.cpp
	g++ $(cflags) -c -o $@ $^

generator.o: $(generatorpath)/Generator.cpp	
	g++ $(cflags) -c -o $@ $^

refactor: refactor.cpp generator.o sine.o square.o triangle.o
	g++ $(cflags) -o $@ $^

square.o: $(generatorpath)/SquareGenerator.cpp
	g++ $(cflags) -c -o $@ $^

triangle.o: $(generatorpath)/TriangleGenerator.cpp
	g++ $(cflags) -c -o $@ $^

