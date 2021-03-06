// Cody Brown
// Chess animation starter kit.

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <vector>
#include <string.h>
#include <fstream>
#include <iostream>
using namespace std;
#include <GLUT/glut.h>
#include "graphics.h"
#include "ctime"

void DrawCircle(double x1, double y1, double radius)
{
    glBegin(GL_LINE_LOOP);
    for(int i=0; i<32; i++)
    {
        double theta = (double)i/32.0 * 2.0 * 3.1415926;
        double x = x1 + radius * cos(theta);
        double y = y1 + radius * sin(theta);
        glVertex2d(x, y);
    }
    glEnd();
}
enum PIECES {PAWN=10, ROOK, KNIGHT, BISHOP, QUEEN, KING};
// Global Variables
// Some colors you can use, or make your own and add them
// here and in graphics.h
GLdouble redMaterial[] = {0.7, 0.1, 0.2, 1.0};
GLdouble greenMaterial[] = {0.1, 0.7, 0.4, 1.0};
GLdouble brightGreenMaterial[] = {0.1, 0.9, 0.1, 1.0};
GLdouble blueMaterial[] = {0.1, 0.2, 0.7, 1.0};
GLdouble whiteMaterial[] = {1.0, 1.0, 1.0, 1.0};
bool first = false;
double screen_x = 1000;
double screen_y = 500;


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

// Given the three triangle points x[0],y[0],z[0],
//		x[1],y[1],z[1], and x[2],y[2],z[2],
//		Finds the normal vector n[0], n[1], n[2].
void FindTriangleNormal(double x[], double y[], double z[], double n[])
{
	// Convert the 3 input points to 2 vectors, v1 and v2.
	double v1[3], v2[3];
	v1[0] = x[1] - x[0];
	v1[1] = y[1] - y[0];
	v1[2] = z[1] - z[0];
	v2[0] = x[2] - x[0];
	v2[1] = y[2] - y[0];
	v2[2] = z[2] - z[0];
	
	// Take the cross product of v1 and v2, to find the vector perpendicular to both.
	n[0] = v1[1]*v2[2] - v1[2]*v2[1];
	n[1] = -(v1[0]*v2[2] - v1[2]*v2[0]);
	n[2] = v1[0]*v2[1] - v1[1]*v2[0];

	double size = sqrt(n[0]*n[0] + n[1]*n[1] + n[2]*n[2]);
	n[0] /= -size;
	n[1] /= -size;
	n[2] /= -size;
}

// Loads the given data file and draws it at its default position.
// Call glTranslate before calling this to get it in the right place.
void DrawPiece(char filename[])
{
	// Try to open the given file.
	char buffer[200];
	ifstream in(filename);
	if(!in)
	{
		cerr << "Error. Could not open " << filename << endl;
		exit(1);
	}

	double x[100], y[100], z[100]; // stores a single polygon up to 100 vertices.
	int done = false;
	int verts = 0; // vertices in the current polygon
	int polygons = 0; // total polygons in this file.
	do
	{
		in.getline(buffer, 200); // get one line (point) from the file.
		int count = sscanf(buffer, "%lf, %lf, %lf", &(x[verts]), &(y[verts]), &(z[verts]));
		done = in.eof();
		if(!done)
		{
			if(count == 3) // if this line had an x,y,z point.
			{
				verts++;
			}
			else // the line was empty. Finish current polygon and start a new one.
			{
				if(verts>=3)
				{
					glBegin(GL_POLYGON);
					double n[3];
					FindTriangleNormal(x, y, z, n);
					glNormal3dv(n);
					for(int i=0; i<verts; i++)
					{
						glVertex3d(x[i], y[i], z[i]);
					}
					glEnd(); // end previous polygon
					polygons++;
					verts = 0;
				}
			}
		}
	}
	while(!done);

	if(verts>0)
	{
		cerr << "Error. Extra vertices in file " << filename << endl;
		exit(1);
	}

}

// NOTE: Y is the UP direction for the chess pieces.
double eyex = 4500;
double eyey = 8000;
double eyez = -4000;
double eyex2 = 4500;
double eyey2 = 0;
double eyez2 = 4000;
double eye[3] = {eyex, eyey, eyez}; // pick a nice vantage point.
double at[3]  = {eyex2, eyey2, eyez2};



//
// GLUT callback functions
//
void RatioSet(double currentTime, double time1, double time2, double &value, double value1, double value2)
{
    double ratio = (currentTime - time1) / (time2 - time1);
    if (ratio < 0)
    {
        ratio = 0;
    }
    if (ratio > 1)
    {
        ratio = 1;
    }
    value = value1 + ratio*(value2 - value1);
}

void DrawBoard()
{
    //    glBegin(GL_QUADS);
    //    glVertex3d(0, -1000, 0);
    //    glVertex3d(0, -1000, 9000);
    //    glVertex3d(9000, -1000, 9000);
    //    glVertex3d(9000, -1000, 0);
    //    glEnd();
    GLfloat black[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat brown[] = {0.89, 0.53, 0.27, 1.0};
    bool oddCol = false;
    bool oddRow = false;
    for (int row=500; row<10000; row+=1000)
    {
        for (int col=500; col<10000; col+=1000)
        {
            if (col == 500 || row == 500 || col == 9500 || row == 9500) {
                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown);
            }
            else if (!oddRow)
            {
                // even row
                if (!oddCol)
                {
                    // even col
                    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
                    
                }
                else
                {
                    // odd col
                    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
                }
            }
            else
            {
                // odd row
                if (!oddCol)
                {
                    // even col
                    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
                    
                }
                else
                {
                    // odd col
                    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
                }
            }
            glBegin(GL_POLYGON);
            glNormal3f(0, 1, 0);
            glVertex3d(col, 0, row);
            glVertex3d(col, 0, row + 1000);
            glVertex3d(col + 1000, 0, row + 1000);
            glVertex3d(col + 1000, 0, row);
            glEnd();
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown);
            glBegin(GL_POLYGON);
            glNormal3f(0, 0, -1);
            glVertex3d(col, 0, row);
            glVertex3d(col, -1000, row);
            glVertex3d(col + 1000, -1000, row);
            glVertex3d(col + 1000, 0, row);
            glEnd();
            
            oddCol = !oddCol;
        }
        oddRow = !oddRow;
    }
}
void DrawSphere(float x, float y, float z, float radius)
{
    glPushMatrix();
    
    glTranslatef(x,y,z);
    int slices = 40;
    int stacks = 40;
    glutSolidSphere(radius, slices, stacks);
    glPopMatrix();
}
// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{
    static clock_t start = clock();
    clock_t finish = clock();
    double currentTime = ((double)(finish - start) / CLOCKS_PER_SEC)*10;
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2],  at[0], at[1], at[2],  0,1,0); // Y is up!
    DrawBoard();
	// Set the color for one side (white), and draw its 16 pieces.
	GLfloat mat_amb_diff1[] = {0.9, 0.9, 0.9, 1.0};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff1);
    GLfloat red[] = {1.0, 0.0, 0.0, 1.0};
    GLfloat black[] = {0.5, 0.5, 0.5, 1.0};
    glPushMatrix();
    double rook_x = 2000;
    double rook_x2 = 2400;
    double rook_y = 0;
    double rook_z = 2000;
    double rook_z2 = 2600;
    double rook_z3 = 3600;
    double bomb_z = 4800;
    double bomb_y = 420;
    double rook_x3 = 5400;
    double rook_y2 = 400;
    double bomb_size = 1;
    double angle =0;
    double angle1 =90;
    double site_x = 2400;
    double site_z = 6000;
    RatioSet(currentTime, 2.0, 5.0, rook_y, 0, 400);
    RatioSet(currentTime, 2.0, 5.0, rook_x, 2000, 2400);
    RatioSet(currentTime, 2.0, 5.0, rook_z, 2000, 2600);
    
    
    if (currentTime > 5.0 && currentTime < 8.0)
    {
        RatioSet(currentTime, 5.0, 8.0, rook_z2, 2600, 3600);
        glTranslated(rook_x, rook_y, rook_z2);
        glRotated(90, 1, 0, 0);
    }
    else if (currentTime > 8.0 && currentTime < 18)
    {
        //std::cout<<8<<std::endl;
        RatioSet(currentTime, 8.0, 15.0, rook_x2, 2400, 5400);
        glTranslated(rook_x2, rook_y, 3600);
        glRotated(angle1, 1, 0, 0);
    }
    else if (currentTime > 18)
    {
        std::cout<<8<<std::endl;
        RatioSet(currentTime, 19.0, 21.0, angle1, 90, 0);
        RatioSet(currentTime, 19.0, 21.0, rook_x3, 5400, 6000);
        RatioSet(currentTime, 19.0, 21.0, rook_y2, 400, 0);
        RatioSet(currentTime, 19.0, 21.0, rook_z3, 3600, 4000);
        glTranslated(rook_x3, rook_y2, rook_z3);
        glRotated(angle1, 1, 0, 0);
    }
    else
    {
    RatioSet(currentTime, 2.0, 5.0, angle, 0, 90);
    glTranslatef(rook_x, rook_y, rook_z);
    }
    glRotated(angle, 1, 0, 0);
    glCallList(ROOK);
    glPopMatrix();
    if (currentTime > 15 && currentTime <19)
    {
        if (currentTime< 18) {
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,black);
        }
        else
        {
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,red);
        }
        RatioSet(currentTime, 15.0, 18.0, bomb_z, 4800, 8500);
        RatioSet(currentTime, 16.0, 18.0, bomb_y, 420, 0);
        RatioSet(currentTime, 18.0, 19.0, bomb_size, 200, 3000);
        DrawSphere(5400, bomb_y, bomb_z, bomb_size);
    }
    
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff1);
    glPushMatrix();
    
    glTranslatef(3000, 0,2000);
    glCallList(KNIGHT);
    glPopMatrix();
    
	glPushMatrix();
	glTranslatef(4000, 0, 2000);
	glCallList(BISHOP);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5000, 0, 2000);
	glCallList(KING);
	glPopMatrix();

	glPushMatrix();
    double queen_z = 2000;
    //RatioSet(currentTime, 2.0, 4.0, queen_z, 2000, 5000);
	glTranslatef(6000, 0, queen_z);
	glCallList(QUEEN);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7000, 0, 2000);
	glCallList(BISHOP);
	glPopMatrix();
    
    glPushMatrix();
    glTranslatef(8000, 0, 2000);
    glCallList(KNIGHT);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(9000, 0, 2000);
    glCallList(ROOK);
    glPopMatrix();
    if (first && currentTime > 5)
    {
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,red);
        
        glPushMatrix();
        if (currentTime>8) {
            RatioSet(currentTime, 8.0, 15.0, site_x, 2400, 5400);
             glTranslated(site_x, 540, 7000);
        }
        else
        {
            RatioSet(currentTime, 5.0, 8.0, site_z, 6000, 7000);
            glTranslated(2400, 540, site_z);
        }
        if (currentTime < 18) {
            DrawCircle(0, 0, 100);

        }
        glPopMatrix();

        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff1);
    }
    
    
    glPushMatrix();
    double p1_z = 3000;
    double p1_x = 2000;
    if (currentTime > 8.0)
    {
        if (first) {
            RatioSet(currentTime, 8.0, 15.0, eyex2, 2000, 5000);
            eye[0] = eyex2;
            at[0] = eyex2;
            
        }
        RatioSet(currentTime, 8.0, 15.0, p1_x, 2000, 5000);
        glTranslatef(p1_x, 0, 4000);
    }
    else
    {
    RatioSet(currentTime, 5.0, 8.0, p1_z, 3000, 4000);
    if (first)
    {
    RatioSet(currentTime, 5.0, 8.0, eyez, 3000, 4000);
    eye[2]=eyez;
    }
    glTranslatef(2000, 0, p1_z);
    }
    if (!first) {
         glCallList(PAWN);
    }
   
    glPopMatrix();
    
    for(int x=3000; x<=9000; x+=1000)
    {
        glPushMatrix();
        glTranslatef(x, 0, 3000);
        glCallList(PAWN);
        glPopMatrix();
    }
    double piece_y = 0;

    RatioSet(currentTime, 18.0, 20.0, piece_y, 0,4000);
    // Set the color for one side (black), and draw its 16 pieces.
    GLfloat mat_amb_diff2[] = {0.3, 0.3, 0.3, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff2);
    double piece_r = 2000;
    RatioSet(currentTime, 18.0, 20.0, piece_r, 2000, -4000);
    glPushMatrix();
    glTranslatef(piece_r, piece_y, 9000);
    glCallList(ROOK);
    glPopMatrix();
    double piece_k = 3000;
    RatioSet(currentTime, 18.0, 20.0, piece_k, 3000, -4000);
    glPushMatrix();
    glTranslatef(piece_k, piece_y, 9000);
    glRotated(piece_k, 0, 1, 0);
    glCallList(KNIGHT);
    glPopMatrix();
    double piece_b = 4000;
    RatioSet(currentTime, 18.0, 20.0, piece_b, 4000, -2000);
    glPushMatrix();
    glTranslatef(piece_b, piece_y, 9000);
    glCallList(BISHOP);
    glPopMatrix();
    double piece_ki = 5000;
    RatioSet(currentTime, 18.0, 20.0, piece_ki, 5000, -2000);
    glPushMatrix();
    glTranslatef(piece_ki, piece_y, 9000);
    glCallList(KING);
    glPopMatrix();
    
    glPushMatrix();
    double piece_q = 6000;
    RatioSet(currentTime, 18.0, 20.0, piece_q, 6000, 10000);
    glTranslatef(piece_q, piece_y, 9000);
    glCallList(QUEEN);
    glPopMatrix();
    
    double piece_b2 = 7000;
    RatioSet(currentTime, 18.0, 20.0, piece_b2, 7000, 10000);
    glPushMatrix();
    glTranslatef(piece_b2, piece_y, 9000);
    glCallList(BISHOP);
    glPopMatrix();
    double piece_k2 = 8000;
    RatioSet(currentTime, 18.0, 20.0, piece_k2, 8000, 13000);
    glPushMatrix();
    glTranslatef(piece_k2, piece_y, 9000);
    glCallList(KNIGHT);
    glPopMatrix();
    double piece_r2 = 9000;
    RatioSet(currentTime, 18.0, 20.0, piece_b2, 9000, 13000);
    glPushMatrix();
    glTranslatef(piece_b2, piece_y, 9000);
    glCallList(ROOK);
    glPopMatrix();
    vector<double> X;

	for(double x=2000; x<=9000; x+=1000)
	{
        X.push_back(x);
		
	}
    for (int i=0; i<X.size(); i++)
    {
        if (i<5)
        {
            RatioSet(currentTime, 18.0, 20.0, X[i], X[i], -4000);
            glPushMatrix();
            glTranslatef(X[i], piece_y, 8000);
            glCallList(PAWN);
            glPopMatrix();
        }
        else
        {
            RatioSet(currentTime, 18.0, 20.0, X[i], X[i], 13000);
            glPushMatrix();
            glTranslatef(X[i], piece_y, 8000);
            glCallList(PAWN);
            glPopMatrix();
        }
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
        case 'f':
            if (first) {
                first = false;
                eyex = 4500;
                eyey = 8000;
                eyez = -4000;
                eyey2 = 0;
                eyez2 = 4000;
                eye[0] = eyex;
                eye[1] = eyey;
                eye[2] = eyez;
                at[0] = eyex;
                at[1] = eyey2;
                at[2] = eyez2;
                break;
            } else {
                first = true;
                eyex = 2000;
                eyex2 = 2000;
                eyey = 500;
                eyez = 3000;
                eyey2 = 1000;
                eyez2 = 8000;
                
                eye[0] = eyex;
                eye[1] = eyey;
                eye[2] = eyez;
                at[0] = eyex2;
                at[1] = eyey2;
                at[2] = eyez2;
                break;
            }
        case 'q':
            case 27: // escape character means to quit the program
                exit(0);
                break;
		default:
			return; // if we don't care, return without glutPostRedisplay()
	}

	glutPostRedisplay();
}



void SetPerspectiveView(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double aspectRatio = (GLdouble) w/(GLdouble) h;
	gluPerspective( 
	/* field of view in degree */ 42.0,
	/* aspect ratio */ aspectRatio,
	/* Z near */ 100, /* Z far */ 30000.0);
	glMatrixMode(GL_MODELVIEW);
}

// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape(int w, int h)
{
	screen_x = w;
	screen_y = h;

	// Set the pixel resolution of the final picture (Screen coordinates).
	glViewport(0, 0, w, h);

	SetPerspectiveView(w,h);

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
void PieceList(PIECES e, char filename[])
{
    glNewList(e, GL_COMPILE);
    DrawPiece(filename);
    glEndList();
}
// Your initialization code goes here.
void InitializeMyStuff()
{
	// set material's specular properties
	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_shininess[] = {50.0};
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	// set light properties
	GLfloat light_position[] = {eye[0], eye[1], eye[2],1};
	GLfloat white_light[] = {1,1,1,1};
	GLfloat low_light[] = {.3,.3,.3,1};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); // position first light
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light); // specify first light's color
	glLightfv(GL_LIGHT0, GL_SPECULAR, low_light);

	glEnable(GL_DEPTH_TEST); // turn on depth buffering
	glEnable(GL_LIGHTING);	// enable general lighting
	glEnable(GL_LIGHT0);	// enable the first light.
    
    PieceList(PAWN, "PAWN.POL");
    PieceList(BISHOP, "BISHOP.POL");
    PieceList(ROOK, "ROOK.POL");
    PieceList(KING, "KING.POL");
    PieceList(KNIGHT, "KNIGHT.POL");
    PieceList(QUEEN, "QUEEN.POL");
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screen_x, screen_y);
	glutInitWindowPosition(10, 10);

	int fullscreen = 0;
	if (fullscreen) 
	{
		glutGameModeString("800x600:32");
		glutEnterGameMode();
	} 
	else 
	{
		glutCreateWindow("Gears Of Chess");
	}

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);

	glClearColor(1,1,1,1);	
	InitializeMyStuff();

	glutMainLoop();

	return 0;
}
