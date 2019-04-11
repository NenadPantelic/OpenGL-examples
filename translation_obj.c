
#include <math.h>		
#include <stdio.h>
#include <stdlib.h>		
#include "Glut.h"

const double Xmin = 0.0, Xmax = 12.0;
const double Ymin = 0.0, Ymax = 12.0;


float rectW = 1.6;
float rectH = 0.8;

float deltaX = 0.001, deltaY = 0.0;
float xPos = 6.8, yPos = 6.8;
int slope = 0;
const float PI = 3.1415926;
void myKeyboardFunc(unsigned char key, int x, int y)
{


}

void mySpecialKeyFunc(int key, int x, int y)
{

}

void drawLine(float x1, float y1, float x2, float y2) {
	glColor3ub(255, 255, 255);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();

}
//origin's x coord is on the half of the screen 
void drawRect(float width, float height) {
	glBegin(GL_QUADS);
	glVertex2f(-width / 2, 0);
	glVertex2f(-width / 2, height);
	glVertex2f(width / 2, height);
	glVertex2f(width / 2, 0);
	glEnd();


}

void drawTriangle(float startingX, float startingY, float width) {
	glColor3ub(0, 0, 255);
	glBegin(GL_TRIANGLES);
	int flag = (startingX > 0) ? 1 : -1;
	glVertex2f(startingX, startingY);
	glVertex2f(startingX, 0);
	glVertex2f(flag * width + startingX, 0);
	glEnd();


}


void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	drawLine(0, Ymax / 2, Xmax, Ymax / 2);
	glTranslatef(Xmax / 2, Ymax / 2, 0);

	if (xPos + 0.2 < Xmax) {
		xPos += deltaX;
	}
	yPos += deltaY;

	if (xPos >= ((Xmax + rectW) / 2)) {
		//deltaX * tan(alpha) -> tan(alpha) = rectH / (rectW/2) * (-1)
		deltaY = -1 * deltaX * 2 * rectH / rectW;
		if(!slope)  slope = 1;
	}
	if (yPos <= Ymax / 2) {
		deltaY = 0.0;
		slope = 0;
	}
	glColor3ub(255, 82, 0);
	drawRect(rectW, rectH);
	drawRect(rectW, rectH);
	drawTriangle(-rectW / 2, rectH, rectW / 2);
	drawTriangle(rectW / 2, rectH, rectW / 2);
	glLoadIdentity();
	glTranslatef(xPos, yPos, 0);
	if (slope) glRotatef(180 * atan(rectH, rectW / 2) / PI , 0, 0, 1);
	glColor3ub(0, 255, 0);
	drawRect(0.4, 0.4);

	glutPostRedisplay();
	glFlush();
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

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(10, 60);
	glutInitWindowSize(360, 360);

	glutCreateWindow("Translation objects");

	initRendering();

	glutKeyboardFunc(myKeyboardFunc);
	glutSpecialFunc(mySpecialKeyFunc);


	glutReshapeFunc(resizeWindow);


	glutDisplayFunc(drawScene);

	glutMainLoop();

	return(0);
}

