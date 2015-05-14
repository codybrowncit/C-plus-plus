

#include "curve.h"
#include <GLUT/GLUT.h>
#include <math.h>

void drawCircle(double x1, double y1, double radius)
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

void drawLine(Point *p1, Point *p2) {
    glBegin(GL_LINES);
    glVertex2d(p1->x, p1->y);
    glVertex2d(p2->x, p2->y);
    glEnd();
}

// Calculate the next bezier point.
Point* drawBezier(Point *A, Point *B, Point *C, Point *D, double t) {
    Point *P = new Point(0, 0);
    P->x = pow((1 - t), 3) * A->x + 3 * t * pow((1 -t), 2) * B->x + 3 * (1-t) * pow(t, 2)* C->x + pow (t, 3)* D->x;
    P->y = pow((1 - t), 3) * A->y + 3 * t * pow((1 -t), 2) * B->y + 3 * (1-t) * pow(t, 2)* C->y + pow (t, 3)* D->y;
    P->z = pow((1 - t), 3) * A->z + 3 * t * pow((1 -t), 2) * B->z + 3 * (1-t) * pow(t, 2)* C->z + pow (t, 3)* D->z;
    
    return P;
}

void Curve::draw()
{
    for (int i=0; i<4; i++)
    {
        if (isSelected)
        {
            glColor3f(1, 0, 0);
            drawCircle(points[i]->x, points[i]->y, kControlPointRadius);
        }
        else{
        glColor3f(0.0,0.0,0.0);
        drawCircle(points[i]->x, points[i]->y, kControlPointRadius);
        }
    }
    
    Point *pivot = points[0];
    for (double t = 0.0; t <= 1.0; t += 0.01) {
        Point *P = drawBezier(points[0], points[1], points[2], points[3],  t);
        glColor3f(rgb[0], rgb[1], rgb[2]);
        drawLine(pivot, P);
        pivot = P;
    }
}

int Curve::controlAtPoint(int x, int y)
{
    for (int i=0; i<4; i++)
    {
        Point *point = points[i];
        if (x >= point->x - (kControlPointRadius * 2) && x <= point->x + (kControlPointRadius * 2) &&
            y >= point->y - (kControlPointRadius * 2) && y <= point->y + (kControlPointRadius * 2))
        {
            return i;
        }
    }
    return -1;
}

void Curve::setRgb(double rgb_in[3])
{
    rgb[0] = rgb_in[0];
    rgb[1] = rgb_in[1];
    rgb[2] = rgb_in[2];
}

Curve::Curve(Point* points_in[4], double rgb_in[3])
{
    points[0] = points_in[0];
    points[1] = points_in[1];
    points[2] = points_in[2];
    points[3] = points_in[3];
    rgb[0] = rgb_in[0];
    rgb[1] = rgb_in[1];
    rgb[2] = rgb_in[2];
    isSelected = false;
}
