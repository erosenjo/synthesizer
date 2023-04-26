#include <cmath>
#include <curses.h>

#include "aquila-src/aquila/aquila.h"

#define PI 3.141592
#define Y_OFFSET 2
#define X_OFFSET 2

// Draws a rectangle defined by given coordinates.
void drawRect(int y1, int x1, int y2, int x2)
{
	y1 += Y_OFFSET;
	y2 += Y_OFFSET;
	x1 += X_OFFSET;
	x2 += X_OFFSET;

	mvhline(y1, x1, 0, x2 - x1);
	mvhline(y2, x1, 0, x2 - x1);
	mvvline(y1, x1, 0, y2 - y1);
	mvvline(y1, x2, 0, y2 - y1);

	mvaddch(y1, x1, ACS_ULCORNER);
	mvaddch(y2, x1, ACS_LLCORNER);
	mvaddch(y1, x2, ACS_URCORNER);
	mvaddch(y2, x2, ACS_LRCORNER);
}

// Executes mvprintw with given y and x offsets.
void displaySymbol(int y, int x, char *symbol)
{
	mvprintw(y + Y_OFFSET, x + X_OFFSET, symbol);
}

int main()
{
	int amplitude = 255;
	int frequency = 80;

	int height = 12;	// Height of wave window
	int n_samples = 50; // Width of wave window
	double scale_factor = height / ((double)255 * 2);

	// Initialize ncurses
	initscr();	 // Initialize ncurses screen
	curs_set(0); // Hide cursor
	timeout(-1); // No timeout for getch()
	noecho();	 // Suppress keyboard input print

	drawRect(-1, -1, height + 1, n_samples); // Draw wave window

	// Generate waveform
	Aquila::SineGenerator sinegen(1000);
	sinegen.setFrequency(frequency)
		.setAmplitude(amplitude)
		.generate(n_samples);

	Aquila::TriangleGenerator trigen(1000);
	trigen.setFrequency(frequency)
		.setAmplitude(amplitude)
		.generate(n_samples);

	Aquila::SquareGenerator squaregen(1000);
	squaregen.setFrequency(frequency)
		.setAmplitude(amplitude)
		.generate(n_samples);

	// Get samples
	const Aquila::SampleType *sample_array = sinegen.toArray();
	for (int s = 0; s < n_samples; s++)
	{
		int scaled_sample = round(sample_array[s] * scale_factor);
		displaySymbol(scaled_sample + (height / 2), s, (char *)"*");
	}

	// Get realtime keyboard input
	char display[10];
	while (1)
	{
		switch (getch())
		{
		case 'a':
			strcpy(display, "C      ");
			break;
		case 'w':
			strcpy(display, "C# / Db");
			break;
		case 's':
			strcpy(display, "D      ");
			break;
		case 'e':
			strcpy(display, "D# / Eb");
			break;
		case 'd':
			strcpy(display, "E      ");
			break;
		case 'f':
			strcpy(display, "F      ");
			break;
		case 't':
			strcpy(display, "F# / Gb");
			break;
		case 'g':
			strcpy(display, "G      ");
			break;
		case 'y':
			strcpy(display, "G# / Ab");
			break;
		case 'h':
			strcpy(display, "A      ");
			break;
		case 'u':
			strcpy(display, "A# / Bb");
			break;
		case 'j':
			strcpy(display, "B      ");
			break;
		case 'k':
			strcpy(display, "C      ");
			break;
		case 'o':
			strcpy(display, "C# / Db");
			break;
		case 'l':
			strcpy(display, "D      ");
			break;
		case 'p':
			strcpy(display, "D# / Eb");
			break;
		case ';':
			strcpy(display, "E      ");
			break;
		case '\'':
			strcpy(display, "F      ");
			break;
		}
		displaySymbol(height + 2, 0, (char *)display);
	}

	getch();
	endwin();

	return 0;
}
