
#include <math.h>		
#include <stdio.h>
#include <stdlib.h>		
#include "Glut.h"

const double Xmin = 0.0, Xmax = 6.0;
const double Ymin = 0.0, Ymax = 8.0;
const float PI = 3.1415926;

float deltaX = 0.0;
float rotationAngle = 0.0;

void myKeyboardFunc(unsigned char key, int x, int y)
{


}

void mySpecialKeyFunc(int key, int x, int y)
{

}

void drawCircle(float xCenter, float yCenter, float radius, int numOfPoints) {

	
	glBegin(GL_POLYGON);
	glColor3ub(255, 0, 0);

	float angle = 0.0;

	for (int i = 0; i < numOfPoints; i++) {

		angle = i * 2 * PI / numOfPoints;
		glVertex2f(radius * cos(angle),radius * sin(angle));
	}
	   
	glEnd();
	
}

void drawRect(float pointX, float pointY, float width, float height) {

	glBegin(GL_QUADS);
	glColor3ub(0, 0, 255);

	glVertex2f(pointX, pointY);
	glVertex2f(pointX, pointY + height);
	glVertex2f(pointX + width, pointY + height);
	glVertex2f(pointX + width, pointY);
	glEnd();


}
void drawScene(void)
{
	deltaX += 0.0001;
	rotationAngle += 0.0001;

	if (deltaX >= Xmax) {
		deltaX = 0.0;
	}
	if (rotationAngle >= 360) {
		rotationAngle = 0.0;
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glTranslatef(1.0, 0.2, 0);
	glTranslatef(deltaX, 0, 0);
	glRotatef(rotationAngle, 0, 0, 1);
	drawCircle(1.0, 0.2, 0.2, 360);
	glLoadIdentity();

	glTranslatef(2.0, 0.2, 0);
	glTranslatef(deltaX, 0, 0);
	glRotatef(rotationAngle, 0, 0, 1);
	drawCircle(2, 0.2, 0.2, 360);
	glLoadIdentity();

	glTranslatef(deltaX, 0, 0);
	drawRect(0.55, 0.4, 1.9, 0.8);
	glutSwapBuffers();
	glutPostRedisplay();
}

void initRendering()
{

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

	glutCreateWindow("Vehicle");

	initRendering();

	glutKeyboardFunc(myKeyboardFunc);
	glutSpecialFunc(mySpecialKeyFunc);


	glutReshapeFunc(resizeWindow);


	glutDisplayFunc(drawScene);

	glutMainLoop();

	return(0);
}

