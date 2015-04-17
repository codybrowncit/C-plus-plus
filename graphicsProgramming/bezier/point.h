#ifndef __Bezier__Point__
#define __Bezier__Point__

#include <iostream>

class Point {
public:
    double x, y, z;
    Point() {};
    Point(double x, double y);
    void setxy(double x2, double y2) { x = x2; y = y2; }
    const Point & operator=(const Point &rPoint) {
        x = rPoint.x;
        y = rPoint.y;
        z = rPoint.z;
        
        return *this;
    }
    
};

#endif /* defined(__Bezier__Point__) */