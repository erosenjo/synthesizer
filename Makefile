cflags = -g -pedantic -Wall -Wextra -std=c++11
targets = alsa mac tui.o samplegenerator.o

rtaudio = rtaudio-src/RtAudio.cpp

all: $(targets)

clean:
	rm -rf $(targets) synth *.dSYM/

alsa: tui.o samplegenerator.o $(rtaudio)
	g++ $(cflags) -o synth $^ -D'__LINUX_ALSA__' -I/usr/include/rtaudio -lasound -lpthread -lncurses

mac: tui.o samplegenerator.o $(rtaudio)
	g++ $(cflags) -o synth $^ -D'__MACOSX_CORE__' -framework CoreAudio -framework CoreFoundation -lpthread -lncurses

tui.o: tui.cpp tui.hpp samplegenerator.hpp
	g++ $(cflags) -c -o $@ $<

samplegenerator.o: samplegenerator.cpp samplegenerator.hpp
	g++ $(cflags) -c -o $@ $<
