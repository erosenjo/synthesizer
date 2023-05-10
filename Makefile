cflags = -g -pedantic -Wall -Wextra -std=c++11
targets = alsa mac synthesizer.o samplegenerator.o tui.o

rtaudio = rtaudio-src/RtAudio.cpp

all: $(targets)

clean:
	rm -rf $(targets) synth *.dSYM/

alsa: synthesizer.cpp samplegenerator.cpp tui.cpp $(rtaudio)
	g++ $(cflags) -o synth $^ -D'__LINUX_ALSA__' -I/usr/include/rtaudio -lasound -lpthread -lncurses

mac: synthesizer.o samplegenerator.o tui.o $(rtaudio)
	g++ $(cflags) -o synth $^ -D'__MACOSX_CORE__' -framework CoreAudio -framework CoreFoundation -lpthread -lncurses

synthesizer.o: synthesizer.cpp samplegenerator.hpp tui.hpp
	g++ $(cflags) -c -o $@ $<

samplegenerator.o: samplegenerator.cpp samplegenerator.hpp
	g++ $(cflags) -c -o $@ $<

tui.o: tui.cpp tui.hpp samplegenerator.hpp
	g++ $(cflags) -c -o $@ $<
