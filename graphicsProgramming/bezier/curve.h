#ifndef __Bezier__Curve__
#define __Bezier__Curve__

#include "point.h"

static double kControlPointRadius = 6;
static double kCurveRedColor[3] = { 1.0, 0.0, 0.0 };
static double kCurveGreenColor[3] = { 0.0, 1.0, 0.0 };
static double kCurveBlueColor[3] = { 0.0, 0.0, 1.0 };
static double kCurveOrangeColor[3] = { 226/255.0, 163/255.0, 1/255.0 };
static double kCurveYellowColor[3] = { 253/255.0, 245/255.0, 4/255.0 };
static double kCurvePurpleColor[3] = { 216/255.0, 63/255.0, 255/255.0 };

class Curve {
public:
    Curve(Point* points_in[4], double rgb_in[3]);
    Point* points[4];
    double rgb[3];
    void draw();
    void setRgb(double rgb_in[3]);
    int controlAtPoint(int x, int y);
    bool isSelected;
};

#endif /* defined(__Bezier__Curve__) */
