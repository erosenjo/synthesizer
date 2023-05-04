#ifndef SAMPLEGENERATOR_H
#define SAMPLEGENERATOR_H

class SampleGenerator
{
private:
    int amplitude;
    int frequency;

public:
    static const int N_SAMPLES = 50;

    void set(int, int);
    void getSamples(double *);
};

#endif /* SAMPLEGENERATOR_H */
