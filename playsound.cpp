/**
 *
 *
 *
 */

#include "rtaudio-src/RtAudio.h"
#include <cstdio>
#include <iostream>
#include <cmath>

int sine(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *userData )
{
    static double pi = 3.14159;
    double *buffer = (double *) outputBuffer;
    double *freq = (double *) userData;

    if ( status ) 
        std::cout << "Stream underflow detected!" << std::endl;
 
    // write non-interleaved audio data using aquila
    for (unsigned int i = 0; i <= nBufferFrames; i++){
        *buffer++ = sin(
                //equation for the sin wave.
                //everything until "freq" converts a time to radians
                //everything after gets a time based on the
                //time elapsed since the start of the stream and
                //the time per sample, incremented for each sample
                2 * pi * *freq * ((i / (double) 44100) + streamTime)
                );
        if (i == 0 || i == nBufferFrames) printf("ends: %f\n",buffer[-1]);
    }
    return 0;
}

int main(void){

    //copied from https://www.music.mcgill.ca/~gary/rtaudio/playback.html
  RtAudio dac;
  if ( dac.getDeviceCount() < 1 ) {
    std::cout << "\nNo audio devices found!\n";
    exit( 0 );
  }
  RtAudio::StreamParameters parameters;
  parameters.deviceId = dac.getDefaultOutputDevice();
  parameters.nChannels = 1;
  parameters.firstChannel = 0;
  unsigned int sampleRate = 44100;
  unsigned int bufferFrames = 256; // 256 sample frames
  double freq = 440;
  try {
    dac.openStream( &parameters, NULL, RTAUDIO_FLOAT64,
                    sampleRate, &bufferFrames, &sine, (void *)&freq );
    dac.startStream();
  }
  catch ( RtAudioError& e ) {
    e.printMessage();
    exit( 0 );
  }
  
  char input;
  std::cout << "\nPlaying ... press <enter> to quit.\n";
  std::cin.get( input );
  try {
    // Stop the stream
    dac.stopStream();
  }
  catch (RtAudioError& e) {
    e.printMessage();
  }
  if ( dac.isStreamOpen() ) dac.closeStream();
  //end copied segment

    return 0;
}
