#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#include "Sampler.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    void processOsc(ofxOscMessage msg);

    void dur_sec_to_samp();

    void audioOut(ofSoundBuffer &outBuffer);

    ofShader shader;

    ofSoundStreamSettings soundSettings;
    ofSoundStream soundStream;
    ofSoundDevice soundDevice;

    ofxOscReceiver oscReceiver;

    const static int numOfSamplers = 8;
    Sampler samplers[numOfSamplers];

    string wavFiles[numOfSamplers] = {"kick2","crunch","vox","snare2", "clap", "zap", "snare","keys"};

    int t = 0;
    int T = 0;
    float dur_seconds = 0.25;
    int dur_samples = 4;

    bool first_run = true;

    const static int START_MOD = 16;
    int mod = START_MOD;
    std::vector<ofxOscMessage> message_seq[START_MOD*8];

    int sampleRate = 44100;
    int bufferSize = 512;

    int samp = 0;
    float counter = 0.0;

    float randoms[4] = {1.0};

    int current_synth = 0;

    std::vector<float> buf;

    bool fontInside = false;

    int blue_mode = 0;

};
