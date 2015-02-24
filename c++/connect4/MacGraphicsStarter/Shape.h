//
//  Shape.h
//  MacGraphicsStarter
//
//  Created by Cody Brown on 10/27/14.
//
//

#ifndef _SHAPE_H_
#define _SHAPE_H_
#include <vector>
#ifdef _WIN32
#include "glut.h"
#else
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#endif
#include <stdio.h>

class Shape
{
public:
    Shape(double red, double green, double blue);
    virtual void draw() = 0;
    std::vector<double> points;
    double Mred;
    double Mblue;
    double Mgreen;
    int Mid;
    
};

#endif /* defined(__MacGraphicsStarter__Shape__) */
