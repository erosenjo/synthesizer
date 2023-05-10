#ifndef SAMPLEGENERATOR_H
#define SAMPLEGENERATOR_H

class SampleGenerator
{
private:
    int amplitude;
    int frequency;

public:
    // Get 1 second of samples at 44100 Hz
    static const int N_SAMPLES = 44100;

    static int toFrequency(int);
    int getAmplitude();
    int getFrequency();

    void set(int, int);
    void getSamples(double *);
};

#endif /* SAMPLEGENERATOR_H */
