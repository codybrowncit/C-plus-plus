//
//  maze.cpp
//  MacGraphicsStarter
//
//  Created by Cody Brown on 2/3/15.
//
//

#include "maze.h"
#include "Tga.h"
using namespace std;
int counter=0;

extern GLuint texName[];
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
    if (current_view != top_view ) {
        if (current_view !=perspective_view){
    // sky
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texName[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3d(-10, -10, .5);
    glTexCoord2f(1, 0); glVertex3d(-10, 10, .5);
    glTexCoord2f(1, 1); glVertex3d(10, 10, .5);
    glTexCoord2f(0, 1); glVertex3d(10, -10, .5);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    }
    // ground
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texName[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3d(0, 0, 0);
    glTexCoord2f(10, 0); glVertex3d(0, ROW, 0);
    glTexCoord2f(10, 10); glVertex3d(COL, ROW, 0);
    glTexCoord2f(0, 10); glVertex3d(COL, 0, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
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

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texName[1]);

        if (mBottom)
        {
            glBegin(GL_QUADS);
            glTexCoord2f(0, 0);
            glVertex3d(x,y-.0005, 0);
            glTexCoord2f(1, 0);
            glVertex3d(x+1,y-.0005, 0);
            glTexCoord2f(1, 1);
            glVertex3d(x+1,y-.0005, .5);
            glTexCoord2f(0, 1);
            glVertex3d(x,y-.0005, .5);
            glEnd();
            
        }
        if (mLeft)
        {

            glBegin(GL_QUADS);
            glTexCoord2f(0, 0);
            glVertex3d(x-.0005,y+1, 0);
            glTexCoord2f(1, 0);
            glVertex3d(x-.0005,y, 0);
             glTexCoord2f(1, 1);
            glVertex3d(x-.0005,y, .5);
            glTexCoord2f(0, 1);
            glVertex3d(x-.0005,y+1, .5);
            glEnd();

        }
        if (mRight)
        {

            glBegin(GL_QUADS);
            glTexCoord2f(0, 0);
            glVertex3d(x+1,y, 0);
            glTexCoord2f(1, 0);
            glVertex3d(x+1,y+1, 0);
             glTexCoord2f(1, 1);
            glVertex3d(x+1,y+1, .5);
            glTexCoord2f(0, 1);
            glVertex3d(x+1,y, .5);
            glEnd();
        }
        if (mTop)
        {

            glBegin(GL_QUADS);
            glTexCoord2f(0, 0);
            glVertex3d(x+1,y+1, 0);
            glTexCoord2f(1, 0);
            glVertex3d(x,y+1, 0);
             glTexCoord2f(1, 1);
            glVertex3d(x,y+1, .5);
            glTexCoord2f(0, 1);
            glVertex3d(x+1,y+1, .5);
            glEnd();
        }
        glDisable(GL_TEXTURE_2D);

        
       
    }
    

}
