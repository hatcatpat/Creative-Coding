#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

    int windowWidth = 800;
    int windowHeight = 800;

    #ifdef TARGET_OPENGLES
    ofGLESWindowSettings settings;
    settings.width = windowWidth;
    settings.height = windowHeight;
    settings.setGLESVersion(2);
    ofCreateWindow(settings);
    #else
    ofSetupOpenGL(windowWidth, windowHeight, OF_WINDOW);
    #endif

    ofRunApp(new ofApp());
}
