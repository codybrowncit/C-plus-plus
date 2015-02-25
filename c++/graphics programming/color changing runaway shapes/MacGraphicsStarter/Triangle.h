//
//  Triangle.h
//  MacGraphicsStarter
//
//  Created by Cody Brown on 11/2/14.
//
//

#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_
#include "Shape.h"
#include <stdio.h>
#ifdef _WIN32
#include "glut.h"
#else
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#endif
class Triangle : public Shape
{
public:
    Triangle(double x1, double y1, double x2, double y2, double x3, double y3, double red, double green, double blue, bool solid);
    void draw();
};

#endif /* defined(__MacGraphicsStarter__Triangle__) */
