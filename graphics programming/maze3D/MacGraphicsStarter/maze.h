//
//  maze.h
//  MacGraphicsStarter
//
//  Created by Cody Brown on 2/3/15.
//
//

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>
#include <GLUT/glut.h>
#include <vector>

#ifndef __MAZE_H_
#define __MAZE_H_

const int COL = 10;
const int ROW = 10;

class Maze
{
public:
    Maze();
    void draw();
    void removeWalls(int x, int y);
    bool isSafe(double x, double y, double radius);
    class Cell
    {
    public:
        Cell();
        void draw(int x, int y);
        bool getLeft();
        bool getRight();
        bool getTop();
        bool getBottom();
        bool mBottom, mTop, mLeft, mRight, mVisited;
        std::string num;
    };
    Cell mCell[COL][ROW];
};

#include <stdio.h>

#endif /* defined(__MacGraphicsStarter__maze__) */
