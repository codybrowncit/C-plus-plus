//
//  Spiral.h
//  MacGraphicsStarter
//
//  Created by Cody Brown on 11/2/14.
//
//
#ifndef _SPIRAL_H_
#define _SPIRAL_H_
#include "Shape.h"
#include <stdio.h>

class Spiral : public Shape
{
public:
    Spiral(double x1, double y1, double x2, double y2, double red, double green, double blue, bool solid);
    void draw();
    double getx();
    double gety();
    double getradius();
    double getr();
    double getg();
    double getb();
    double getdx();
    double getdy();
    double getnextx();
    double getnexty();
    bool getsolid();
    void setdx(double dx);
    void setdy(double dy);
private:
    double x1,y1,radius;
    double xDir, yDir;
    double r,g,b, Msides;
};


#endif /* defined(__MacGraphicsStarter__Spiral__) */
