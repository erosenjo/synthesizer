#include <ncurses.h>

/*
 * This file handles the tui. For now it is very general, because I am still learning about ncurses.
 * I am following the tutorial found here: https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/index.html
 */

int main() {
	initscr(); //start curses mode
	endwin(); //end curses mode
}
