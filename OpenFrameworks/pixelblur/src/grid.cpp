#include "grid.h"

Grid::Grid()
{

}

void Grid::setup(int _densityX, int _densityY, float _w, float _h, float _mx, float _my, ofColor _bg, ofColor _fg){
    w = _w; h = _h, mx = _mx; my = _my;
    bg = _bg; fg = _fg;
    setDensity(_densityX, _densityY);
}

void Grid::setDensity(int dx, int dy){
    densityX = dx;
    densityY = dy;

    grid.clear();

    float wUnit = (float) w/densityX;
    float hUnit = (float) h/densityY;

    for (int i = 0; i < densityX; ++i) {
        for(int j = 0; j < densityY; ++j){
            float x = i*wUnit, y = j*hUnit;
            grid.push_back( GridBlock(x,y,wUnit,hUnit,mx,my,bg,fg) );
        }
    }
}

void Grid::draw(){
    for (auto i = 0; i < grid.size(); i++){
        grid.at(i).draw();
    }
}

void Grid::update(){
    for (auto i = 0; i < grid.size(); i++){
        grid.at(i).update();
    }
}

void Grid::trigger(int x, int y, float dur){
    if (0 <= x && x < densityX)
        if (0 <= y && y < densityY)
            grid.at(x+y*densityX).trigger(dur);
}

void Grid::fillBlock(int x, int y, bool on){
    if (0 <= x && x < densityX)
        if (0 <= y && y < densityY)
            grid.at(x+y*densityX).fillBlock(on);
}
