#include "grid_block.h"

GridBlock::GridBlock(float _x, float _y, float _w, float _h, float _mx, float _my, ofColor _bg, ofColor _fg)
{
    x = _x; y = _y; w = _w; h = _h; mx = _mx; my = _my;
    bg = _bg; fg = _fg;
    animatorW.setup(mx, true); animatorH.setup(my, true);
    animatorFill.setup(bg.r, false);
}

void GridBlock::update(){
    MX = animatorW.getNextValue();
    MY = animatorH.getNextValue();
    MR = animatorFill.getNextValue();
}

void GridBlock::draw(){
    if (hasFill || animatorFill.running){
        ofFill();
        ofSetColor( ofColor(MR) );
        drawMarginRect();
    }
    ofNoFill();
    ofSetColor(fg);
    drawMarginRect();
}

void GridBlock::drawMarginRect(){
    ofDrawRectangle(x + w*MX,y + h*MY,w-2*w*MX,h-2*h*MY);
}

void GridBlock::trigger(float dur){
    animatorW.startAnimation(mx, 0.0, dur);
    animatorW.looping = true;
    animatorH.startAnimation(my, 0.0, dur);
    animatorH.looping = true;
}

void GridBlock::fillBlock(bool on){
    if (on){
        animatorFill.startAnimation(0.0, 255.0, 10.0);
        hasFill = true;
    } else {
        animatorFill.startAnimation(255.0,0.0, 10.0);
    }

}
