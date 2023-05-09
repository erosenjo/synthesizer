#include "aquila-src/aquila/aquila.h"

#include "samplegenerator.hpp"

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
    Aquila::SineGenerator sinegen(1000);
    sinegen.setFrequency(frequency)
        .setAmplitude(amplitude)
        .generate(N_SAMPLES);

    // Get samples
    const Aquila::SampleType *samplesgen = sinegen.toArray();
    for (int s = 0; s < N_SAMPLES; s++)
    {
        samples[s] = samplesgen[s];
    }
}
