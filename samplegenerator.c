#include <math.h>

#include "samplegenerator.h"

int toFrequency(SampleGenerator *sg)
{
    return round(440 * pow(2, sg->octave) * pow(2, sg->semitones / (double)12));
}

void getSamples(double *buffer, unsigned int nBufferFrames, SampleGenerator *sg, double streamTime)
{
    static double pi = 3.14159;

    for (unsigned int i = 0; i <= nBufferFrames; i++){
        *buffer++ = (sg->amplitude / (double) 255) * sin(
                //equation for the sin wave.
                //everything until "freq" converts a time to radians
                //everything after gets a time based on the
                //time elapsed since the start of the stream and
                //the time per sample, incremented for each sample
                2 * pi * toFrequency(sg) * ((i / (double) 44100) + streamTime)
                );
    }
}
