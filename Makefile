cflags = -g -pedantic -Wall -Wextra -std=c++11
targets = tui
aquilapath = aquila-src/aquila
rtaudiopath = rtaudio-src
generatorpath = $(aquilapath)/source/generator

all: $(targets)
	
clean: 
	rm -rf $(targets) *.dSYM/

# Is there a more efficient way to link all generator files?
tui: tui.cpp samplegenerator.cpp
	g++ $(cflags) -o tui tui.cpp samplegenerator.cpp -lncurses
