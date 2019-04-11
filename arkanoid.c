
#include <math.h>		
#include <stdio.h>
#include <stdlib.h>		
#include "Glut.h"

const double Xmin = 0.0, Xmax = 8.0;
const double Ymin = 0.0, Ymax = 8.0;

const float PI = 3.1415926;
float rotationAngle = 0.0;
float xPos = 1.5, yPos = 2.0;
float vector = 0;
float stepX = 0.0015;
float stepY = 0.00075;
float angle = 3.1415926 / 6.;
float vectorX = 0.0, vectorY = 0.0;
const float radius = 0.25;
const float boardWidth = 1.2, boardHeight = 0.35;
float boardX = 4.0, boardY = 0.025;
const float offset = 0.0001;


/*buggy - improve board edge collision*/
void myKeyboardFunc(unsigned char key, int x, int y)
{

	float newX;
	if (key == 'd') {
		newX = boardX + boardWidth / 2 + offset;
		boardX = (newX < Xmax) ? newX : boardX;
	}
	else if (key == 'a') {
		newX = boardX - boardWidth / 2 - offset;
		boardX = (newX > Xmin) ? newX : boardX;
	}


}

void mySpecialKeyFunc(int key, int x, int y)
{
	
}

void drawCircle(float radius, int numOfPoints) {
	glColor3ub(0, 255, 255);
	glBegin(GL_POLYGON);
	float angle;
	for (int i = 0; i < numOfPoints; i++) {
		angle = i * 2 * PI / numOfPoints;
		glVertex2f(radius * cos(angle), radius * sin(angle));
	}
	glutPostRedisplay();
	glEnd();
}

void drawRect(float width, float height) {
	glColor3ub(0, 255, 0);
	glBegin(GL_QUADS);
	glVertex2f(-width / 2, -height / 2);
	glVertex2f(- width / 2, height / 2);
	glVertex2f(width / 2, height / 2);
	glVertex2f(width / 2, -height / 2);
	glEnd();
}

int boardCollision() {
	float leftBoardBound = boardX - boardWidth / 2;
	float righthBoardBound = boardX + boardWidth / 2;
	int hFlag = ((yPos - radius) <= boardY + boardHeight / 2);
	return hFlag && (leftBoardBound + 0.05) <= (xPos + radius)  && (xPos - radius) <= (righthBoardBound - 0.05);

}
void determineVector() {

	float xUBound = xPos + radius, yUBound = yPos + radius;
	float xLBound = xPos - radius, yLBound = yPos - radius;
	if (xUBound >= Xmax || xLBound <= Xmin) {
		stepX *= -1;
	}

	if (yUBound >= Ymax || boardCollision()) {
		stepY *= -1;
	}

}
void drawScene(void)
{

	rotationAngle += 0.01;
	if (rotationAngle >= 360) {
		rotationAngle = 0.0;
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3ub(0, 10, 255);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(boardX, boardY, 0.0);
	drawRect(boardWidth, boardHeight);
	glLoadIdentity();
	determineVector();
	xPos += stepX * cos(angle);
	yPos += stepY * sin(angle);
	glTranslatef(xPos, yPos, 0.);
	glRotatef(rotationAngle, 0.0, 0.0, 1.0);
	drawCircle(radius, 360);

	glutSwapBuffers();
	glutPostRedisplay();

	
	if (yPos + radius < Ymin) {
		exit(1);
	}
	
	
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

	glutCreateWindow("Arkanoid");

	initRendering();

	glutKeyboardFunc(myKeyboardFunc);
	glutSpecialFunc(mySpecialKeyFunc);


	glutReshapeFunc(resizeWindow);


	glutDisplayFunc(drawScene);

	glutMainLoop();

	return(0);
}

