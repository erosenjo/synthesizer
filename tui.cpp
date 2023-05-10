#include <cmath>
#include <cstring>
#include <curses.h>

#include "samplegenerator.h"
#include "tui.hpp"
#include "rtaudio-src/RtAudio.h"

//sound generating function
int sine(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *userData )
{
    double *buffer = (double *) outputBuffer;
    SampleGenerator *sg = (SampleGenerator *) userData;

    if ( status ) 
        std::cout << "Stream underflow detected!" << std::endl;

    getSamples(buffer, nBufferFrames, sg, streamTime);
 
    return 0;
}

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
    int y2 = WINDOW_HEIGHT + WINDOW_Y_OFFSET + 1;
    int x2 = WINDOW_WIDTH + WINDOW_X_OFFSET + 1;
    drawRect(y1, x1, y2, x2);
}

// Clears the waveform window.
void TUI::clearWaveWindow()
{
    for (int row = 0; row < WINDOW_HEIGHT + 1; row++)
    {
        for (int col = 0; col < N_SAMPLES; col++)
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
    double *samples = (double *) malloc(sizeof(double) * N_SAMPLES);
    getSamples((double *) samples, (unsigned int) N_SAMPLES, sg, (double) 0);

    for (int s = 0; s < N_SAMPLES; s++)
    {
        // Only print '*' every DISPLAY_STEP = (N_SAMPLES / WINDOW_WIDTH)th sample
        if (s % DISPLAY_STEP == 0)
        {
            int scaled_sample = round(samples[s] * SCALE_FACTOR);
            displayString(scaled_sample + (WINDOW_HEIGHT / 2), (s / DISPLAY_STEP), (char *)"*");
        }
    }
    free(samples);
}

void TUI::init()
{
    // Set initial amplitude and frequency
    sg = (SampleGenerator *) malloc(sizeof(SampleGenerator));
    sg->amplitude = 255;
    sg->octave = 0;
    sg->semitones = 0;

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
    int semitones = 0;

    // open RTAudio stream here with sg as userData var
    //copied from https://www.music.mcgill.ca/~gary/rtaudio/playback.html
    //modified slightly
  RtAudio dac;
  if ( dac.getDeviceCount() < 1 ) {
    std::cout << "\nNo audio devices found!\n";
    exit( 0 );
  }
  RtAudio::StreamParameters parameters;
  parameters.deviceId = dac.getDefaultOutputDevice();
  parameters.nChannels = 1;
  parameters.firstChannel = 0;
  unsigned int sampleRate = 44100;
  unsigned int bufferFrames = 256; // 256 sample frames
  try {
    dac.openStream( &parameters, NULL, RTAUDIO_FLOAT64,
                    sampleRate, &bufferFrames, &sine, (void *)sg );
    dac.startStream();
  }
  catch ( RtAudioError& e ) {
    e.printMessage();
    exit( 0 );
  }
//end copied segment
    
    int running = 1;
    while (running)
    {
        int amplitude = sg->amplitude;
        int semitones = sg->semitones;

        drawWave();

        // Print amplitude and frequency
        displayString(WINDOW_HEIGHT + 2, 0, (char *)display);
        mvprintw(WINDOW_HEIGHT + 4 + WINDOW_Y_OFFSET, WINDOW_X_OFFSET, "%6.2f %%", amplitude * 100 / (double)255);
        mvprintw(WINDOW_HEIGHT + 5 + WINDOW_Y_OFFSET, WINDOW_X_OFFSET, "%6d Hz", toFrequency(sg));

        switch (getch())
        {
        case KEY_UP:
            strcpy(display, "amp++  ");
            if (amplitude <= 255 - amp_step)
                sg->amplitude+= amp_step; 
            break;
        case KEY_DOWN:
            strcpy(display, "amp--  ");
            if (amplitude >= amp_step)
                sg->amplitude-= amp_step;
            break;
        case KEY_RIGHT:
            strcpy(display, "freq++ ");
            if (sg->octave <= 6)
                semitones++;
            break;
        case KEY_LEFT:
            strcpy(display, "freq-- ");
            if (semitones >= 0)
                semitones--;
            break;
        case 'q':
            running = 0;
        case 'a':
            strcpy(display, "C      ");
            semitones = -9;
            break;
        case 'w':
            strcpy(display, "C# / Db");
            semitones = -8;
            break;
        case 's':
            strcpy(display, "D      ");
            semitones = -7;
            break;
        case 'e':
            strcpy(display, "D# / Eb");
            semitones = -6;
            break;
        case 'd':
            strcpy(display, "E      ");
            semitones = -5;
            break;
        case 'f':
            strcpy(display, "F      ");
            semitones = -4;
            break;
        case 't':
            strcpy(display, "F# / Gb");
            semitones = -3;
            break;
        case 'g':
            strcpy(display, "G      ");
            semitones = -2;
            break;
        case 'y':
            strcpy(display, "G# / Ab");
            semitones = -1;
            break;
        case 'h':
            strcpy(display, "A      ");
            semitones = 0;
            break;
        case 'u':
            strcpy(display, "A# / Bb");
            semitones = 1;
            break;
        case 'j':
            strcpy(display, "B      ");
            semitones = 2;
            break;
        case 'k':
            strcpy(display, "C      ");
            semitones = 3;
            break;
        case 'o':
            strcpy(display, "C# / Db");
            semitones = 4;
            break;
        case 'l':
            strcpy(display, "D      ");
            semitones = 5;
            break;
        case 'p':
            strcpy(display, "D# / Eb");
            semitones = 6;
            break;
        case ';':
            strcpy(display, "E      ");
            semitones = 7;
            break;
        case '\'':
            strcpy(display, "F      ");
            semitones = 8;
            break;
        }

        sg->semitones = semitones;
    }

    getch();
    endwin();

    //copied from https://www.music.mcgill.ca/~gary/rtaudio/playback.html
    try {
        // Stop the stream
        dac.stopStream();
    }
    catch (RtAudioError& e) {
        e.printMessage();
    }
    if ( dac.isStreamOpen() ) dac.closeStream();
    //end copied segment
    

    //TODO- memory management
    free(sg);

}

int main()
{
    TUI t;
    t.init();

    // close rtaudio stream
    return 0;
}
