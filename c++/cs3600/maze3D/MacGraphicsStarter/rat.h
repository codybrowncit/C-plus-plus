//
//  rat.h
//  MacGraphicsStarter
//
//  Created by Cody Brown on 2/11/15.
//
//

#ifndef _RAT_H_
#define _RAT_H_

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>
#include <GLUT/glut.h>
#include <vector>
#include <cmath>
#include "maze.h"
using namespace std;
const double SCURRY_SPEED = 50;
const double TURN_SPEED = 10;

class Rat
{
public:
    Rat();
    void draw();
    void scurry(double dt, Maze &maze);
    void turnLeft(double dt);
    void turnRight(double dt);
    double get_x();
    double get_y();
    
    
private:
    double mX, mY, mDegrees, mRadius;
    Maze *mMaze;

    
};



#endif /* defined(__MacGraphicsStarter__rat__) */
