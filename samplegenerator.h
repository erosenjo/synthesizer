#ifndef SAMPLEGENERATOR_H
#define SAMPLEGENERATOR_H

#define N_SAMPLES 256

typedef struct SampleGenerator
{
    int amplitude;
    int frequency;

} SampleGenerator;

int toFrequency(int);
void getSamples(double *buffer, unsigned int nBufferFrames, SampleGenerator *sg, double streamTime);

#endif /* SAMPLEGENERATOR_H */
