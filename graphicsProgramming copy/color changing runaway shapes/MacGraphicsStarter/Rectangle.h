//
//  Rectangle.h
//  MacGraphicsStarter
//
//  Created by Cody Brown on 11/2/14.
//
//

#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_
#include "Shape.h"
#include <stdio.h>

class Rectangle : public Shape
{
public:
    Rectangle(double x1, double y1, double x2, double y2, double red, double green, double blue, bool solid);
    void draw();
};

#endif /* defined(__MacGraphicsStarter__Rectangle__) */
