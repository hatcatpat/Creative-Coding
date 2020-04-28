#ifndef GRIDBLOCK_H
#define GRIDBLOCK_H

#include "ofMain.h"
#include "animator.h"

class GridBlock
{
public:
    GridBlock(float _x, float _y, float _w, float _h, float _mx, float _my, ofColor _bg, ofColor _fg);

    void update();
    void draw();
    void drawMarginRect();
    void trigger(float dur = 10.0);
    void fillBlock(bool on);

private:
    float x, y, w, h, mx, my;
    ofColor bg, fg;
    Animator animatorW;
    Animator animatorH;
    Animator animatorFill;
    bool hasFill = false;

    float MX, MY, MR;
};

#endif // GRIDBLOCK_H
