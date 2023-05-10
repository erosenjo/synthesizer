#ifndef TUI_H
#define TUI_H

#include "samplegenerator.hpp"

class TUI
{
private:
    static const int WINDOW_Y_OFFSET = 2;
    static const int WINDOW_X_OFFSET = 2;
    static const int WINDOW_HEIGHT = 16;
    static const int WINDOW_WIDTH = 128;

    static const int SCALE_FACTOR = WINDOW_HEIGHT / 2;

    SampleGenerator sg;

    void displayString(int, int, char *);
    void drawRect(int, int, int, int);

    void drawWaveWindow();
    void clearWaveWindow();
    void drawWave();

public:
    void update();
};

#endif /* TUI_H */
