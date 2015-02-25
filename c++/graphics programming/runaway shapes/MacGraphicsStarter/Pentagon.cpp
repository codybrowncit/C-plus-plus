//
//  Rectangle.cpp
//  MacGraphicsStarter
//
//  Created by Cody Brown on 11/2/14.
//
//

#include "Pentagon.h"

Pentagon::Pentagon(double x1, double y1, double x2, double y2,double x3, double y3,double x4, double y4,double x5, double y5, double red, double green, double blue, bool solid)
:Shape(red, green, blue, solid)
{
    points.push_back(x1);
    points.push_back(y1);
    points.push_back(x2);
    points.push_back(y2);
    points.push_back(x3);
    points.push_back(y3);
    points.push_back(x4);
    points.push_back(y4);
    points.push_back(x5);
    points.push_back(y5);
    
    Mid=4;
    
}
void Pentagon::draw()
{
    double x1 ,x2, y1, y2, x3, y3, x4, y4, x5, y5;
    x1 = points[0];
    y1 = points[1];
    x2 = points[2];
    y2 = points[3];
    x3 = points[4];
    y3 = points[5];
    x4 = points[6];
    y4 = points[7];
    x5 = points[8];
    y5 = points[9];
    
    //glColor3d(0, 0, 0);
    glColor3d(Mred, Mgreen, Mblue);
    if (mSolid)
    {
        glBegin(GL_POLYGON);
    }
    else
    {
        glBegin(GL_LINE_LOOP);
    }
    glVertex2d(x1,y1);
    glVertex2d(x2,y2);
    glVertex2d(x3,y3);
    glVertex2d(x4,y4);
    glVertex2d(x5,y5);
    
    
    
    /* if (x1<x2 | y1<y2) {
     glVertex2d(x1+5,y1+5);
     glVertex2d(x2-5,y1+5);
     glVertex2d(x2-5,y2-5);
     glVertex2d(x1+5,y2-5);
     }else{
     glVertex2d(x1-5,y1+5);
     glVertex2d(x2+5,y1+5);
     glVertex2d(x2+5,y2-5);
     glVertex2d(x1-5,y2-5);
     }*/
    
    glEnd();
}
