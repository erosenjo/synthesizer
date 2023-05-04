#include "aquila-src/aquila/aquila.h"

#include "samplegenerator.hpp"

void SampleGenerator::set(int a, int f)
{
    amplitude = a;
    frequency = f;
}

void SampleGenerator::getScaledSamples(int *scaled_samples)
{
    // Generate waveform
    Aquila::SineGenerator sinegen(44100);
    sinegen.setFrequency(frequency)
        .setAmplitude(amplitude)
        .generate(N_SAMPLES);

    const Aquila::SampleType *samples = sinegen.toArray();

    for (int s = 0; s < N_SAMPLES; s++)
    {
        scaled_samples[s] = (int) round(samples[s] * WINDOW_HEIGHT);
    }
}
