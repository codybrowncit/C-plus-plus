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
#include <ctime>
#include <cstdlib>
#include "Pentagon.h"
#include "Triangle.h"
#include "Circle.h"
#include "Spiral.h"
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
std::vector <Shape*> shapes;
int num = 10;
double screen_x = 70*num;
double screen_y = 50*num;

bool solid=true;
const double COLLISION_FRICTION = .99999;

struct vectortype
{
    double x;
    double y;
};

void Collide(int p1, int p2, std::vector <Circle*> particles)
{
    vectortype en; // Center of Mass coordinate system, normal component
    vectortype et; // Center of Mass coordinate system, tangential component
    vectortype u[2]; // initial velocities of two particles
    vectortype um[2]; // initial velocities in Center of Mass coordinates
    double umt[2]; // initial velocities in Center of Mass coordinates, tangent component
    double umn[2]; // initial velocities in Center of Mass coordinates, normal component
    vectortype v[2]; // final velocities of two particles
    double m[2];	// mass of two particles
    double M; // mass of two particles together
    vectortype V; // velocity of two particles together
    double size;
    int i;
    double xdif = particles[p1]->getnextx() - particles[p2]->getnextx();
    double ydif = particles[p1]->getnexty() - particles[p2]->getnexty();
    // set Center of Mass coordinate system
    size=sqrt(xdif * xdif + ydif * ydif);
    xdif /= size; ydif /= size; // normalize
    en.x = xdif;
    en.y = ydif;
    et.x = ydif;
    et.y =- xdif;
    // set u values
    u[0].x = particles[p1]->getdx();
    u[0].y = particles[p1]->getdy();
    m[0] = particles[p1]->getradius() * particles[p1]->getradius();
    u[1].x = particles[p2]->getdx();
    u[1].y = particles[p2]->getdy();
    m[1] = particles[p2]->getradius() * particles[p2]->getradius();
    // set M and V
    M=m[0] + m[1];
    V.x = (u[0].x * m[0] + u[1].x * m[1]) / M;
    V.y = (u[0].y * m[0] + u[1].y * m[1]) / M;
    // set um values
    um[0].x = m[1] / M * (u[0].x - u[1].x);
    um[0].y = m[1] / M * (u[0].y - u[1].y);
    um[1].x = m[0] / M * (u[1].x - u[0].x);
    um[1].y = m[0] / M * (u[1].y - u[0].y);
    // set umt and umn values
    for( i = 0; i < 2; i++)
    {
        umt[i] = um[i].x * et.x + um[i].y * et.y;
        umn[i] = um[i].x * en.x + um[i].y * en.y;
    }
    // set v values
    for(i = 0; i < 2; i++)
    {
        v[i].x = umt[i] * et.x - umn[i] * en.x + V.x;
        v[i].y = umt[i] * et.y - umn[i] * en.y + V.y;
    }
    // reset particle values
    particles[p1]->setdx(v[0].x * COLLISION_FRICTION);
    particles[p1]->setdy(v[0].y * COLLISION_FRICTION);
    particles[p2]->setdx(v[1].x * COLLISION_FRICTION);
    particles[p2]->setdy(v[1].y * COLLISION_FRICTION);
} /* Collide */

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

void drawShapes()
{
    for(int i = 0; i < shapes.size(); i++)
    {
        shapes[i]->draw();
    }
}

//
// GLUT callback functions
//

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawShapes();
    glutPostRedisplay();
    glutSwapBuffers();
}


// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard(unsigned char c, int x, int y)
{
  switch (c) 
    {
        case '3':
            shapes[0]=new Circle(300, 300, 400, 400, 1, 0, 0, solid, 3.0);
            
            break;
        case '4':
            shapes[0]=new Circle(300, 300, 400, 400, 1, 0, 0, solid, 4.0);
            
            break;
        case '5':
            shapes[0]=new Circle(300, 300, 400, 400, 1, 0, 0, solid, 5.0);
            
            break;
        case '6':
            shapes[0]=new Circle(300, 300, 400, 400, 1, 0, 0, solid, 6.0);
            
            break;
        case '7':
            shapes[0]=new Circle(300, 300, 400, 400, 1, 0, 0, solid, 7.0);
            
            break;
        case '8':
            shapes[0]=new Circle(300, 300, 400, 400, 1, 0, 0, solid, 8.0);
            
            break;
        case '9':
            shapes[0]=new Circle(300, 300, 400, 400, 1, 0, 0, solid, 9.0);
            
            break;
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

        shapes.push_back(new Circle(300, 300, 400, 400, 1, 0, 0, solid, 6.0));
        shapes.push_back(new Spiral(200,200, 210, 210, 0,1,0,solid));
}

int main(int argc, char **argv)
{
  std::srand(time(0));
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
      glutCreateWindow("Runaway Shapes!");
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
