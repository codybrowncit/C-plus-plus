//
//  terrain.cpp
//  MacGraphicsStarter
//
//  Created by Cody Brown on 3/6/15.
//
//
#include "cmath"
#include "terrain.h"

using namespace std;


Terrain::Terrain()
{
    srand(time(0));
    for (int x=0; x<COL+1; x++)
    {
        mCell[x][0].mBottom = true;
        mCell[x][49].mTop = true;
        mCell[0][x].mLeft = true;
        mCell[49][x].mRight = true;
    }
}

Terrain::Cell::Cell()
{

}
bool Terrain::Cell::getLeft()
{
    return mLeft;
}

bool Terrain::Cell::getRight()
{
    return mRight;
}

bool Terrain::Cell::getTop()
{
    return mTop;
}

bool Terrain::Cell::getBottom()
{
    return mBottom;
}



bool Terrain::isSafe(double x, double y, double radius)
{
    int celli = (int)x;
    int cellj = (int)y;
    double offsetx = x-celli;
    double offsety = y-cellj;
    if ((offsetx - radius < 0 && mCell[celli][cellj].getLeft()) || (offsetx + radius > 1 && mCell[celli][cellj].getRight()) || (offsety - radius < 0 && mCell[celli][cellj].getBottom()) || (offsety + radius > 1 && mCell[celli][cellj].getTop()))
    {
        return false;
    }
    if ((offsetx - radius < 0 && offsety - radius < 0) || (offsetx - radius < 0 && offsety + radius > 1) || (offsetx + radius > 1 && offsety - radius < 0) || (offsetx + radius > 1 && offsety + radius > 1))
    {
        return false;
    }
    
    return true;
}
double Terrain::get_z(double x, double y)
{
    return (y * .03 * sin(y * .09)) + (.221 * y * cos(x*.09)) + ( .9 * sin(x*.432)) * (x * .03 + cos(y*.32324));
}

void Terrain::draw(int zed)
{
    
    for (int x=0; x<COL; x++)
    {
        for (int y=0; y<ROW; y++)
        {
            z[x][y] = get_z(x, y);
        }
    }
    for (int x=0; x<COL; x++)
    {
        for (int y=0; y<ROW; y++)
        {
            int r =(x*37952+y*79528174)%256;
            int g = (x*93489021+y*349812374)%256;
            int b = (x*1234+y*4321)%256;
            glColor3ub(r,g,b);
            glBegin(GL_QUADS);
            glVertex3d(x,y, z[x][y]);
            glVertex3d(x+1,y, z[x+1][y]);
            glVertex3d(x+1,y+1, z[x+1][y+1]);
            glVertex3d(x,y+1, z[x][y+1]);
            glEnd();
            mCell[x][y].mZed = zed;
            mCell[x][y].draw(x, y);
        }
    }
}

void Terrain::Cell::draw(int x, int y)
{

    glColor3d(0,0,1);
    glBegin(GL_QUADS);
    glVertex3d(x,y, mZed);
    glVertex3d(x+1,y, mZed);
    glVertex3d(x+1,y+1, mZed);
    glVertex3d(x,y+1, mZed);
    glEnd();
}