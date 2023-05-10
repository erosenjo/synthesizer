#include "rtaudio-src/RtAudio.h"

#include "samplegenerator.hpp"
#include "tui.hpp"

int sine(void *output_buffer, void *input_buffer, unsigned int n_frames,
                       double stream_time, RtAudioStreamStatus status, void *user_data)
{
    double *buffer = (double *)output_buffer;
}

int main()
{
    SampleGenerator sg;
    TUI tui;
    tui.update();

    RtAudio dac;
    if (dac.getDeviceCount() < 1)
    {
        std::cout << "No audio devices found." << std::endl;
        return 1;
    }
    RtAudio::StreamParameters params;
    params.deviceId = dac.getDefaultOutputDevice();
    params.nChannels = 1;
    params.firstChannel = 0;
    unsigned int sample_rate = 44100;
    unsigned int buffer_frames = 256;
    try
    {
        dac.openStream(&params, NULL, RTAUDIO_FLOAT64, sample_rate, &buffer_frames, &sine, (void *)&sg);
        dac.startStream();
    }
    catch (RtAudioError e)
    {
        e.printMessage();
        return 1;
    }

    return 0;
}
