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
const double WATER_HEIGHT = 0.5;


class Terrain
{
public:
    Terrain();
    void draw(double waterLevel, double slope);
    enum viewtype{top_view, perspective_view, eye_view};
    viewtype current_view = eye_view;
    bool isSafe(double x, double y, double radius);
    double get_z(double x, double y, double slope);
    class Cell
    {
    public:
        Cell();
        bool getLeft();
        bool getRight();
        bool getTop();
        bool getBottom();
        bool mBottom, mTop, mLeft, mRight;
        void draw(int x, int y);
        double mWaterLevel;

    };
    Cell mCell[COL][ROW];
    double z[COL][ROW];
    
    
};

#include <stdio.h>

#endif /* defined(__MacGraphicsStarter__terrain__) */

