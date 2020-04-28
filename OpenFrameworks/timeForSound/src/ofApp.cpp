#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    shader.load("noise");

    buf.clear();

    oscReceiver.setup(12000);

    for (int i = 0; i < numOfSamplers; ++i){
        samplers[i].setup(wavFiles[i]);
        samplers[i].setLooping(false);
    }

    soundSettings.setApi( ofSoundDevice::PULSE );
    soundSettings.setOutListener(ofGetAppPtr());
    soundSettings.numOutputChannels = 2;
    soundSettings.numInputChannels = 0;
    ofSoundStreamSetup(soundSettings);

    bufferSize = soundSettings.bufferSize;
    sampleRate = soundSettings.sampleRate;

    dur_sec_to_samp();

    ofSetBackgroundColor(0);

    ofSetFrameRate(60);
}

void ofApp::dur_sec_to_samp(){ dur_samples = dur_seconds * sampleRate / bufferSize; }

void ofApp::audioOut(ofSoundBuffer &outBuffer) {

    if (t == 0){
        std::vector<ofxOscMessage> fixed_message_seq = message_seq[T];

        for (ofxOscMessage msg : fixed_message_seq)
            processOsc(msg);

        message_seq[T].clear();
        T++;
        T %= mod;
    }

    t++;
    t %= dur_samples;


    for (int i = 0; i < numOfSamplers; ++i)
        samplers[i].process(outBuffer);

    buf.swap(outBuffer.getBuffer());

}

void ofApp::processOsc(ofxOscMessage msg){

   string address = msg.getAddress();

   if (msg.getNumArgs() > 0){
       if (address == "/trig"){
           samp = msg.getArgAsInt(1);
           samplers[samp].trigger(true);
       }
       else if (address == "/rel"){
           int synth = msg.getArgAsInt(1);
           if (0 <= synth && synth < numOfSamplers)
               samplers[synth].setEnd(msg.getArgAsFloat(2));
       }
       else if (address == "/atk"){
           int synth = msg.getArgAsInt(1);
           if (0 <= synth && synth < numOfSamplers)
               samplers[synth].setStart(msg.getArgAsFloat(2));
       }
       else if (address == "/sus"){
           int synth = msg.getArgAsInt(1);
           if (0 <= synth && synth < numOfSamplers)
               samplers[synth].setVolume(msg.getArgAsFloat(2));
       }
       else if (address == "/pan"){
           int synth = msg.getArgAsInt(1);
           if (0 <= synth && synth < numOfSamplers)
               samplers[synth].setPan(msg.getArgAsFloat(2));
       }

       else if (address == "/blue_mode"){
           blue_mode = msg.getArgAsInt(1);
       }
   }

}

//--------------------------------------------------------------
void ofApp::update(){

    while (oscReceiver.hasWaitingMessages()){
        ofxOscMessage msg;
        oscReceiver.getNextMessage(msg);

        if (msg.getNumArgs() > 0){
            string address = msg.getAddress();

            if (address == "/speed"){
                dur_seconds = msg.getArgAsFloat(0);
                dur_sec_to_samp();
            }
            else {
                int timeTag = msg.getArgAsInt(0)%mod;
                if (timeTag < T+mod)
                    message_seq[timeTag].push_back(msg);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    if (T == 0)
        for (int i = 0; i < 4; i++)
            randoms[i] = ofRandom(0,1);

    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofScale( 0.5, 0.5, 1.f );
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);

    shader.begin();
    shader.setUniform1i("width", ofGetWidth() );
    shader.setUniform1i("height", ofGetHeight() );
    shader.setUniform1f("T", t);
    shader.setUniform1i("blue_mode", blue_mode);
    shader.setUniform4f("random", randoms[0], randoms[1], randoms[2], randoms[3]);

    for (int i = 0; i < numOfSamplers; ++i)
        samplers[i].draw_graph(32, 32+i*(ofGetHeight()-32)/numOfSamplers ,ofGetWidth()-32, (ofGetHeight()-32)/numOfSamplers );

    if (T%3 == 0)
        for (int i = 0; i < numOfSamplers; ++i)
            samplers[i].draw_info(32, 32+i*(ofGetHeight()-32)/numOfSamplers ,ofGetWidth()-32, (ofGetHeight()-32)/numOfSamplers );

    shader.end();

    if (T%3 != 0)
        for (int i = 0; i < numOfSamplers; ++i)
            samplers[i].draw_info(32, 32+i*(ofGetHeight()-32)/numOfSamplers ,ofGetWidth()-32, (ofGetHeight()-32)/numOfSamplers );

    ofPolyline p;
    std::vector<float> fixed_buf = buf;
    float xUnit = ofGetWidth()/min( (int)fixed_buf.size(),1);
    for (int i = 0; i < fixed_buf.size(); ++i) {
        p.addVertex( ofVec3f(i*xUnit, 8*fixed_buf[i]*ofGetHeight()/2+ofGetHeight()/2, 0) );
    }
    p.draw();

    ofPopMatrix();


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == 'a')
        samplers[0].trigger(true);

    if (key == 's')
        samplers[1].trigger(true);
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
