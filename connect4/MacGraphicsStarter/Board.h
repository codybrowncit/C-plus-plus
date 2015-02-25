//
//  Board.h
//  MacGraphicsStarter
//
//  Created by Cody Brown on 11/22/14.
//
//

#ifndef _BOARD_H_
#define _BOARD_H_
#include "Button.h"
#include "Circle.h"
#include <vector>
#include <iostream>
#include <stdio.h>
#include <cmath>

class Board
{
public:
    Board();
    // set all 42 squares to empty
    // set current player (turn) to red.
   bool Win();
    // sets Mwin 0 if game still going, 1 if red wins, 2 if blue wins, 3 on a draw.
    // for wins, check all 24 horizontal wins, all 21 vertical wins, all 24 diagonal wins
    // for a tie, check if there are no white squares left.
   void Draw();
    // Draw the board
    // Draw the 7 drop boxes.
    // Draw the 42 circles as red, black, or white(for empty)
    // Maybe also print whose turn it is.
    
    void MouseClick(double x, double y);
    // If the click is not in one of the 7 drop boxes, ignore and return
    // If the clicked on drop box is full, ignore and return
    // Update the appropriate board space from white to red or blue
    // toggle the current player
    // check for Win
    void Move(int button);
    void DrawText(double x, double y, const char *string);
private:
    // Storing what is in each of the 42 squares: red, blue, or white
    // Current player: red or blue

    double Mred,Mgreen,Mblue;
    int spaces[7][8];
    int Mturn;
    bool Mwin;
};

#endif /* defined(__MacGraphicsStarter__Board__) */
