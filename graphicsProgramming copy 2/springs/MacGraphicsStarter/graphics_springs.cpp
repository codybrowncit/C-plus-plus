// CS 3600 Graphics Programming
// Spring, 2002
// Program #4 - SpringMan
// This program simulates various forces between particles, such as springs.

#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cmath>
#include <string.h>
#include <fstream>
#include <iostream>
using namespace std;
#include <vector>
#include "graphics.h"
#include "particle.h"
#include "forces.h"


// Global Variables
// Some colors you can use, or make your own and add them
// here and in graphics.h
GLdouble redMaterial[] = {0.7, 0.1, 0.2, 1.0};
GLdouble greenMaterial[] = {0.1, 0.7, 0.4, 1.0};
GLdouble brightGreenMaterial[] = {0.1, 0.9, 0.1, 1.0};
GLdouble blueMaterial[] = {0.1, 0.2, 0.7, 1.0};
GLdouble whiteMaterial[] = {1.0, 1.0, 1.0, 1.0};

double screen_x = 700;
double screen_y = 500;
vector<Particle*> particles;
vector<Force*> sforces;
vector<Force*> dforces;
vector<Force*> gforces;

// The particle system.
ParticleSystem PS;

// 
// Functions that draw basic primitives
//
void DrawCircle(double x1, double y1, double radius)
{
	glBegin(GL_POLYGON);
	for(int i=0; i<32; i++)
	{
		double theta = (double)i/32.0 * 2.0 * 3.1415926;
		double x = x1 + radius * cos(theta);
		double y = y1 + radius * sin(theta);
		glVertex2d(x, y);
	}
    
	glEnd();
}

void DrawLine(double x1, double y1, double x2, double y2)
{
	glBegin(GL_LINES);
	glVertex2d(x1,y1);
	glVertex2d(x2,y2);
	glEnd();
}

void DrawRectangle(double x1, double y1, double x2, double y2)
{
	glBegin(GL_QUADS);
	glVertex2d(x1,y1);
	glVertex2d(x2,y1);
	glVertex2d(x2,y2);
	glVertex2d(x1,y2);
	glEnd();
}

void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3)
{
	glBegin(GL_TRIANGLES);
	glVertex2d(x1,y1);
	glVertex2d(x2,y2);
	glVertex2d(x3,y3);
	glEnd();
}

// Outputs a string of text at the specified location.
void text_output(double x, double y, char *string)
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


//
// GLUT callback functions
//

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.

void display(void)
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3dv(whiteMaterial);


	//EulerStep(PS, DeltaT);
	//MidpointStep(PS, DeltaT);
   // double DeltaT = 0.5;
    double delta = PS.getDeltaT();
	RungeKuttaStep(PS, delta);

	int N = PS.GetNumParticles();
	int NF = PS.GetNumForces();

	// Check Resulting particles for wall collisions
	for(i=0; i<N; i++)
	{
		Particle * p = PS.GetParticle(i);
		double radius = p->GetRadius();
		double x = p->GetPositionx();
		double y = p->GetPositiony();
		double xDir = p->GetDirectionx();
		double yDir = p->GetDirectiony();

		// bounce off left wall
		if(x - radius < 0)
		{
			p->SetPositionx(radius);
			p->SetDirectionx(fabs(xDir));
		}

		// bounce off right wall
		if(x + radius > screen_x)
		{
			p->SetPositionx(screen_x - radius);
			p->SetDirectionx(-fabs(xDir));
		}

		// bounce off bottom wall
		if(y - radius < 0)
		{
			p->SetPositiony(radius);
			p->SetDirectiony(fabs(yDir));
		}

		// bounce off top wall
		if(y + radius > screen_y)
		{
			p->SetPositiony(screen_y - radius);
			p->SetDirectiony(-fabs(yDir));
		}
	}


	// Draw Spring Forces as edges
	for(i=0; i<NF; i++)
	{
		Force * f = PS.GetForce(i);
		if(f->Type() == SPRING_FORCE)
		{
			SpringForce * sf = (SpringForce*)f;
			Particle * p1 = sf->GetParticle1();
			Particle * p2 = sf->GetParticle2();
            double *material = sf->getMaterial();
			glColor3dv(material);
			DrawLine(p1->GetPositionx(), p1->GetPositiony(),  p2->GetPositionx(), p2->GetPositiony());
		}
	}

	// Draw Particles
	for(i=0; i<N; i++)
	{
		Particle * p = PS.GetParticle(i);
		double radius = p->GetRadius();

		double thePos[DIM];
		p->GetPosition(thePos);
		if(p->GetAnchored())
			glColor3dv(redMaterial);
		else
			glColor3dv(whiteMaterial);
		DrawCircle(thePos[0], thePos[1], radius);
	}

	glutSwapBuffers();
	glutPostRedisplay();
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
	screen_x = w;
	screen_y = h;

	// Set the pixel resolution of the final picture (Screen coordinates).
	glViewport(0, 0, w, h);

	// go into 2D mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Set the world coordinates.
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);

}

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse(int mouse_button, int state, int x, int y)
{
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

void InitParticles()
{
    double starting_length = 100.00;
    int count = 0;
    string kind, anchored;
    double x, y, pos_temp, dir_temp, r_temp, spring_constant, damping_constant, rest_length, friction_temp, g1, g2, delta, r, g, b;
    int p1, p2;
    bool anchored_temp;
    cout << "Please enter a text file name"<<std::endl;
    char file_name[30];
    cin >> file_name;
    ifstream fin(file_name);
    //ifstream fin("data.txt");
    while (fin >> kind)
    {
        if (kind == "DeltaT")
        {
            fin >> delta;
            PS.setDeltaT(delta);
        }
        if (kind == "Particle")
        {
            fin >> x >> y >> pos_temp >> dir_temp >> r_temp;
            fin >> anchored;
            if (anchored == "false")
            {
                anchored_temp = false;
            }
            else if(anchored == "true")
            {
                anchored_temp = true;
            }
            particles.push_back(new Particle(x, y, pos_temp, dir_temp, r_temp, anchored_temp));
            PS.AddParticle(particles[count]);
            count++;
        }

        if (kind == "SpringForceDefault")
        {
            fin >> p1 >> p2 >> spring_constant >> damping_constant;
            PS.AddForce(new SpringForce(r, g, b, particles[p1-1], particles[p2-1], spring_constant, damping_constant));
        }
        if (kind == "SpringForce")
        {
            fin >> r >> g >> b >> p1 >> p2 >> spring_constant >> damping_constant >> rest_length;
            rest_length *= starting_length;
            PS.AddForce(new SpringForce(r, g, b, particles[p1-1], particles[p2-1], spring_constant, damping_constant, rest_length));
        }
        if (kind == "DragForce")
        {
            fin >> friction_temp;
            PS.AddForce(new DragForce(friction_temp, &PS));
        }
        if (kind == "GravityForce")
        {
            fin >> g1 >> g2;
            double gravity[DIM] = {g1, g2};
            PS.AddForce(new GravityForce(gravity, &PS));
        }
    }
}

// Your initialization code goes here.
void InitializeMyStuff()
{
	InitParticles();
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
		glutCreateWindow("Springy Shapes");
	}

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);

	glClearColor(.3,.3,.3,0);	
	InitializeMyStuff();

	glutMainLoop();

	return 0;
}
