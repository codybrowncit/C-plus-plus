//
//  terrain.h
//  MacGraphicsStarter
//
//  Created by Cody Brown on 3/6/15.
//
//

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>
#include <GLUT/glut.h>
#include <vector>

#ifndef __TERRAIN_H_
#define __TERRAIN_H_

const int COL = 100;
const int ROW = 100;

class Terrain
{
public:
    Terrain();
    void draw();
    enum viewtype{top_view, perspective_view, eye_view};
    viewtype current_view = eye_view;
    bool isSafe(double x, double y, double radius);
    class Cell
    {
    public:
        Cell();
        bool getLeft();
        bool getRight();
        bool getTop();
        bool getBottom();
        bool mBottom, mTop, mLeft, mRight;
        void draw(int x, int y, char type);
    };
    Cell mCell[COL][ROW];
    
};

#include <stdio.h>

#endif /* defined(__MacGraphicsStarter__terrain__) */

