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
    void draw(Maze &maze);
    void scurry(double dt, Maze &maze);
    void turnLeft(double dt);
    void turnRight(double dt);
    void moveLeft(double dt, Maze &maze);
    void moveRight(double dt, Maze &maze);
    void jump(double dt, Maze &maze);
    double get_x();
    double get_y();
    double get_dx();
    double get_dy();
    
    
private:
    double dx, dy, mX, mY, mDegrees, mRadius;


    
};



#endif /* defined(__MacGraphicsStarter__rat__) */
