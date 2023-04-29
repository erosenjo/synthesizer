#include <iostream> // For debugging; delete eventually

#include "aquila-src/aquila/aquila.h"

class SampleGenerator
{
private:
    int amplitude;
    int frequency;

    static double toFreq(int semitones)
    {
        return 440 * pow(2, semitones / (double)12);
    }

public:
    SampleGenerator()
    {
    }
    void set(int amplitude, int frequency)
    {
        std::cout << "hello";
    }
};

int main()
{
    SampleGenerator s;
    s.set(1, 1);

    return 0;
}
