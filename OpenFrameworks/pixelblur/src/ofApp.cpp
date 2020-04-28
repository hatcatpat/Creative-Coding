#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    oscReceiver.setup(12000);

    ofBackground(bg);
    grid.setup(8,16, ofGetWidth(), ofGetHeight(), 0.1, 0.2, bg, fg );
    shader.load("shader");

    for (int i=0; i < 2; i++)
        squishAnims[i].setup(squish[i], false);

    screengrab.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
}

//--------------------------------------------------------------
void ofApp::update(){
    grid.update();

//    if (t%echo == 0){
//        screengrab.clear();
//        screengrab.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
//    }

    while (oscReceiver.hasWaitingMessages()){
        ofxOscMessage msg;
        oscReceiver.getNextMessage(msg);
        string address = msg.getAddress();

        if (address == "/lines"){
            for (int i=0; i < 4; i++)
                randomNumbers[i] = ofRandom(-1,1);
        }

        if (address == "/trig")
            grid.trigger( (int) ofRandom(0,8), (int) ofRandom(0,16), ofRandom(10,60*4) );

        if (address == "/fill")
            grid.fillBlock( (int) ofRandom(0,8), (int) ofRandom(0,16), (bool)(int)ofRandom(0,2) );

        if (address == "/squish/x")
            squishAnims[0].startAnimation(squish[0], ofRandom(0.4,1), ofRandom(1,10) );

        if (address == "/squish/y")
            squishAnims[1].startAnimation(squish[1], ofRandom(0.4,1), ofRandom(1,10) );

        if (address == "/echo"){
//            echo = (int) floor(msg.getArgAsFloat(0));
            screengrab.clear();
            screengrab.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
        }

    }

    for (int i=0; i < 2; i++)
        squish[i] = squishAnims[i].getNextValue();

}

//--------------------------------------------------------------
void ofApp::draw(){

//    ofSetColor(0.0);
//    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());

    screengrab.draw(0,0);

    shader.begin();
    shader.setUniform1i("t", t);
    shader.setUniform1f("mul", mul );
    shader.setUniform1f("width", ofGetWidth()*mul );
    shader.setUniform1f("height", ofGetHeight()*mul );
    shader.setUniform2f("squish", squish[0], squish[1]);
    shader.setUniform4f("randNum", randomNumbers[0], randomNumbers[1],
                                   randomNumbers[2], randomNumbers[3]
                       );
    grid.draw();

    shader.end();

    screengrab.loadScreenData(0,0,ofGetWidth(),ofGetHeight());

    t++;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    screengrab.clear();
    screengrab.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
