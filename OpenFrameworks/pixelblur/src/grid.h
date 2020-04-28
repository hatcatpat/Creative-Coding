#ifndef GRID_H
#define GRID_H

#include "ofMain.h"
#include "grid_block.h"

class Grid
{
public:
    Grid();

    void setup(int _densityX, int _densityY, float _w, float _h, float _mx, float _my, ofColor _bg, ofColor _fg);
    void setDensity(int dx, int dy);
    void update();
    void draw();
    void trigger(int x, int y, float dur = 10.0);
    void fillBlock(int x, int y, bool on);

    int densityX;
    int densityY;
private:
    float w, h, mx, my;
    std::vector<GridBlock> grid;
    ofColor bg;
    ofColor fg;
};

#endif // GRID_H
