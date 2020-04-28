#include "animator.h"

Animator::Animator(){}

void Animator::setup(float _defaultValue, bool _looping){
    value = _defaultValue;
    looping = _looping;
}

void Animator::startAnimation(float newStartValue, float newEndValue, float newDur){
    if (!running){
        startValue = newStartValue; endValue = newEndValue; dur = newDur;

        step = 1.0/dur;
        counter = 0.0;
        running = true;
    }
}

void Animator::incrementCounter(){
    counter += step;
}

float Animator::getNextValue(){
    if (running){
        if ( abs(counter+step) < 1){
            value = ofLerp(startValue, endValue, counter);
            incrementCounter();
        } else {
            if (looping){
                step = -step;
//                counter = 0;
                looping = false;
            } else{
                running = false;
            }
        }
    }
    return value;
}
