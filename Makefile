cflags = -g -pedantic -Wall -Wextra -std=c++11
targets = soundgen rtaudio.o tui
aquilapath = aquila-src/aquila
rtaudiopath = rtaudio-src
generatorpath = $(aquilapath)/source/generator

all: $(targets)
	
clean: 
	rm -f $(targets)

soundgen: soundgen.cpp rtaudio.o 
	g++ $(cflags) -o $@ $^ 
	
rtaudio.o: $(rtaudiopath)/RtAudio.cpp
	g++ $(cflags) -c -o $@ $^

tui: tui.c
	gcc -Wall -pedantic -Wextra -o $@ $< -lncurses
