#include <ncurses.h> //ncurses.h includes stdio.h
#include <string.h>

/*
 * This file handles the tui. For now it is very general, because I am still learning about ncurses.
 * I am following the tutorial found here: https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/index.html
 */

#define DIST_FROM_TOP_TO_TITLE 3
#define DIST_FROM_TITLE_TO_MENU 3
#define DIST_FROM_MENU_TO_BOTTOM 2
#define DIST_FROM_MENU_TO_SIDES 5

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

	mvprintw(DIST_FROM_TOP_TO_TITLE,(col-strlen(msg))/2,msg); //move printing cursor to (y,x) and print
	refresh(); //prints the buffer to the screen
	
	//making a menu
    int menuy = row - (DIST_FROM_TITLE_TO_MENU + DIST_FROM_TOP_TO_TITLE + DIST_FROM_MENU_TO_BOTTOM);
    int menux = col - (DIST_FROM_MENU_TO_SIDES * 2);
    int starty = DIST_FROM_TITLE_TO_MENU + DIST_FROM_TOP_TO_TITLE; //origin y coordinate for menu
    int startx = DIST_FROM_MENU_TO_SIDES; //origin x coordinate for menu
	WINDOW *menu = newwin(menuy, menux, starty, startx);
    wborder(menu, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(menu);

	getch(); //waits for user input
	endwin(); //end curses mode
	return 0;
}
