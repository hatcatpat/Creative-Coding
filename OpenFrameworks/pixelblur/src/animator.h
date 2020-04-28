#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "ofMain.h"

class Animator{
public:

    Animator();

    float getNextValue();

    void setup(float defaultValue, bool looping);
    void startAnimation(float start, float end, float dur);

    bool looping = false;
    bool running = false;

private:

    void incrementCounter();
    float startValue, endValue, value, step, dur, counter;
};

#endif // ANIMATOR_H
