#include "maze.h"
#include "rat.h"
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <GLUT/glut.h>


// Global Variables (Only what you need!)
double screen_x = 700;
double screen_y = 500;
Maze maze;
Rat rat;
bool left_button_down = false;
bool middle_button_down = false;
bool right_button_down = false;
void drawRectangle(double x1, double y1, double x2, double y2)
{
    glBegin(GL_QUADS);
    glVertex2d(x1,y1);
    glVertex2d(x2,y1);
    glVertex2d(x2,y2);
    glVertex2d(x1,y2);
    glEnd();
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
    maze.draw();
    //if in perspective view
    //glLookAt(x,y,z x,y,z x,y,z);
    //glEndable(GL_DEPTH_TEST):
    glColor3d(1,0,0);
    std::string start = "START";
    std::string end = "FINISH";
    
    DrawText(0, -.5, &start);
    DrawText(COL-1,ROW+.5, &end);
    double x = rat.get_x();
    double y = rat.get_y();
    rat.draw();
    if (left_button_down)
    {
        rat.turnLeft(dt);
    }
    if (right_button_down)
    {
        rat.turnRight(dt);
    }
    if (middle_button_down)
    {
        rat.scurry(dt, maze);
    }
    if ((int)x == ROW-1 && (int)y == COL)
    {
        std::string win = "You Win!";
        DrawText(1.5, 1.5, &win);
    }
	glutSwapBuffers();
}




// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard(unsigned char c, int x, int y)
{
	switch (c) 
	{
        case 'a':
            right_button_down = false;
            left_button_down = true;
            middle_button_down = false;
            break;
        case 'd':
            left_button_down = false;
            right_button_down = true;
            middle_button_down = false;
            break;
        case 'w':
            left_button_down = false;
            right_button_down = false;
            middle_button_down = true;
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
	gluOrtho2D(-.5, ROW+.5, -1.5, COL+1.5);
	glMatrixMode(GL_MODELVIEW);

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
		glutCreateWindow("2D Maze");
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
