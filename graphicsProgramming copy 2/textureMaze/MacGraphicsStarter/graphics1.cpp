
#include "rat.h"
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <GLUT/glut.h>
#include "Tga.h"

// Global Variables (Only what you need!)
double screen_x = 2000;
double screen_y = 2000;
Maze maze;
Rat rat;
bool left_button_down = false;
bool middle_button_down = false;
bool right_button_down = false;
const int num_textures = 4;
GLuint texName[num_textures];
bool supermouse = false;

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
                   /* Z near */ .1, /* Z far */ 30.0);
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
    maze.draw();
    if(maze.current_view == maze.perspective_view)
    {
        glEnable(GL_DEPTH_TEST);
        glLoadIdentity();
        gluLookAt(-3,-3,7,  3,3,0,  0,0,1);
    }
    else if(maze.current_view == maze.top_view)
    {
        glDisable(GL_DEPTH_TEST);
        glLoadIdentity();
    }
    else // current_view == rat_view
    {
        glEnable(GL_DEPTH_TEST);
        glLoadIdentity();
        double z_level = .25;
        double x = rat.get_x();
        double y = rat.get_y();
        double dx = rat.get_dx();
        double dy = rat.get_dy();
        double at_x = x + dx;
        double at_y = y + dy;
        double at_z = z_level;
        gluLookAt(x,y,z_level,  at_x, at_y, at_z,  0,0,1);
    }
    double x = rat.get_x();
    double y = rat.get_y();
    rat.draw(maze);
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
        rat.scurry(dt, maze, supermouse);
    }
	glutSwapBuffers();
    glutPostRedisplay();
}




// This callback function gets called by the Glut
// system whenever a q is pressed.
void keyboard(unsigned char c, int x, int y)
{
    double ratx = (int)rat.get_x();
    double raty = (int)rat.get_y();
	switch (c)
	{
        case 's':
            supermouse = true;
            break;
        case 'n':
            supermouse = false;
            ratx = (int)rat.get_x();
            raty = (int)rat.get_y();
            ratx += .5;
            raty += .5;
            std::cout<<ratx<<" "<<raty<<std::endl;
            rat.set_x(ratx);
            rat.set_y(raty);
            break;
        case 'r':
            maze.current_view = maze.rat_view;
            SetPerspectiveView(screen_x, screen_y);
            break;
        case 'p':
            maze.current_view = maze.perspective_view;
            SetPerspectiveView(screen_x, screen_y);
            break;
        case 't':
            maze.current_view = maze.top_view;
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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(maze.current_view == maze.top_view)
    {
        SetTopView(w,h);
    }
    else if(maze.current_view == maze.perspective_view)
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

gliGenericImage *readTgaImage(char *filename)
{
    FILE *file;
    gliGenericImage *image;
    
    file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error: could not open \"%s\"\n", filename);
        return NULL;
    }
    image = gliReadTGA(file, filename);
    fclose(file);
    if (image == NULL) {
        printf("Error: could not decode file format of \"%s\"\n", filename);
        return NULL;
    }
    return image;
}

// Return true if h is a perfect power of 2 (up to 4096)
bool PowerOf2(int h)
{
    if(h!= 2 && h!=4 && h!=8 && h!=16 && h!=32 && h!=64 && h!=128 &&
       h!=256 && h!=512 && h!=1024 && h!=2048 && h!=4096)
        return false;
    else
        return true;
}

// Generic image loader code.
gliGenericImage *readImage(char *filename)
{
    size_t size = strlen(filename);
    if(toupper(filename[size-3]) == 'T' && toupper(filename[size-2]) == 'G' && toupper(filename[size-1]) == 'A')
    {
        gliGenericImage * result = readTgaImage(filename);
        if(!result)
        {
            std::cerr << "Error opening " << filename << std::endl;
            exit(1);
        }
        return result;
    }
    else
    {
        std::cerr << "Unknown Filetype!\n";
        exit(1);
    }
}

// This resets the edges of the texture image to a given "border color".
// You must call this for clamped images that do not take up the whole polygon.
// Otherwise, the texture edges will smear outward across the rest
// of the polygon.
void SetBorder(gliGenericImage * image)
{
    // set a border color.
    unsigned int border_r=50;
    unsigned int border_g=50;
    unsigned int border_b=255;
    int x,y;
    y=0;
    for(x=0; x<image->width; x++)
    {
        image->pixels[ 3*(y*image->width + x) + 0]=border_r;
        image->pixels[ 3*(y*image->width + x) + 1]=border_g;
        image->pixels[ 3*(y*image->width + x) + 2]=border_b;
    }
    y=1;
    for(x=0; x<image->width; x++)
    {
        image->pixels[ 3*(y*image->width + x) + 0]=border_r;
        image->pixels[ 3*(y*image->width + x) + 1]=border_g;
        image->pixels[ 3*(y*image->width + x) + 2]=border_b;
    }
    y=image->height-1;
    for(x=0; x<image->width; x++)
    {
        image->pixels[ 3*(y*image->width + x) + 0]=border_r;
        image->pixels[ 3*(y*image->width + x) + 1]=border_g;
        image->pixels[ 3*(y*image->width + x) + 2]=border_b;
    }
    y=image->height-2;
    for(x=0; x<image->width; x++)
    {
        image->pixels[ 3*(y*image->width + x) + 0]=border_r;
        image->pixels[ 3*(y*image->width + x) + 1]=border_g;
        image->pixels[ 3*(y*image->width + x) + 2]=border_b;
    }
    
    x=0;
    for(y=0; y<image->height; y++)
    {
        image->pixels[ 3*(y*image->width + x) + 0]=border_r;
        image->pixels[ 3*(y*image->width + x) + 1]=border_g;
        image->pixels[ 3*(y*image->width + x) + 2]=border_b;
    }
    x=1;
    for(y=0; y<image->height; y++)
    {
        image->pixels[ 3*(y*image->width + x) + 0]=border_r;
        image->pixels[ 3*(y*image->width + x) + 1]=border_g;
        image->pixels[ 3*(y*image->width + x) + 2]=border_b;
    }
    x=image->width-1;
    for(y=0; y<image->height; y++)
    {
        int index = 3*(y*image->width + x);
        image->pixels[ index + 0]=border_r;
        image->pixels[ index + 1]=border_g;
        image->pixels[ index + 2]=border_b;
    }
    x=image->width-2;
    for(y=0; y<image->height; y++)
    {
        int index = 3*(y*image->width + x);
        image->pixels[ index + 0]=border_r;
        image->pixels[ index + 1]=border_g;
        image->pixels[ index + 2]=border_b;
    }
}



// Your initialization code goes here.
void InitializeMyStuff()
{
    gliGenericImage *image[num_textures];
    int n=0;
    image[n++] = readImage("contemporary-mosaic-tile.tga");
    image[n++] = readImage("brick-wall.tga");
    image[n++] = readImage("sky.tga");
    image[n++] = readImage("Seattle.tga");
    if(n!=num_textures)
    {
        printf("Error: Wrong number of textures\n");
        
        exit(1);
    }
    
    glGenTextures(num_textures, texName);
    
    for(int i=0; i<num_textures; i++)
    {
        glBindTexture(GL_TEXTURE_2D, texName[i]);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
        int repeats = true;
        int needs_border = false; // Needed if clamping and not filling the whole polygon.
        if(repeats)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }
        else
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        }
        if(needs_border)
        {
            // set a border.
            SetBorder(image[i]);
        }
        
        bool mipmaps = false;
        if(!PowerOf2(image[i]->height) || !PowerOf2(image[i]->width))
        {
            // WARNING: Images that do not have width and height as
            // powers of 2 MUST use mipmaps.
            mipmaps = true;
        }
        
        if (mipmaps)
        {
            gluBuild2DMipmaps(GL_TEXTURE_2D, image[i]->components,
                              image[i]->width, image[i]->height,
                              image[i]->format, GL_UNSIGNED_BYTE, image[i]->pixels);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                            //GL_LINEAR_MIPMAP_LINEAR);
                            GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                            //GL_LINEAR);
                            GL_NEAREST);
        } 
        else 
        {
            glTexImage2D(GL_TEXTURE_2D, 0, image[i]->components,
                         image[i]->width, image[i]->height, 0,
                         image[i]->format, GL_UNSIGNED_BYTE, image[i]->pixels);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
    }
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
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	InitializeMyStuff();

	glutMainLoop();

	return 0;
}
