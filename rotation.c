
#include <math.h>		
#include <stdio.h>
#include <stdlib.h>		
#include "Glut.h"


const double Xmin = 0.0, Xmax = 6.0;
const double Ymin = 0.0, Ymax = 6.0;
const double PI = 3.1415926;

double angle = 0.0;

void myKeyboardFunc(unsigned char key, int x, int y)
{


}

void mySpecialKeyFunc(int key, int x, int y)
{

}


void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3ub(0, 255, 0);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	angle += 2 * PI  / 360;
	
	if (angle >= 360) {
		angle = 0;
	}
	glTranslatef(2.0, sqrt(5), 0);
	glRotatef(angle, 0, 0, 1);
	glTranslatef(-2.0, -sqrt(5), 0);

	glBegin(GL_TRIANGLES);
	
	glVertex2f(1.0, 1.0);
	glVertex2f(3.0, 1.0);
	glVertex2f(2, sqrt(5));

	glEnd();
	glutSwapBuffers();
	glutPostRedisplay();




}

void initRendering()
{
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
}

void resizeWindow(int w, int h)
{
	double scale, center;
	double windowXmin, windowXmax, windowYmin, windowYmax;

	glViewport(0, 0, w, h);

	w = (w == 0) ? 1 : w;
	h = (h == 0) ? 1 : h;
	if ((Xmax - Xmin) / w < (Ymax - Ymin) / h) {
		scale = ((Ymax - Ymin) / h) / ((Xmax - Xmin) / w);
		center = (Xmax + Xmin) / 2;
		windowXmin = center - (center - Xmin)*scale;
		windowXmax = center + (Xmax - center)*scale;
		windowYmin = Ymin;
		windowYmax = Ymax;
	}
	else {
		scale = ((Xmax - Xmin) / w) / ((Ymax - Ymin) / h);
		center = (Ymax + Ymin) / 2;
		windowYmin = center - (center - Ymin)*scale;
		windowYmax = center + (Ymax - center)*scale;
		windowXmin = Xmin;
		windowXmax = Xmax;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(windowXmin, windowXmax, windowYmin, windowYmax, -1, 1);

}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(10, 60);
	glutInitWindowSize(360, 360);

	glutCreateWindow("Rotation");

	initRendering();

	glutKeyboardFunc(myKeyboardFunc);
	glutSpecialFunc(mySpecialKeyFunc);


	glutReshapeFunc(resizeWindow);


	glutDisplayFunc(drawScene);

	glutMainLoop();

	return(0);
}

