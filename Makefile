cflags = -g -pedantic -Wall -Wextra -std=c++11
targets = soundgen tui
aquilapath = aquila-src/aquila
rtaudiopath = rtaudio-src
generatorpath = $(aquilapath)/source/generator

all: $(targets)
	
clean: 
	rm -rf *.dSYM $(targets) 

soundgen_sine: generator.o sine.o plot.o soundgen_sine.cpp 
	g++ $(cflags) -D'__LINUX_ALSA__' -I/usr/include/rtaudio -o $@ $^ $(rtaudiopath)/RtAudio.cpp -lasound -lpthread

soundgen: soundgen.cpp 
	g++ $(cflags) -D'__LINUX_ALSA__' -I/usr/include/rtaudio -o $@ $^ $(rtaudiopath)/RtAudio.cpp -lasound -lpthread
	
tui: tui.c
	gcc -Wall -pedantic -Wextra -o $@ $< -lncurses

wavedrawtest: wavedrawtest.cpp generator.o sine.o square.o triangle.o
	g++ $(cflags) -o $@ $^ -lncurses

plot.o: $(aquilapath)/tools/TextPlot.cpp
	g++ $(cflags) -c -o $@ $^

sine.o: $(generatorpath)/SineGenerator.cpp
	g++ $(cflags) -c -o $@ $^

generator.o: $(generatorpath)/Generator.cpp	
	g++ $(cflags) -c -o $@ $^

refactor: refactor.cpp generator.o sine.o square.o triangle.o
	g++ $(cflags) -o $@ $^
