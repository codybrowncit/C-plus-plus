// OpenGL/GLUT starter kit for Windows 7 and Visual Studio 2010
// Created spring, 2011
//
// This is a starting point for OpenGl applications.
// Add code to the "display" function below, or otherwise
// modify this file to get your desired results.
//
// For the first assignment, add this file to an empty Windows Console project
//		and then compile and run it as is.
// NOTE: You should also have glut.h,
// glut32.dll, and glut32.lib in the directory of your project.
// OR, see GlutDirectories.txt for a better place to put them.

#include <cmath>
#include <cstring>
#include <cstdlib>
#include "Pentagon.h"
#include "Triangle.h"
#include "Circle.h"
#include "Button.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#ifdef _WIN32
  #include "glut.h"
#else
  #ifdef __APPLE__
    #include <GLUT/glut.h>
  #else
    #include <GL/glut.h>
  #endif
#endif

// Global Variables (Only what you need!)
double screen_x = 700;
double screen_y = 500;
std::vector<Shape*> shapes_vector;
std::vector<int> clicks;
unsigned int i;
std::vector<Button*> buttons (5);
std::vector<Shape*> feedback;
std::vector<Button*> slider;
double red, green, blue;
bool solid=true;
int rx1, rx2, gx1, gx2, bx1, bx2;
std::vector<Shape*> saved_shape;

//
// Functions that draw basic primitives
//



// Outputs a string of text at the specified location.
void DrawText(double x, double y, const char *string)
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

void createButtons()
{
    int leftb_x1 = 25;
    int length = 100;
    int height= 30;
    int fstb_y1 = 25;
    int sndb_y1 = fstb_y1+50;
    int trdb_y1 = sndb_y1+50;
    int frthb_y1 = trdb_y1+50;
    int fthb_y1 = frthb_y1+50;
    int sixb_y1 = fthb_y1+50;
    int rightb_x1 = 575;
    int rightb_x2 = rightb_x1+length;
    int leftb_x2 = leftb_x1+length;
    buttons[0] = new Button(leftb_x1, fstb_y1, leftb_x2, fstb_y1+height, "Rectangle", true, 1.0, 0.0, 0.0, true);
    buttons[1] = new Button(leftb_x1, sndb_y1, leftb_x2, sndb_y1+height, "Circle", false, 1.0, 0.0, 0.0,true);
    buttons[2] = new Button(leftb_x1, trdb_y1, leftb_x2, trdb_y1+height, "Triangle", false, 1.0, 0.0, 0.0,true);
    buttons[3] = new Button(rightb_x1, fstb_y1, rightb_x2, fstb_y1+height, "Quit", false, 0.0, 0.0, 1.0,true);
    buttons[4] = new Button(rightb_x1, sndb_y1, rightb_x2, sndb_y1+height, "Clear", false, 0.0, 0.0, 1.0,true);
    buttons.push_back(new Button(rightb_x1, trdb_y1, rightb_x2, trdb_y1+height, "Undo",false, 0.0, 0.0, 1.0,true));
    buttons.push_back(new Button(rightb_x1, frthb_y1, rightb_x2, frthb_y1+height, "Load",false, 0.0, 0.0, 1.0,true));
    buttons.push_back(new Button(rightb_x1, fthb_y1, rightb_x2, fthb_y1+height, "Save",false, 0.0, 0.0, 1.0,true));
    buttons.push_back(new Button(leftb_x1, 325, leftb_x2, 325+height, "Solid", true, 1.0, 0.0, 0.0, true));
    buttons.push_back(new Button(rightb_x1, sixb_y1, rightb_x2, sixb_y1+height, "Redo", false, 0.0,0.0,1.0,true));
    buttons.push_back(new Button(rightb_x1, sixb_y1+50, rightb_x2, sixb_y1+height+50, "Pentagon", false, 1.0,0.0,0.0,true));
}

void drawButtons()
{
    int text_padding_left = 5;
    int text_padding_bottom = 10;
    
    for(i=0; i<buttons.size(); i++)
    {
        if (i>7)
        {
            glColor3d(1,0,0);
        }
        buttons[i]->draw();
        if (buttons[i]->mActive)
        {
            glColor3d(0,1,0);
        }
        else
        {
            glColor3d(1,1,1);
        }
        DrawText(buttons[i]->points[0]+text_padding_left, buttons[i]->points[1]+text_padding_bottom, buttons[i]->mTitle);
    }
}

void drawShapes()
{
    int text_padding_left = 5;
    int text_padding_bottom = 10;
    
    for(i=0; i<shapes_vector.size(); i++)
    {
        shapes_vector[i]->draw();
    }
}

void drawFeedback()
{
    for(i=0; i<feedback.size(); i++)
    {
        glColor3d(1,1,1);
        feedback[i]->draw();
    }
}

void createSliders()
{
    int x1 = 25;
    int length = 100;
    int height = 30;
    int x2 = x1+length;
    int y1 = 175;
    int snd_y1 = y1+50;
    int trd_y1 = snd_y1+50;
    int fth_y1 = trd_y1+50;
    // draw slider posts
    buttons.push_back(new Button(x1, y1, x2, y1+height, "Blue", false, red, green, blue,true));
    buttons.push_back(new Button(x1, snd_y1, x2, snd_y1+height, "Green", false, red, green, blue,true));
    buttons.push_back(new Button(x1, trd_y1, x2, trd_y1+height, "Red",false, red, green, blue,true));
    // draw slider dials
    buttons.push_back(new Button(bx1, y1, bx2, y1+height, "", false, 1.0, 0.0, 0.0,true));
    buttons.push_back(new Button(gx1, snd_y1, gx2, snd_y1+height, "", false, 1.0, 0.0, 0.0,true));
    buttons.push_back(new Button(rx1, trd_y1, rx2, trd_y1+height, "", false, 1.0, 0.0, 0.0,true));
}


void feedbacks(int x,int xdisplay, int ydisplay)
{
    feedback.push_back(new Circle(xdisplay, ydisplay, xdisplay+2, ydisplay+2, 0.0, 0.0, 0.0,true));
    clicks.push_back(x);
    clicks.push_back(ydisplay);
}

//
// GLUT callback functions
//

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(0,0,1);
    drawButtons();
    drawShapes();
    drawFeedback();
  glutSwapBuffers();
}


// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard(unsigned char c, int x, int y)
{
  switch (c) 
    {
    case 'q':
    case 27: // escape character means to quit the program
      exit(0);
      break;
    case 'b':
      // do something when 'b' character is hit.
      break;
    default:
      return; // if we don't care, return without glutPostRedisplay()
    }
  glutPostRedisplay();
}

// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape(int w, int h)
{
  // Reset our global variables to the new width and height.
  screen_x = w;
  screen_y = h;

  // Set the pixel resolution of the final picture (Screen coordinates).
  glViewport(0, 0, w, h);

  // Set the projection mode to 2D orthographic, and set the world coordinates:
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, w, 0, h);
  glMatrixMode(GL_MODELVIEW);
}


// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse(int mouse_button, int state, int x, int y)
{
  // translate pixel coordinates to display coordinates
  int xdisplay = x;
  int ydisplay = screen_y - y;
  if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
    {
        // check if it was a button click
        if(buttons[0]->clicked(xdisplay, ydisplay))
        {
            buttons[0]->setActive();
            buttons[1]->setInactive();
            buttons[2]->setInactive();
            buttons[10]->setInactive();
            feedback.clear();
            clicks.clear();
            return;
        }
        else if(buttons[1]->clicked(xdisplay, ydisplay))
        {
            buttons[1]->setActive();
            buttons[2]->setInactive();
            buttons[0]->setInactive();
            buttons[10]->setInactive();
            feedback.clear();
            clicks.clear();
            return;
        }
        else if(buttons[2]->clicked(xdisplay, ydisplay))
        {
            buttons[2]->setActive();
            buttons[0]->setInactive();
            buttons[1]->setInactive();
            buttons[10]->setInactive();
            feedback.clear();
            clicks.clear();
            return;
        }
        else if(buttons[10]->clicked(xdisplay, ydisplay))
        {
            buttons[10]->setActive();
            buttons[0]->setInactive();
            buttons[1]->setInactive();
            buttons[2]->setInactive();
            feedback.clear();
            clicks.clear();
            return;
        }
        else if(buttons[3]->clicked(xdisplay, ydisplay))
        {
            exit(0);
        }
        else if(buttons[4]->clicked(xdisplay, ydisplay))
        {
            shapes_vector.clear();
            saved_shape.clear();
            feedback.clear();
            clicks.clear();
            return;
        }
        else if(buttons[5]->clicked(xdisplay, ydisplay))
        {
            
            if (shapes_vector.size() > 0)
            {
                saved_shape.push_back(shapes_vector.back());
                shapes_vector.pop_back();
            }
            feedback.clear();
            clicks.clear();
            return;
        }
        else if(buttons[8]->clicked(xdisplay, ydisplay))
        {
            
            if(buttons[8]->getActive())
            {
                buttons[8]->setInactive();
                solid = false;
                feedback.clear();
                clicks.clear();
                return;
            }
            else
            {
                buttons[8]->setActive();
                solid = true;
                feedback.clear();
                clicks.clear();
                return;
            }
        }
        else if(buttons[9]->clicked(xdisplay, ydisplay))
        {
            if (saved_shape.size()>0)
            {
                shapes_vector.push_back(saved_shape.back());
                saved_shape.pop_back();
            }
            return;
        }
        else if(buttons[6]->clicked(xdisplay, ydisplay))
        {
            std::string kind;
            double x1, x2, y1, y2, x3, y3, x4, y4, x5,y5;
            std::ifstream fin("data.txt");
            while (fin >> kind)
            {
                if (kind == "Triangle")
               {
                   fin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
                   fin >> red >> green >>blue;
                   fin >> solid;
                   shapes_vector.push_back(new Triangle(x1, y1, x2, y2, x3, y3, red, green, blue, solid));
                   
               }
                else if(kind == "Rectangle")
                {
                    fin >> x1 >> y1 >> x2 >> y2;
                    fin >> red >> green >>blue;
                    fin >> solid;
                    shapes_vector.push_back(new Rectangle(x1, y1, x2, y2, red, green, blue, solid));
                }
                else if(kind == "Circle")
                {
                    fin >> x1 >> y1 >> x2 >> y2;
                    fin >> red >> green >>blue;
                    fin >> solid;
                    shapes_vector.push_back(new Circle(x1, y1, x2, y2, red, green, blue, solid));
                }
                else if(kind == "Pentagon")
                {
                    fin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4 >>x5 >>y5;
                    fin >> red >> green >>blue;
                    fin >> solid;
                    shapes_vector.push_back(new Pentagon(x1, y1, x2, y2, x3, y3, x4, y4, x5,y5, red, green, blue, solid));
                }
            }
            return;
            
            
        }
        else if(buttons[7]->clicked(xdisplay, ydisplay))
        {
            std::ofstream fout;
            fout.open("data.txt", std::ios::out);
            if(!fout)
            {
                std::cerr << "error: could not write file";
                return;
            }
            for(i=0; i<shapes_vector.size(); i++)
            {
                
                if(shapes_vector[i]->Mid == 1)
                {
                    fout << "Circle" << std::endl;
                }
                else if(shapes_vector[i]->Mid == 2)
                {
                    fout << "Rectangle" <<std::endl;
                }
                else if(shapes_vector[i]->Mid == 4)
                {
                    fout << "Pentagon" <<std::endl;
                }
                else
                {
                    fout << "Triangle" << std::endl;
                }
                int j;
                for(j=0; j<shapes_vector[i]->points.size(); j++)
                {
                    fout << shapes_vector[i]->points[j] << " ";
                }
                fout << std::endl;
                fout << shapes_vector[i]->Mred << " " << shapes_vector[i]->Mgreen << " " << shapes_vector[i]->Mblue << std::endl;
                fout << shapes_vector[i]->mSolid<<std::endl;
            }
            fout.close();
            return;
        }
        for(i=10; i<buttons.size(); i++)
            
        {
            if(i <14 && buttons[i]->clicked(xdisplay, ydisplay))
            {
                switch (i)
                {
                    case 11:
                       blue = (double)(xdisplay-25)/100;
                        std::cout<<xdisplay;
                        bx1=xdisplay-5;
                        bx2=xdisplay+5;
                        createSliders();
                        feedback.clear();
                        clicks.clear();
                        return;
                    case 12:
                       green = (double)(xdisplay-25)/100;
                        gx1=xdisplay-5;
                        gx2=xdisplay+5;
                        createSliders();
                        feedback.clear();
                        clicks.clear();
                        return;
                    case 13:
                        red = (double)(xdisplay-25)/100;
                        rx1=xdisplay-5;
                        rx2=xdisplay+5;
                        createSliders();
                        feedback.clear();
                        clicks.clear();
                        return;
                }
            }
        }
        if(buttons[0]->getActive())
        {
            feedbacks(x,xdisplay, ydisplay);
            if(clicks.size() == 4)
            {
                feedback.clear();
                shapes_vector.push_back(new Rectangle(clicks[0], clicks[1], clicks[2], clicks[3], red, green, blue, solid));
                clicks.clear();
            }
        }
        else if(buttons[1]->getActive())
        {
            feedbacks(x,xdisplay, ydisplay);
            if(clicks.size() == 4)
            {
                feedback.clear();
                shapes_vector.push_back(new Circle(clicks[0], clicks[1], clicks[2], clicks[3], red, green, blue, solid));
                clicks.clear();
            }
        }
        else if(buttons[2]->getActive())
        {
            feedbacks(x,xdisplay, ydisplay);
            if(clicks.size() == 6)
            {
                feedback.clear();
                shapes_vector.push_back(new Triangle(clicks[0], clicks[1], clicks[2], clicks[3], clicks[4], clicks[5], red, green, blue, solid));
                clicks.clear();
            }
        }
        else if(buttons[10]->getActive())
        {
            feedbacks(x,xdisplay, ydisplay);
            if(clicks.size() == 10)
            {
                feedback.clear();
                shapes_vector.push_back(new Pentagon(clicks[0], clicks[1], clicks[2], clicks[3], clicks[4], clicks[5], clicks[6], clicks[7], clicks[8],clicks[9], red, green, blue, solid));
                clicks.clear();
            }
        }
    }
  if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
    {
    }
  if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) 
    {
    }
  if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) 
    {
    }
  glutPostRedisplay();
}

// Your initialization code goes here.
void InitializeMyStuff()
{
    red = 0.0;
    green = 0.0;
    blue = 0.0;
    rx1 = 25;
    gx1 = 25;
    bx1 = 25;
    rx2 = 35;
    gx2 = 35;
    bx2 = 35;
    createButtons();
    createSliders();
}


int main(int argc, char **argv)
{
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(screen_x, screen_y);
  glutInitWindowPosition(50, 50);

  int fullscreen = 0;
  if (fullscreen) 
    {
      glutGameModeString("800x600:32");
      glutEnterGameMode();
    } 
  else 
    {
      glutCreateWindow("Shape Builder 2014");
    }

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);

  glColor3d(0,0,0); // forground color
  glClearColor(1, 1, 1, 0); // background color
  InitializeMyStuff();

  glutMainLoop();

  return 0;
}
