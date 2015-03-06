//
//  person.cpp
//  MacGraphicsStarter
//
//  Created by Cody Brown on 3/6/15.
//
//

#include "person.h"

void DrawCircle(double x1, double y1, double radius)
{
    glBegin(GL_POLYGON);
    for(int i=0; i<32; i++)
    {
        double theta = (double)i/32.0 * 2.0 * 3.1415926;
        double x = x1 + radius * cos(theta);
        double y = y1 + radius * sin(theta);
        glVertex2d(x, y);
    }
    glEnd();
}

void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3)
{
    glBegin(GL_TRIANGLES);
    glVertex2d(x1,y1);
    glVertex2d(x2,y2);
    glVertex2d(x3,y3);
    glEnd();
}

double Person::get_x(){
    return mX;
}
double Person::get_y(){
    return mY;
}
double Person::get_dx(){
    double radians = mDegrees * M_PI / 180;
    dx = cos(radians);
    return dx;
}
double Person::get_dy(){
    double radians = mDegrees * M_PI / 180;
    dy = sin(radians);
    return dy;
}


Person::Person()
{
    
    mX =mY = .5;
    mDegrees = 0;
    mRadius = .4;
}


void Person::move(double dt, Terrain &terrain)
{
    double radians = mDegrees * M_PI / 180;
    dx = cos(radians) * dt * MOVE_SPEED;
    dy = sin(radians) * dt * MOVE_SPEED;
    if (terrain.isSafe(mX+dx, mY+dy, mRadius))
    {
        mX += dx;
        mY += dy;
    }
    else if (terrain.isSafe(mX, mY+dy, mRadius))
    {
        mY += dy;
    }
    else if (terrain.isSafe(mX+dx, mY, mRadius))
    {
        mX += dx;
    }
    
}

void Person::turnLeft(double dt)
{
    mDegrees += TURN_SPEED * dt * 360;
}

void Person::turnRight(double dt)
{
    mDegrees -= TURN_SPEED * dt * 360;
}


