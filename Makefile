cflags = -g -pedantic -Wall -Wextra -std=c++11
targets = alsa mac tui.o samplegenerator.o sine.o square.o triangle.o generator.o

aquilapath = aquila-src/aquila
rtaudio = rtaudio-src/RtAudio.cpp
generatorpath = $(aquilapath)/source/generator

all: $(targets)

clean:
	rm -rf $(targets) *.dSYM/

alsa: tui.o samplegenerator.o sine.o square.o triangle.o generator.o $(rtaudio)
	g++ $(cflags) -o synth $^ -D'__LINUX_ALSA__' -I/usr/include/rtaudio -lasound -lpthread -lncurses

mac: tui.o samplegenerator.o sine.o square.o triangle.o generator.o $(rtaudio)
	g++ $(cflags) -o synth $^ -D'__MACOSX_CORE__' -framework CoreAudio -framework CoreFoundation -lpthread -lncurses

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
