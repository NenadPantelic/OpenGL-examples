

#include <math.h>		
#include <stdio.h>
#include <stdlib.h>		
#include "Glut.h"


#define M_PI acos(-1.0)
const double Xmin = 0.0, Xmax = 10.0;
const double Ymin = 0.0, Ymax = 10.0;

const int pointsNo = 360;

typedef struct {

	int red;
	int green;
	int blue;
}Color;

void myKeyboardFunc(unsigned char key, int x, int y)
{


}

void mySpecialKeyFunc(int key, int x, int y)
{

}

void getBinaryRepr(int x, Color *color) {

	color->red = x / 4 * 255;
	color->green = (x % 4) / 2 * 255;
	color->blue = (x % 2) * 255;
}

void drawCircle(double radius, int numOfPoints, double xCenter, double yCenter, Color color) {


	glColor3ub(color.red, color.green, color.blue);
	glBegin(GL_POLYGON);
	double xCoeff, yCoeff;
	double angle;
	for (int i = 0; i <= numOfPoints; i++) {

		angle = 2 * M_PI * i / numOfPoints;
		xCoeff = radius * cos(angle);
		yCoeff = radius * sin(angle);
		fprintf(stdout, "x = %f, y = %f\n", xCoeff, yCoeff);
		glVertex2f(xCenter - xCoeff, yCenter - yCoeff);

	}
	glEnd();
	glFlush();

}


void drawScene(void)
{
	double xCenter = Xmax / 2, yCenter = Ymax / 2;
	Color color;
	for (int i = 5; i > 0; i--) {
		fprintf(stdout, "center(x) = %f, center(y) = %f, radius = %d\n", xCenter, yCenter, i);
		getBinaryRepr(i, &color);
		drawCircle(i, pointsNo, xCenter, yCenter, color);

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

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(10, 60);
	glutInitWindowSize(360, 360);

	glutCreateWindow("Circles");

	initRendering();

	glutKeyboardFunc(myKeyboardFunc);
	glutSpecialFunc(mySpecialKeyFunc);


	glutReshapeFunc(resizeWindow);


	glutDisplayFunc(drawScene);

	glutMainLoop();

	return(0);
}

