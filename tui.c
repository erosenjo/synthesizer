#include <ncurses.h> //ncurses.h includes stdio.h
#include <string.h>

/*
 * This file handles the tui. For now it is very general, because I am still learning about ncurses.
 * I am following the tutorial found here: https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/index.html
 */

int main() {

	/* VARIABLES */
	char msg[] = "Terminal Synth"; //title for printing
	int row, col; //variables to store size of window

	/* FUNCTION PROTOTYPES */

	/* INITIALIZATION */
	initscr(); //start curses mode
	cbreak(); //disables having to use enter to send input to the program, but retains ability to C-c it, etc.
		  //replace with raw() to manually control use of terminal signal commands, like C-c, etc.
	noecho(); //prevents input being echoed to the screen
	keypad(stdscr, TRUE); //enables the use of the arrow keys 
			      //to interact with the stdscr (the one we are using)
			      //and also other keys like the FN keys

	/* NCURSES STUFF */

	getmaxyx(stdscr,row,col); //get size of window

	mvprintw(5,(col-strlen(msg))/2,msg); //move printing cursor to (y,x) and print
	refresh(); //prints the buffer to the screen
	
	//making a menu
	

	getch(); //waits for user input
	endwin(); //end curses mode
	return 0;
}
