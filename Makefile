cflags = -g -pedantic -Wall -Wextra -std=c++11
targets = tui
clean = playsound

rtaudiopath = rtaudio-src

all: $(targets)

clean:
	rm -rf $(targets) $(clean) *.dSYM/

alsa: playsound.cpp 
	g++ $(cflags) -D'__LINUX_ALSA__' -I/usr/include/rtaudio -o playsound $^ $(rtaudiopath)/RtAudio.cpp -lasound -lpthread

mac: playsound.cpp
	g++ $(cflags) -D'__MACOSX_CORE__' -o playsound $^ $(rtaudiopath)/RtAudio.cpp -framework CoreAudio -framework CoreFoundation -lpthread

tui: tui.c
	gcc -Wall -pedantic -Wextra -o $@ $< -lncurses

synth: tui.o samplegenerator.o sine.o square.o triangle.o generator.o
	g++ $(cflags) -o $@ $^ -lncurses

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
