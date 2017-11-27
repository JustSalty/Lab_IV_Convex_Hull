
#include "freeglut.h"
#include <iostream>

#include "Kirpatrick.h"
#include "Graham.h"
#include "Andrew_Jarv.h"
#include "Recursive.h"

using namespace std;


vector<Point> init_points;
vector<Point> hull;
const double point_Size = 0.04;

void reshape (int width, int height);
void display (void);
void drawHULL();
void onEF();


///<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void drawHULL()
{
    int h = hull.size(), p = init_points.size();
    for (int i = 0; i < p; ++i)
    {
        glBegin(GL_QUADS);
        glVertex2f( init_points[i].x + point_Size , init_points[i].y + point_Size);
        glVertex2f( init_points[i].x - point_Size , init_points[i].y + point_Size);
        glVertex2f( init_points[i].x - point_Size , init_points[i].y - point_Size);
        glVertex2f( init_points[i].x + point_Size , init_points[i].y - point_Size);
        glEnd();
        /**
        glBegin(GL_POINT);
        glPointSize(point_Size);
        glVertex2f( hull[i].x, hull[i].y );
        glEnd();
        **/
    }
    for (int i = 0; i < h; ++i)
    {
        glBegin(GL_LINES);
		glVertex2f( hull[i].x , hull[i].y );
		glVertex2f( hull[(i+1)%h].x , hull[(i+1)%h].y );
		glEnd();
    }
}

void display (void)
{
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f); // Clear the background of our window to red
    glClear(GL_COLOR_BUFFER_BIT);//Clear the screen

	drawHULL();

	glutSwapBuffers();
	glFlush();
}

void reshape (int width, int height)
{

	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
	glOrtho(-2, 5, -2, 5, -1, 10);
	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly
}

void onEF()
{
	glutPostRedisplay();
	//Draw everything to the screen
}
///<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


int main(int argc, char **argv)
{
    init_points = {{0, 3}, {2, 2}, {1, 1}, {2, 1},
                    {3, 0}, {0, 0}, {3, 3}};
    //vector<Point> hull_K; convexHull_K (init_points, hull_K); hull = hull_K;
    //vector<Point> hull_G; convexHull_G (init_points, hull_G); hull = hull_G;
    //vector<Point> hull_A; convexHull_AJ(init_points, hull_A); hull = hull_A;
    //vector<Point> hull_R; convexHull_R (init_points, hull_R); hull = hull_R;

    glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode(GLUT_SINGLE); // Set up a basic display buffer (only single buffered for now)
	glutInitWindowSize(600, 600); // Set the width and height of the window
	glutInitWindowPosition(100, 100); // Set the position of the window
	glutCreateWindow("OpenGL Window"); // Set the title for the window
	//glEnable( GL_POINT_SMOOTH );

	glutIdleFunc(onEF);
	glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering
	glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping
	glutMainLoop(); // Enter GLUT's main loop

    return 0;
}
