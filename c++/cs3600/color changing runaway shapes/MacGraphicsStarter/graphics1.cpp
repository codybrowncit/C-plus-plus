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
std::vector <Circle*> shapes;
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
    for (int i = 0; i < shapes.size(); i++)
    {
        double gnextX = shapes[i]->getnextx();
        double gnextY = shapes[i]->getnexty();
        double radius = shapes[i]->getradius();
        
        for (int j = i+1; j < shapes.size(); j++)
        {

            double jnextx = shapes[j]->getnextx();
            double jnexty = shapes[j]->getnexty();
            double jradius = shapes[j]->getradius();

            double a = pow((jnextx-gnextX),2);
            double b = pow((jnexty-gnextY),2);
            double distance = sqrt(a+b);
            if (distance < radius+jradius )
            {
                Collide(i, j, shapes);
                double r = std::rand() % 100;
                double g = std::rand() % 100;
                double b = std::rand() % 100;
                r /= 100;
                g /= 100;
                b /= 100;
                double r1 = std::rand() % 100;
                double g1 = std::rand() % 100;
                double b1 = std::rand() % 100;
                r1 /= 100;
                g1 /= 100;
                b1 /= 100;
                shapes[i]->Mgreen = g;
                shapes[i]->Mred = r;
                shapes[i]->Mblue = b;
                shapes[j]->Mgreen = g1;
                shapes[j]->Mred = r1;
                shapes[j]->Mblue = b1;
                
            }
        }
    }
    for (int i = 0; i < shapes.size(); i++)
    {
        double gX = shapes[i]->getx();
        double gY = shapes[i]->gety();
        double gDY = shapes[i]->getdy();
        double gDX = shapes[i]->getdx();
        double gnextX = shapes[i]->getnextx();
        double gnextY = shapes[i]->getnexty();
        double radius = shapes[i]->getradius();
        gX += gDX;
        gY += gDY;
        if (gX-radius <= 0)
        {
            gX = 0;
            gX += radius;

        }
        if (gY-radius <= 0)
        {
            gY = radius;
            
        }
        if (gX+radius >= screen_x)
        {
            gX = screen_x - radius;
        }
        if (gY+radius >= screen_y)
        {
            gY = screen_y - radius;
        }
        
        double r = shapes[i]->getr();
        double g = shapes[i]->getg();
        double b = shapes[i]->getb();
        solid = shapes[i]->getsolid();
        
        if (gnextY-radius > 0)
        {
            gDY -= 1;
        }
        shapes[i] = new Circle(gX, gY, gX+radius, gY, r, g, b, solid);
        if (gnextX+radius >= screen_x)
        {
            gDX = -gDX;
            gDX *= COLLISION_FRICTION;
            double r = std::rand() % 100;
            double g = std::rand() % 100;
            double b = std::rand() % 100;
            r /= 100;
            g /= 100;
            b /= 100;
            shapes[i]->Mgreen = g;
            shapes[i]->Mred = r;
            shapes[i]->Mblue = b;
        }
        if (gnextY+radius >= screen_y)
        {
            gDY = -gDY;
            gDY *= COLLISION_FRICTION;
            double r = std::rand() % 100;
            double g = std::rand() % 100;
            double b = std::rand() % 100;
            r /= 100;
            g /= 100;
            b /= 100;
            shapes[i]->Mgreen = g;
            shapes[i]->Mred = r;
            shapes[i]->Mblue = b;
        }
        if (gnextX-radius <= 0)
        {
            gDX = -gDX;
            gDX *= COLLISION_FRICTION;
            double r = std::rand() % 100;
            double g = std::rand() % 100;
            double b = std::rand() % 100;
            r /= 100;
            g /= 100;
            b /= 100;
            shapes[i]->Mgreen = g;
            shapes[i]->Mred = r;
            shapes[i]->Mblue = b;
        }
        if (gnextY-radius <= 0)
        {
            gDY = -gDY;
            gDY *= COLLISION_FRICTION;
            double r = std::rand() % 100;
            double g = std::rand() % 100;
            double b = std::rand() % 100;
            r /= 100;
            g /= 100;
            b /= 100;
            shapes[i]->Mgreen = g;
            shapes[i]->Mred = r;
            shapes[i]->Mblue = b;
        }

        shapes[i]->setdx(gDX);
        shapes[i]->setdy(gDY);
    }
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

    for (int i = 0; i < num; i++)
    {
        int sol = std::rand() % 2;
        int dir = std::rand() % 2;
        double r = std::rand() % 100;
        double g = std::rand() % 100;
        double b = std::rand() % 100;
        r /= 100;
        g /= 100;
        b /= 100;
        int xsize = screen_x-100;
        int ysize = screen_y-100;
        double radius = (std::rand() % 50);
        double r1 = (std::rand() % (xsize));
        double r2 = (std::rand() % (ysize));
        double r3 = (std::rand() % (5));
        double r4 = (std::rand() % (5));
       
        if (radius < 10)
        {
            radius+=10;
        }
        
        if (r3 == 0)
        {
            r3++;
        }
        if (r4 == 0)
        {
            r4++;
        }
        if (r1+radius > screen_x)
        {
            r1 -= radius;
        }
        if (r2+radius > screen_y)
        {
            r2 -= radius;
        }

        if (r1-radius < 0)
        {
            r1 += radius;
        }
        if (r2-radius < 0)
        {
            r2 += radius;
        }
        double gX = r1;
        double gY = r2;
        double gDX =r3;
        double gDY =r4;
        if (sol == 0)
        {
            solid = true;
        }
        else
        {
            solid = false;
        }
        if (dir == 0)
        {
            gDX = -gDX;
            gDY = -gDY;
        }
        //gDX=0;
        //gDY=0;
        shapes.push_back(new Circle(gX, gY, gX+radius, gY, r, g, b, solid));
        shapes[i]->setdx(gDX);
        shapes[i]->setdy(gDY);
    }
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
