
#include "person.h"
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <GLUT/glut.h>


// Global Variables (Only what you need!)
double screen_x = 1000;
double screen_y = 1000;
Terrain terrain;
Person person;
bool left_button_down = false;
bool middle_button_down = false;
bool right_button_down = false;



void SetTopView(int w, int h)
{
    // go into 2D mode
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double world_margin_x = 1.5;
    double world_margin_y = 1.5;
    gluOrtho2D(-world_margin_x, ROW+world_margin_x,
               -world_margin_y, COL+world_margin_y);
    glMatrixMode(GL_MODELVIEW);
}

void SetPerspectiveView(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double aspectRatio = (GLdouble) w/(GLdouble) h;
    gluPerspective(
                   /* field of view in degree */ 38.0,
                   /* aspect ratio */ aspectRatio,
                   /* Z near */ .1, /* Z far */ 100.0);
    glMatrixMode(GL_MODELVIEW);
}

double GetDeltaTime()
{
    static clock_t start_time = clock();
    static int current_frame = 0;
    clock_t current_time = clock();
    current_frame += 1;
    double total_time = double(current_time - start_time)/CLOCKS_PER_SEC;
    if (total_time == 0)
        total_time = .001;
    double frames_per_second = (double)current_frame / total_time;
    double DT = 1.0 / frames_per_second;
    return DT;
}

//


// Outputs a string of text at the specified location.
void DrawText(double x, double y, std::string *stringer)
{
	void *font = GLUT_BITMAP_9_BY_15;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
	
	int len, i;
	glRasterPos2d(x, y);
    len = stringer->length();
	for (i = 0; i < len; i++) 
	{
		glutBitmapCharacter(font, stringer->at(i));
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    double dt = GetDeltaTime();
    terrain.draw();
    if(terrain.current_view == terrain.perspective_view)
    {
        glEnable(GL_DEPTH_TEST);
        glLoadIdentity();
        gluLookAt(-3,-3,7,  3,3,0,  0,0,1);
    }
    else if(terrain.current_view == terrain.top_view)
    {
        glDisable(GL_DEPTH_TEST);
        glLoadIdentity();
    }
    else // current_view == eye_view
    {
        double HOVER_HEIGHT = .2;
        glEnable(GL_DEPTH_TEST);
        glLoadIdentity();
        double z_level = 2.0;
        double x = person.get_x();
        double y = person.get_y();
        double z = fmax(terrain.get_z(x, y), WATER_HEIGHT)+HOVER_HEIGHT;
        double dx = person.get_dx();
        double dy = person.get_dy();
        double at_x = x + dx;
        double at_y = y + dy;
        double at_z = fmax(terrain.get_z(at_x, at_y), WATER_HEIGHT)+HOVER_HEIGHT;
        gluLookAt(x,y,z,  at_x, at_y, at_z,  0,0,1);
    }
    if (left_button_down)
    {
        person.turnLeft(dt);
    }
    if (right_button_down)
    {
        person.turnRight(dt);
    }
    if (middle_button_down)
    {
        person.move(dt, terrain);
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
        case 'r':
            terrain.current_view = terrain.eye_view;
            SetPerspectiveView(screen_x, screen_y);
            break;
        case 'p':
            terrain.current_view = terrain.perspective_view;
            SetPerspectiveView(screen_x, screen_y);
            break;
        case 't':
            terrain.current_view = terrain.top_view;
            SetTopView(screen_x, screen_y);
            break;
        case 'a':
            right_button_down = false;
            if (left_button_down == true) {
                left_button_down = false;
            }
            else{
            left_button_down = true;
            }
            middle_button_down = false;
            break;
        case 'd':
            left_button_down = false;
            if (right_button_down == true) {
                right_button_down = false;
            }
            else{
                right_button_down = true;
            }
            middle_button_down = false;
            break;
        case 'w':
            left_button_down = false;
            right_button_down = false;
            if (middle_button_down == true) {
                middle_button_down = false;
            }
            else{
                middle_button_down = true;
            }
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

    if(terrain.current_view == terrain.top_view)
    {
        SetTopView(w,h);
    }
    else if(terrain.current_view == terrain.perspective_view)
    {
        SetPerspectiveView(w,h);
    }
    else // current_view == rat_view
    {
        SetPerspectiveView(w,h);
    }

}

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse(int mouse_button, int state, int x, int y)
{
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
        left_button_down =true;
	}
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
	{
        left_button_down =false;
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) 
	{
        middle_button_down =true;
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) 
	{
        middle_button_down =false;
	}
    if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        right_button_down =true;
    }
    if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
    {
        right_button_down =false;
    }
	glutPostRedisplay();
}

// Your initialization code goes here.
void InitializeMyStuff()
{
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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
		glutCreateWindow("3D Maze");
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
