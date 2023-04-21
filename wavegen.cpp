/**
 * A basic proof of concept-- demonstrating usage of Aquila's synthesizer class.  
 *
 *
 *
 */

#include "aquila-src/aquila/aquila.h" // contains all necessary aquila includes
#include "rtaudio-src/RtAudio.h"
#include <cstdio>
#include <iostream>

//copied from https://www.music.mcgill.ca/~gary/rtaudio/playback.html
// Two-channel sawtooth wave generator.
int saw( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *userData )
{
  unsigned int i, j;
  double *buffer = (double *) outputBuffer;
  double *lastValues = (double *) userData;
  if ( status )
    std::cout << "Stream underflow detected!" << std::endl;
  // Write interleaved audio data.
  for ( i=0; i<nBufferFrames; i++ ) {
    for ( j=0; j<2; j++ ) {
      *buffer++ = lastValues[j];
      lastValues[j] += 0.005 * (j+1+(j*0.1));
      if ( lastValues[j] >= 1.0 ) lastValues[j] -= 2.0;
    }
  }
  return 0;
}

// this code largely informed by the Square Wave Generator article in aquila's documentation-- http://aquila-dsp.org/articles/square-wave-generator/
int main(void){
    Aquila::SineGenerator sinegen(1000);
    sinegen.setFrequency(125).setAmplitude(255).generate(64);
    Aquila::TextPlot plot("Sine wave");
    plot.plot(sinegen);

    //double *array = (double *)sinegen.toArray();
    //for (int i = 0; i < 64; i++) printf("%f\n",array[i]);

    //copied from https://www.music.mcgill.ca/~gary/rtaudio/playback.html
  RtAudio dac;
  if ( dac.getDeviceCount() < 1 ) {
    std::cout << "\nNo audio devices found!\n";
    exit( 0 );
  }
  RtAudio::StreamParameters parameters;
  parameters.deviceId = dac.getDefaultOutputDevice();
  parameters.nChannels = 2;
  parameters.firstChannel = 0;
  unsigned int sampleRate = 44100;
  unsigned int bufferFrames = 256; // 256 sample frames
  double data[2] = {0, 0};
  try {
    dac.openStream( &parameters, NULL, RTAUDIO_FLOAT64,
                    sampleRate, &bufferFrames, &saw, (void *)&data );
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
