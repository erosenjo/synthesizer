cflags = -g -pedantic -Wall -Wextra -std=c++11
targets = soundgen tui
aquilapath = aquila-src/aquila
rtaudiopath = rtaudio-src
generatorpath = $(aquilapath)/source/generator

all: $(targets)
	
clean: 
	rm -f $(targets)

soundgen: soundgen.cpp 
	g++ $(cflags) -D'__LINUX_ALSA__' -I/usr/include/rtaudio -o $@ $^ $(rtaudiopath)/RtAudio.cpp -lasound -lpthread
	
tui: tui.c
	gcc -Wall -pedantic -Wextra -o $@ $< -lncurses
