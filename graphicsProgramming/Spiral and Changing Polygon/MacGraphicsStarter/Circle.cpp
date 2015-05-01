//
//  Circle.cpp
//  MacGraphicsStarter
//
//  Created by Cody Brown on 11/2/14.
//
//

#include "Circle.h"
#include <cmath> 

Circle::Circle(double x1, double y1, double x2, double y2, double red, double green, double blue, bool solid, double sides)
:Shape(red, green, blue, solid)
{
    points.push_back(x1);
    points.push_back(y1);
    points.push_back(x2);
    points.push_back(y2);
    Mid=1;
    Msides = sides;
    
    
    
}

void Circle::draw()
{
    double  x2,  y2;
    x1 = points[0];
    y1 = points[1];
    x2 = points[2];
    y2 = points[3];
    radius = sqrt(pow((x2-x1),2)+pow((y2-y1),2));
    glColor3d(Mred, Mgreen, Mblue);
    glBegin(GL_POLYGON);
    for(int i=0; i<32; i++)
    {
        double theta = (double)i/Msides * 2.0 * 3.1415926;
        double x = x1 + radius * cos(theta);
        double y = y1 + radius * sin(theta);
        glVertex2d(x, y);
    }
    glEnd();
}

double Circle::getx()
{
    return x1;
}
double Circle::gety()
{
    return y1;
}
double Circle::getradius()
{
    return radius;
}
double Circle::getr()
{
    return Mred;
}
double Circle::getg()
{
    return Mgreen;
}
double Circle::getb()
{
    return Mblue;
}
double Circle::getdx()
{
    return xDir;
}
double Circle::getdy()
{
    return yDir;
}
double Circle::getnextx()
{
    
    return x1 + xDir;
}
double Circle::getnexty()
{
    return y1 + yDir;
}
void Circle::setdx(double dx)
{
    xDir = dx;
}
void Circle::setdy(double dy)
{
    yDir = dy;
}
bool Circle::getsolid()
{
    return mSolid;
}



