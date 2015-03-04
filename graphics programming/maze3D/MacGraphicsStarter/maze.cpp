//
//  maze.cpp
//  MacGraphicsStarter
//
//  Created by Cody Brown on 2/3/15.
//
//

#include "maze.h"

using namespace std;
int counter=0;


Maze::Maze()
{
    srand(time(0));
    removeWalls(0, 0);
    mCell[0][0].mBottom = false;
    mCell[COL-1][ROW-1].mTop = false;
}

Maze::Cell::Cell()
{
    mTop = mBottom = mLeft = mRight = true;
    mVisited = false;
    num = '0';
}

bool Maze::Cell::getLeft()
{
    return mLeft;
}

bool Maze::Cell::getRight()
{
    return mRight;
}

bool Maze::Cell::getTop()
{
    return mTop;
}

bool Maze::Cell::getBottom()
{
    return mBottom;
}

void Maze::draw()
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



void Maze::removeWalls(int x, int y)
{
    mCell[x][y].mVisited = true;
    vector<char> moves;
    int random;
    while (true)
    {
        moves.clear();
        if (y > 0 && !mCell[x][y-1].mVisited)//down
        {
           moves.push_back('d');
           
        }
        if (y < COL-1 && !mCell[x][y+1].mVisited)//up
        {
            moves.push_back('u');
        }
        if (x > 0 && !mCell[x-1][y].mVisited)//left
        {
            moves.push_back('l');
        }
        if (x < ROW-1 && !mCell[x+1][y].mVisited)//right
        {
            moves.push_back('r');
        }
        if (moves.size()>0)
        {
           /*
            counter++;                // number to be converted to a string
            string Result;            // string which will contain the result
            ostringstream convert;    // stream used for the conversion
            convert << counter;       // insert the textual representation of 'Number' in the characters in the stream
            result = convert.str();   // stores converted string in result
            mCell[x][y].num = result; // stores result in data member num
            */
            random = rand() % moves.size();
            if (moves[random] == 'd')
            {
                mCell[x][y].mBottom = false;
                mCell[x][y-1].mTop = false;
                removeWalls(x, y-1);
            }
            if (moves[random] == 'u')
            {
                mCell[x][y].mTop = false;
                mCell[x][y+1].mBottom = false;
                removeWalls(x, y+1);
            }
            if (moves[random] == 'l')
            {
                mCell[x][y].mLeft = false;
                mCell[x-1][y].mRight = false;
                removeWalls(x-1, y);
            }
            if (moves[random] == 'r')
            {
                mCell[x][y].mRight = false;
                mCell[x+1][y].mLeft = false;
                removeWalls(x+1, y);
            }
        }
        else
        {
            break;
        }
    }
}
bool Maze::isSafe(double x, double y, double radius)
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
void Maze::Cell::draw(int x, int y, char type)
{
    if(type == 't')
    {
        glBegin(GL_LINES);
        glColor3d(0,0,1);
        if (mBottom)
        {
            glVertex2d(x, y);
            glVertex2d(x+1, y);
        }
        if (mLeft)
        {
            glVertex2d(x, y);
            glVertex2d(x, y+1);
        }
        if (mTop)
        {
            glVertex2d(x, y+1);
            glVertex2d(x+1, y+1);
        }
        if (mRight)
        {
            glVertex2d(x+1, y);
            glVertex2d(x+1, y+1);
        }
        glEnd();
    }
    else
    {
        // draw walls as GL_QUADS

        
        if (mBottom)
        {
            glColor3d(1,0,0);
            glBegin(GL_QUADS);
            glVertex3d(x,y-.0005, 0);
            glVertex3d(x+1,y-.0005, 0);
            glVertex3d(x+1,y-.0005, .5);
            glVertex3d(x,y-.0005, .5);
            glEnd();
        }
        if (mLeft)
        {
            glColor3d(0,1,0);
            glBegin(GL_QUADS);
            glVertex3d(x-.0005,y+1, 0);
            glVertex3d(x-.0005,y, 0);
            glVertex3d(x-.0005,y, .5);
            glVertex3d(x-.0005,y+1, .5);
            glEnd();
        }
        if (mRight)
        {
            glColor3d(0,0,1);
            glBegin(GL_QUADS);
            glVertex3d(x+1,y, 0);
            glVertex3d(x+1,y+1, 0);
            glVertex3d(x+1,y+1, .5);
            glVertex3d(x+1,y, .5);
            glEnd();
        }
        if (mTop)
        {
            glColor3d(1,1,0);
            glBegin(GL_QUADS);
            glVertex3d(x+1,y+1, 0);
            glVertex3d(x,y+1, 0);
            glVertex3d(x,y+1, .5);
            glVertex3d(x+1,y+1, .5);
            glEnd();
        }

        
        // figure out a way to draw each wall in a different color. (you don't have to save the color of the wall)
        // figure out a way to prevent two co-planar wall from 'bleeding' on top of each other when drawing.
    }
    

}
