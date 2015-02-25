//
//  Board.cpp
//  MacGraphicsStarter
//
//  Created by Cody Brown on 11/22/14.
//
//

#include "Board.h"
#include <iostream>

std::vector<Button*> Buttons (7);
std::vector<Circle*> circles;

Board::Board()
{
    Mblue = 1.0;
    Mred = 1.0;
    Mgreen = 1.0;
    Mturn = 1;

}
void Board::DrawText(double x, double y, const char *string)
{
    void *font = GLUT_BITMAP_9_BY_15;
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    int len, i;
    glRasterPos2d(x, y);
    len = (int) strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
    
    glDisable(GL_BLEND);
}
void Board::Draw()
{
    int leftb_x1 = 0;
    int length = 100;
    int height= 450;
    int fstb_y1 = 25;
    int leftb_x2 = leftb_x1+length;
    int circle_x1 = 50;
    int circle_y = 60;
    int circle_x2 = circle_x1+30;
    for (int k=0; k<7; k++)
    {
        Buttons[k] = new Button(leftb_x1, fstb_y1, leftb_x2, fstb_y1+height, "", false, 0.0, 0.0, 0.0);
        leftb_x1+=100;
        leftb_x2+=100;
        for (int j=0; j<6; j++)
        {
            if( spaces[k][j]== 0)
            {
                Mblue = 1.0;
                Mred = 1.0;
                Mgreen = 1.0;
            }
            else if(spaces[k][j]== 1)
            {
                Mblue = 0.0;
                Mred = 1.0;
                Mgreen = 0.0;
            }
            else
            {
                Mblue = 1.0;
                Mred = 0.0;
                Mgreen = 0.0;
            }
          //  std::cout << "spaces["<<k<<"]["<<j<<"]"<<spaces[k][j]<<std::endl;
            circles.push_back(new Circle(circle_x1, circle_y, circle_x2, circle_y, Mred, Mgreen, Mblue));
            circle_y+=75;
        }
        circle_y = 60;
        circle_x1+=100;
        circle_x2+=100;
    }

    
    for(int i=0; i<Buttons.size(); i++)
    {
        if (i>7)
        {
            glColor3d(1,0,0);
        }
        Buttons[i]->draw();
    }
    for(int i=0; i<circles.size(); i++)
    {
        circles[i]->draw();
    }
    if (Mwin && Mturn == 2)
    {

        glColor3b(1.0, 0.0, 0.0);
        DrawText(5, 5, "Player 1, You Win!");
    }
    else if (Mwin && Mturn == 1)
    {
        
        glColor3b(0.0, 0.0, 1.0);
        DrawText(5, 5, "Player 2, You Win!");
    }
    else if (Mturn == 1)
    {
        glColor3d(1.0, 0.0, 0.0);
        DrawText(5, 5, "Player 1, It's Your Turn");
    }
    else
    {
        glColor3d(0.0, 0.0, 1.0);
        DrawText(5, 5, "Player 2, It's Your Turn");
    }
}

void Board::Move(int button)
{
    for (int i =0; i<6; i++){
        if (spaces[button][i] == 0) {
            std::cout << "spaces["<<button<<"]["<<i<<"]"<<spaces[button][i];
            spaces[button][i] = Mturn;
            std::cout << "spaces["<<button<<"]["<<i<<"]"<<spaces[button][i]<<std::endl;
            if (Win())
            {
                std::cout<<"Player "<<Mturn<< " is the winner"<<std::endl;
                Mwin= true;
            }
            if (Mturn == 1)
            {
                Mturn =2;
            }
            else
            {
                Mturn = 1;
            }
            break;
        }
        
    }
}

void Board::MouseClick(double x, double y)
{
   if (Mwin)
   {
       return;
   }
    for (int j = 0; j<7; j++)
    {
        if(Buttons[j]->clicked(x, y))
        {
            Move(j);
        }
    }
}

bool Board::Win()
{
    for (int i =0; i<7; i++)
    {
        for (int j=0; j<6; j++)
        {
            if (spaces[i][j] != 0)
            {
                if (i+1 <7 && i+2 < 7 && i+3 < 7 && spaces[i][j] == spaces[i+1][j] && spaces[i][j] == spaces[i+2][j] && spaces[i][j] == spaces[i+3][j])
                {
                    return true;
                }
                else if (j+1 < 6 && j+2 < 6 && j+3 < 6 && spaces[i][j] == spaces[i][j+1] && spaces[i][j] == spaces[i][j+2] && spaces[i][j] == spaces[i][j+3])
                {
                    return true;
                }
                else if (i+1 <7 && i-2 < 7 && i-3 < 7 && j+1 <6 && j+2 <6  && j+3 < 6 && spaces[i][j] == spaces[i+1][j+1] && spaces[i][j] == spaces[i+2][j+2] && spaces[i][j] == spaces[i+3][j+3])
                {
                    return true;
                }
                else if (i-1 >0 && i-2 > 0 && i-3 > 0 && spaces[i][j] == spaces[i-1][j+1] && spaces[i][j] == spaces[i-2][j+2] && spaces[i][j] == spaces[i-3][j+3])
                {
                    return true;
                }
            }
            
        }
    }
    return false;
}