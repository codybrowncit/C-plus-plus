//
//  terrain.cpp
//  MacGraphicsStarter
//
//  Created by Cody Brown on 3/6/15.
//
//

#include "terrain.h"

using namespace std;


Terrain::Terrain()
{
    srand(time(0));
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

void Terrain::draw()
{
    
    for (int i=0; i<COL; i++)
    {
        for (int j=0; j<ROW; j++)
        {
            if(current_view == top_view)
            {
                mCell[i][j].draw(i, j, 't');
            }
            else
            {
                mCell[i][j].draw(i, j, 'p');
            }
            
        }
    }
}



void Terrain::Cell::draw(int x, int y, char type)
{

    int r =(x*37952+y*79528174)%256;
    int g = (x*93489021+y*349812374)%256;
    int b = (x*1234+y*4321)%256;
    glColor3ub(r,g,b);
    glBegin(GL_QUADS);
    glVertex3d(x,y, 0);
    glVertex3d(x+1,y, 0);
    glVertex3d(x+1,y+1, 0);
    glVertex3d(x,y+1, 0);
    glEnd();
}