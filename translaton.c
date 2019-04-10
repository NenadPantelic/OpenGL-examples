
#include <math.h>		
#include <stdio.h>
#include <stdlib.h>		
#include "Glut.h"


const double Xmin = 0.0, Xmax = 5.0;
const double Ymin = 0.0, Ymax = 5.0;
void drawRect(float xpos, float ypos, float dim);

float xPos = 0.0;
float yPos = 0.0;
float deltaX = 0.001, deltaY = 0.0;
int state = 0;
float dim = 0.5;

void myKeyboardFunc(unsigned char key, int x, int y)
{


}

void mySpecialKeyFunc(int key, int x, int y)
{

}

void determineDeltaVals(int state) {

	switch (state) {

	case 0:
		deltaX = 0.001;
		deltaY = 0.0;
		return;
	case 1:
		deltaX = 0.0;
		deltaY = 0.001;
		return;
	case 2:
		deltaX = -0.001;
		deltaY = 0.0;
		return;
	case 3:
		deltaX = 0.0;
		deltaY = -0.001;
		return;
	}

}

void drawScene(void)
{


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*checking state value is just for not calling determineDeltaVals all the time*/
	if (state == 3 && xPos <= Xmin && yPos <= Ymin) {
		state = 0;
		determineDeltaVals(state);
	}
	if (state == 0 && (xPos + dim) >= Xmax) {
		state = 1;
		determineDeltaVals(state);
	}

	if (state == 1 && (yPos + dim) >= Ymax) {
		state = 2;
		determineDeltaVals(state);
	}
	if (state == 2 && xPos <= Xmin && yPos >= Ymin) {
		state = 3;
		determineDeltaVals(state);
	}
	xPos += deltaX;
	yPos += deltaY;

	drawRect(xPos, yPos, 0.5);
	glutPostRedisplay();




}



void initRendering()
{

	glShadeModel(GL_FLAT);	// The default value of GL_SMOOTH is usually better - flat or smooth shading
	glEnable(GL_DEPTH_TEST);

}

void drawRect(float xpos, float ypos, float dim) {

	glColor3ub(0, 0, 255);
	glBegin(GL_QUADS);

	glVertex2f(xpos, ypos);
	glVertex2f(xpos, ypos + dim);
	glVertex2f(xpos + dim, ypos + dim);
	glVertex2f(xpos + dim, ypos);
	glEnd();
	glFlush();


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

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(10, 60);
	glutInitWindowSize(360, 360);

	glutCreateWindow("Translation");

	initRendering();

	glutKeyboardFunc(myKeyboardFunc);
	glutSpecialFunc(mySpecialKeyFunc);


	glutReshapeFunc(resizeWindow);


	glutDisplayFunc(drawScene);

	glutMainLoop();

	return(0);
}

