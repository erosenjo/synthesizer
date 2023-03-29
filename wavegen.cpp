/**
 * A basic proof of concept-- demonstrating usage of Aquila's synthesizer class.  
 *
 *
 *
 */

#include "synthesizer.h"
#include <iostream>

// this code largely informed by the Square Wave Generator article in aquila's documentation-- http://aquila-dsp.org/articles/square-wave-generator/
int main(void){
    Aquila::SineGenerator sinegen(1000);
    sinegen.setFrequency(125).setAmplitude(255).generate(64);
    Aquila::TextPlot plot("Sine wave");
    plot.plot(sinegen);

    return 0;
}
