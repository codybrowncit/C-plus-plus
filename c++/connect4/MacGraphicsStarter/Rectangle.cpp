//
//  Rectangle.cpp
//  MacGraphicsStarter
//
//  Created by Cody Brown on 11/2/14.
//
//

#include "Rectangle.h"

Rectangle::Rectangle(double x1, double y1, double x2, double y2, double red, double green, double blue)
:Shape(red, green, blue)
{
    points.push_back(x1);
    points.push_back(y1);
    points.push_back(x2);
    points.push_back(y2);
    Mred = red;
    Mgreen = green;
    Mblue = blue;
    Mid=2;
    
}
void Rectangle::draw()
{
    double x1 ,x2, y1, y2;
    x1 = points[0];
    y1 = points[1];
    x2 = points[2];
    y2 = points[3];

    glColor3d(Mred, Mgreen, Mblue);
    glBegin(GL_QUADS);
    glVertex2d(x1,y1);
    glVertex2d(x2,y1);
    glVertex2d(x2,y2);
    glVertex2d(x1,y2);
    glEnd();
}
