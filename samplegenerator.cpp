#include <cmath>

#include "samplegenerator.hpp"

int SampleGenerator::toHz()
{
    return round(440 * pow(2, semitones / (double)12));
}

void SampleGenerator::set(int a, int s)
{
    amplitude = a;
    semitones = s;
}

void SampleGenerator::getSamples(double *buffer, int n_frames, double stream_time)
{
    for (int frame_i = 0; frame_i < n_frames; frame_i++)
    {
        /* equation for the sin wave.
        everything until "freq" converts a time to radians;
        everything after gets a time based on the time elapsed since the start of the
        stream and the time per sample, incremented for each sample */
        *buffer++ = (amplitude / (double)255) *
                    sin(2 * PI * semitones * ((frame_i / (double)44100) + stream_time));
    }
}
