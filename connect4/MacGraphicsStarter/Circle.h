//
//  Circle.h
//  MacGraphicsStarter
//
//  Created by Cody Brown on 11/2/14.
//
//
#ifndef _CIRCLE_H_
#define _CIRCLE_H_
#include "Shape.h"
#include <stdio.h>

class Circle : public Shape
{
public:
    Circle(double x1, double y1, double x2, double y2, double red, double green, double blue);
    void draw();
};

#endif /* defined(__MacGraphicsStarter__Circle__) */
