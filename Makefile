cflags = -g -pedantic -Wall -Wextra -std=c++11
targets = tui
clean = synth

rtaudiopath = rtaudio-src

all: $(targets)

clean:
	rm -rf $(targets) $(clean) *.dSYM/

alsa: tui.cpp samplegenerator.c 
	g++ $(cflags) -D'__LINUX_ALSA__' -I/usr/include/rtaudio -o synth $^ $(rtaudiopath)/RtAudio.cpp -lasound -lpthread -lncurses

mac: playsound.cpp samplegenerator.c
	g++ $(cflags) -D'__MACOSX_CORE__' -o synth $^ $(rtaudiopath)/RtAudio.cpp -framework CoreAudio -framework CoreFoundation -lpthread -lncurses
