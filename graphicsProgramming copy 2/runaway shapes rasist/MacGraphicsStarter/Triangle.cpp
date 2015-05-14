//
//  Triangle.cpp
//  MacGraphicsStarter
//
//  Created by Cody Brown on 11/2/14.
//
//

#include "Triangle.h"

Triangle::Triangle(double x1, double y1, double x2, double y2, double x3, double y3, double red, double green, double blue, bool solid)
:Shape(red, green, blue, solid)
{
    points.push_back(x1);
    points.push_back(y1);
    points.push_back(x2);
    points.push_back(y2);
    points.push_back(x3);
    points.push_back(y3);
    Mid=3;


   
}

void Triangle::draw()
{
    double x1, x2, x3, y1, y2, y3, red, green, blue;
    x1 = points[0];
    y1 = points[1];
    x2 = points[2];
    y2 = points[3];
    x3 = points[4];
    y3 = points[5];
    
    glColor3d(Mred, Mgreen, Mblue);
    if (mSolid)
    {
        glBegin(GL_TRIANGLES);
    }
    else
    {
        glBegin(GL_LINE_LOOP);
    }
    
    glVertex2d(x1,y1);
    glVertex2d(x2,y2);
    glVertex2d(x3,y3);
    glEnd();
}

