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

const int COL = 5;
const int ROW = 5;

class Maze
{
public:
    Maze();
    void draw();
    void removeWalls(int x, int y);
    bool isSafe(double x, double y, double radius);
    enum viewtype{top_view, perspective_view, rat_view};
    viewtype current_view = top_view;

    class Cell
    {
    public:
        Cell();
        void draw(int x, int y, char type);
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
