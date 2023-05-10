#include <cmath>

#include "samplegenerator.hpp"

int SampleGenerator::toFrequency(int semitones)
{
    return round(440 * pow(2, semitones / (double)12));
}

int SampleGenerator::getAmplitude()
{
    return amplitude;
}

int SampleGenerator::getFrequency()
{
    return frequency;
}

void SampleGenerator::set(int a, int f)
{
    amplitude = a;
    frequency = f;
}

void SampleGenerator::getSamples(double *samples)
{
    // Generate waveform

    // Get samples
}
