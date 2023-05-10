cflags = -g -pedantic -Wall -Wextra -std=c++11
targets = alsa mac synth.o tui.o samplegenerator.o sine.o square.o triangle.o generator.o

aquilapath = aquila-src/aquila
rtaudiopath = rtaudio-src
generatorpath = $(aquilapath)/source/generator

all: $(targets)

clean:
	rm -rf $(targets) *.dSYM/

alsa: tui.cpp samplegenerator.cpp
	g++ $(cflags) -D'__LINUX_ALSA__' -I/usr/include/rtaudio -o synth $^ $(rtaudiopath)/RtAudio.cpp -lasound -lpthread -lncurses

mac: tui.o samplegenerator.o sine.o square.o triangle.o generator.o
	g++ $(cflags) -D'__MACOSX_CORE__' -o synth $^ $(rtaudiopath)/RtAudio.cpp -framework CoreAudio -framework CoreFoundation -lpthread -lncurses

tui.o: tui.cpp tui.hpp samplegenerator.hpp
	g++ $(cflags) -c -o $@ tui.cpp

samplegenerator.o: samplegenerator.cpp samplegenerator.hpp
	g++ $(cflags) -c -o $@ samplegenerator.cpp

sine.o: $(generatorpath)/SineGenerator.cpp
	g++ $(cflags) -c -o $@ $^

square.o: $(generatorpath)/SquareGenerator.cpp
	g++ $(cflags) -c -o $@ $^

triangle.o: $(generatorpath)/TriangleGenerator.cpp
	g++ $(cflags) -c -o $@ $^

generator.o: $(generatorpath)/Generator.cpp	
	g++ $(cflags) -c -o $@ $^
