#ifndef SAMPLEGENERATOR_H
#define SAMPLEGENERATOR_H

class SampleGenerator
{
private:
    static const int N_SAMPLES = 50;
    static const int WINDOW_HEIGHT = 8;
    int amplitude;
    int frequency;

public:
    void set(int, int);
    void getScaledSamples(int *);
};

#endif /* SAMPLEGENERATOR_H */
