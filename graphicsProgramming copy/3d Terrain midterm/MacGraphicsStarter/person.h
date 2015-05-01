//
//  person.h
//  MacGraphicsStarter
//
//  Created by Cody Brown on 3/6/15.
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
#include "terrain.h"
using namespace std;

const double MOVE_SPEED = 50;
const double TURN_SPEED = 10;

class Person
{
public:
    Person();
    void move(double dt, Terrain &terrain);
    void turnLeft(double dt);
    void turnRight(double dt);
    double get_x();
    double get_y();
    double get_dx();
    double get_dy();
    
    
private:
    double dx, dy, mX, mY, mDegrees, mRadius;

    
    
};



#endif /* defined(__MacGraphicsStarter__person__) */
