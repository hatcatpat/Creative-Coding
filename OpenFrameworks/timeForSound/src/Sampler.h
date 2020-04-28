#ifndef SAMPLER_H
#define SAMPLER_H

#include "ofMain.h"
#include "AudioFile.h"

class Sampler {
public:

    Sampler(){};

    void setup(string fileName="kick"){
        name = fileName;
        audioFile.load ("../bin/data/"+fileName+".wav");
        audioFile.printSummary();
        sampleRate = audioFile.getSampleRate();
        numSamples = audioFile.getNumSamplesPerChannel();
        numChannels = audioFile.getNumChannels();
        end = numSamples;
    };

    void process(ofSoundBuffer &output){

        if (active){
            for (int i = 0; i < output.size(); i += 2)
            {
                output[i] += audioFile.samples[0][index] * volume * (1-pan);
                output[i+1] += audioFile.samples[ numChannels > 1 ? 1 : 0 ][index] * volume * (pan);

                if (index > end){
                    index = start;
                    if (!looping)
                        active = false;
                } else {
                    index++;
                }

            }
        }

    };

    void trigger(bool interrupt=false){
        if (interrupt){
            active = true;
            index = start;
        } else {
            active = true;
        }
    }

    void setEnd(float new_end){
        int end_sample = (int) (numSamples-1)*new_end;
        end = end_sample <= numSamples-1 ? end_sample : numSamples-1;
    }

    void setLooping(bool value){
        looping = value;
    }

    void setStart(float new_start){
        int start_sample = (int) end*new_start;
        start = start_sample >= 0 ? start_sample : 0;
    }

    void setVolume(float new_volume){ volume = abs(new_volume); }

    void setPan(float new_pan){ pan = new_pan; }

    void draw_graph(float x, float y, float width, float height){

        ofSetColor(255);

        ofPolyline p;

        for (int samp = 0; samp < numSamples; ++samp) {
            ofVec3f vec( x+samp*(width/numSamples), y+audioFile.samples[0][samp]*height/2,0.0);
            p.addVertex(vec);
        }
        p.draw();
    }

    void draw_info(float x, float y, float width, float height){
        float xUnit = width/5;

        ofSetColor(0);
        ofFill();
        for (int i = 0; i < 5; ++i)
            ofDrawRectangle(x+xUnit*i, y-16, xUnit, 16);

        ofNoFill();
        ofSetColor(255);
        ofDrawBitmapString(name, x,y);
        ofDrawBitmapString(start, x+xUnit,y);
        ofDrawBitmapString(end, x+xUnit*2,y);
        ofDrawBitmapString(pan, x+xUnit*3,y);
        ofDrawBitmapString(volume, x+xUnit*4,y);
    }

private:
    AudioFile<float> audioFile;

    int sampleRate = 44100;
    int numSamples = 0;
    int numChannels = 0;

    float volume = 0.4;
    float pan = 0.5;

    string name = "";

    int start = 0;

    int end = 44100*8;

    int index = start;

    bool active = false;
    bool looping = false;
};

#endif // SAMPLER_H
