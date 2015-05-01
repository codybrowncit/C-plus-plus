//
//  Spiral.cpp
//  MacGraphicsStarter
//
//  Created by Cody Brown on 11/2/14.
//
//

#include "Spiral.h"
#include <cmath> 

Spiral::Spiral(double x1, double y1, double x2, double y2, double red, double green, double blue, bool solid)
:Shape(red, green, blue, solid)
{
    points.push_back(x1);
    points.push_back(y1);
    points.push_back(x2);
    points.push_back(y2);
    Mid=1;

    
    
    
}

void Spiral::draw()
{
    double  x2,  y2;
    x1 = points[0];
    y1 = points[1];
    x2 = points[2];
    y2 = points[3];
    radius = sqrt(pow((x2-x1),2)+pow((y2-y1),2));
    glColor3d(Mred, Mgreen, Mblue);
    glBegin(GL_LINE_STRIP);
    for(int i=0; i<300; i++)
    {
        double theta = (double)i/32.0 * 2.0 * 3.1415926;
        double x = x1 + radius * cos(theta);
        double y = y1 + radius * sin(theta);
        glVertex2d(x, y);
        radius += 1;
    }
    glEnd();
}

double Spiral::getx()
{
    return x1;
}
double Spiral::gety()
{
    return y1;
}
double Spiral::getradius()
{
    return radius;
}
double Spiral::getr()
{
    return Mred;
}
double Spiral::getg()
{
    return Mgreen;
}
double Spiral::getb()
{
    return Mblue;
}
double Spiral::getdx()
{
    return xDir;
}
double Spiral::getdy()
{
    return yDir;
}
double Spiral::getnextx()
{
    
    return x1 + xDir;
}
double Spiral::getnexty()
{
    return y1 + yDir;
}
void Spiral::setdx(double dx)
{
    xDir = dx;
}
void Spiral::setdy(double dy)
{
    yDir = dy;
}
bool Spiral::getsolid()
{
    return mSolid;
}



