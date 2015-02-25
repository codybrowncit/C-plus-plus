//
//  rat.cpp
//  MacGraphicsStarter
//
//  Created by Cody Brown on 2/11/15.
//
//

#include "rat.h"

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
void DrawRectangle(double x1, double y1, double x2, double y2)
{
    glBegin(GL_QUADS);
    glVertex2d(x1,y1);
    glVertex2d(x2,y1);
    glVertex2d(x2,y2);
    glVertex2d(x1,y2);
    glEnd();
}
double Rat::get_x(){
    return mX;
}
double Rat::get_y(){
    return mY;
}


Rat::Rat()
{

    mX =mY = .5;
    mDegrees = 0;
    mRadius = .4;
}
void Rat::draw()
{
    glPushMatrix();
    
    glTranslated(mX, mY, 0.0);//3rd
    glRotated(mDegrees, 0.0, 0.0, 1.0);//2nd
    glScaled(.5, .5, 1);//1st
    glTranslated(-mX, -mY, 0);
    
    glColor3d(.75, .75, .75);
    
    DrawTriangle(mX-.5, mY-.5, mX+.5, mY-.5, mX, mY); //outerearright
    DrawTriangle(mX-.5, mY+.5, mX+.5, mY+.5, mX, mY); //outerearleft
    DrawCircle(mX, mY, .3); //head
    glColor3d(1, .8, .89);
    DrawTriangle(mX-.3, mY-.4, mX+.3, mY-.4, mX, mY-.2); //innerearright
    DrawTriangle(mX-.3, mY+.4, mX+.3, mY+.4, mX, mY+.2); //innerearleft
    glColor3d(1, 1, 1);
    DrawCircle(mX, mY-.1, .1);//eyeright
    DrawCircle(mX, mY+.1, .1);//eyeleft
    glColor3d(0, 0, 0);
    DrawCircle(mX+.05, mY-.1, .05);//pupilright
    DrawCircle(mX+.05, mY+.1, .05);//pupilleft
    DrawCircle(mX+.35, mY, .1);//nose
    glPopMatrix();
}

void Rat::scurry(double dt, Maze &maze)
{
    double radians = mDegrees * M_PI / 180;
    double dx = cos(radians) * dt * SCURRY_SPEED;
    double dy = sin(radians) * dt * SCURRY_SPEED;
    if (maze.isSafe(mX+dx, mY+dy, mRadius))
    {
        mX += dx;
        mY += dy;
    }
    else if (maze.isSafe(mX, mY+dy, mRadius))
    {
        mY += dy;
    }
    else if (maze.isSafe(mX+dx, mY, mRadius))
    {
        mX += dx;
    }
    
}

void Rat::turnLeft(double dt)
{
    mDegrees += TURN_SPEED * dt * 360;
}

void Rat::turnRight(double dt)
{
    mDegrees -= TURN_SPEED * dt * 360;
}


