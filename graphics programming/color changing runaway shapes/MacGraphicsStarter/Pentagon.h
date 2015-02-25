//
//  Rectangle.h
//  MacGraphicsStarter
//
//  Created by Cody Brown on 11/2/14.
//
//

#ifndef _PENTAGON_H_
#define _PENTAGON_H_
#include "Shape.h"
#include <stdio.h>

class Pentagon : public Shape
{
public:
    Pentagon(double x1, double y1, double x2, double y2, double x3, double y3,double x4, double y4,double x5, double y5,double red, double green, double blue, bool solid);
    void draw();
};

#endif /* defined(__MacGraphicsStarter__Rectangle__) */
