//
//  Circle.cpp
//  MacGraphicsStarter
//
//  Created by Cody Brown on 11/2/14.
//
//

#include "Circle.h"
#include <cmath> 

Circle::Circle(double x1, double y1, double x2, double y2, double red, double green, double blue, bool solid)
:Shape(red, green, blue, solid)
{
    points.push_back(x1);
    points.push_back(y1);
    points.push_back(x2);
    points.push_back(y2);
    Mid=1;
}

void Circle::draw()
{
    double x1, x2, y1, y2, radius;
    x1 = points[0];
    y1 = points[1];
    x2 = points[2];
    y2 = points[3];
    radius = sqrt(pow((x2-x1),2)+pow((y2-y1),2));

    glColor3d(Mred, Mgreen, Mblue);
    if (mSolid)
    {
        glBegin(GL_POLYGON);
    }
    else
    {
        glBegin(GL_LINE_LOOP);
    }
    
    for(int i=0; i<32; i++)
    {
        double theta = (double)i/32.0 * 2.0 * 3.1415926;
        double x = x1 + radius * cos(theta);
        double y = y1 + radius * sin(theta);
        glVertex2d(x, y);
    }
    glEnd();
}


