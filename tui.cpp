#include <cmath>
#include <cstring>
#include <curses.h>

#include "tui.hpp"
#include "samplegenerator.hpp"

// Executes mvprintw with given y and x offsets.
void TUI::displayString(int y, int x, char *symbol)
{
    mvprintw(y + WINDOW_Y_OFFSET, x + WINDOW_X_OFFSET, symbol);
}

// Draws a rectangle defined by given coordinates.
void TUI::drawRect(int y1, int x1, int y2, int x2)
{
    mvhline(y1, x1, 0, x2 - x1);
    mvhline(y2, x1, 0, x2 - x1);
    mvvline(y1, x1, 0, y2 - y1);
    mvvline(y1, x2, 0, y2 - y1);

    mvaddch(y1, x1, ACS_ULCORNER);
    mvaddch(y2, x1, ACS_LLCORNER);
    mvaddch(y1, x2, ACS_URCORNER);
    mvaddch(y2, x2, ACS_LRCORNER);
}

// Draws the waveform window.
void TUI::drawWaveWindow()
{
    int y1 = WINDOW_Y_OFFSET - 1;
    int x1 = WINDOW_X_OFFSET - 1;
    int y2 = WINDOW_HEIGHT + WINDOW_X_OFFSET + 1;
    int x2 = WINDOW_X_OFFSET + WINDOW_WIDTH;
    drawRect(y1, x1, y2, x2);
}

// Clears the waveform window.
void TUI::clearWaveWindow()
{
    for (int row = 0; row < WINDOW_HEIGHT + 1; row++)
    {
        for (int col = 0; col < SampleGenerator::N_SAMPLES; col++)
        {
            displayString(row, col, (char *)" ");
        }
    }
}

// Draws the waveform.
void TUI::drawWave()
{
    clearWaveWindow();

    // Get samples
    // N_SAMPLES is really just going to be 44100
    double samples[SampleGenerator::N_SAMPLES];
    sg.getSamples(samples);

    for (int s = 0; s < SampleGenerator::N_SAMPLES; s++)
    {
        // Only print '*' every DISPLAY_STEP = (N_SAMPLES / WINDOW_WIDTH)th sample
        if (s % DISPLAY_STEP == 0)
        {
            int scaled_sample = round(samples[s] * SCALE_FACTOR);
            displayString(scaled_sample + (WINDOW_HEIGHT / 2), (s / DISPLAY_STEP), (char *)"*");
        }
    }
}

void TUI::init()
{
    int amplitude = 255;
    int frequency = 100;
    sg.set(amplitude, frequency);

    // Initialize ncurses
    initscr();            // Initialize ncurses screen
    curs_set(0);          // Hide cursor
    timeout(-1);          // No timeout for getch()
    noecho();             // Suppress keyboard input print
    keypad(stdscr, TRUE); // Allow for arrow key input

    drawWaveWindow();

    // Get realtime keyboard input
    char display[20];

    int amp_step = 15;
    int freq_step = 25;

    while (1)
    {
        sg.set(amplitude, frequency);
        drawWave();
        switch (getch())
        {
        case KEY_UP:
            strcpy(display, "amp++  ");
            if (amplitude <= 255 - amp_step)
                amplitude += amp_step;
            break;
        case KEY_DOWN:
            strcpy(display, "amp--  ");
            if (amplitude >= amp_step)
                amplitude -= amp_step;
            break;
        case KEY_RIGHT:
            strcpy(display, "freq++ ");
            if (frequency <= 1000 - freq_step)
                frequency += freq_step;
            break;
        case KEY_LEFT:
            strcpy(display, "freq-- ");
            if (frequency >= freq_step)
                frequency -= freq_step;
            break;
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
        displayString(WINDOW_HEIGHT + 2, 0, (char *)display);

        mvprintw(WINDOW_HEIGHT + 4 + WINDOW_Y_OFFSET, WINDOW_X_OFFSET, "%6.2f %%", amplitude * 100 / (double)255);
        mvprintw(WINDOW_HEIGHT + 5 + WINDOW_Y_OFFSET, WINDOW_X_OFFSET, "%6d Hz", frequency);
    }

    getch();
    endwin();
}

int main()
{
    TUI t;
    t.init();

    return 0;
}
