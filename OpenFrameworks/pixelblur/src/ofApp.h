#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#include "grid.h"

#include "animator.h"

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

    ofShader shader;

    ofTexture screengrab;

    ofxOscReceiver oscReceiver;
    int oscValue;

    int t = 0;
    int res = 16;
    int echo = 60;

    Grid grid;

    ofColor bg = ofColor(0);
    ofColor fg = ofColor(255);

    float randomNumbers[4] = {0.0,0.0,0.0,0.0};

    float mul = 0.8;

    float squish[2] = {1.0,1.0};
    Animator squishAnims[2];
};
