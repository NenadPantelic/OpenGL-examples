/*
* Napisati kratko uputstvo za koriscenje igrice
*
*/


/*game over leads to program exit*/
#include <math.h>		
#include <stdio.h>
#include <stdlib.h>		
#include "Glut.h"

const double Xmin = 0.0, Xmax = 6.0;
const double Ymin = 0.0, Ymax = 6.0;


int COLORS[][3] = { { 255, 0, 0 }, { 0, 0, 255 }, { 255, 0, 0 } };

const int NUM_OF_BRICKS = 3;
const double BRICK_XPOS = 3.0;
const double PI = 3.1415926;
const double FIRST_RECT_H = 4.5;
const double SECOND_RECT_H = 4.8;
const double THIRD_RECT_H = 5.1;


float rectWidth = 0.6;
float rectHeight = 0.2;

int brickDestroyed = 0, firstBrickDestroyed = 0, secondBrickDestroyed = 0, thirdBrickDestroyed = 0;


/*board data*/
float boardWidth = 1.0;
float boardHeight = 0.2;
float boardDeltaX = 0.095;
float boardPosX = 3.0, boardPosY = 0.1;


/*ball data*/

const float RADIUS = 0.1;
float xPos = 3.0, yPos = 1.0;
float xVect = 0.0003, yVect = -0.0001;




int detectHBrickBreak(){
	return ((BRICK_XPOS - rectWidth / 2) <= xPos && xPos <= (BRICK_XPOS + rectWidth / 2));

}

int detectVBrickBreak(){

	float lowerBounds[] = { FIRST_RECT_H - rectHeight / 2, SECOND_RECT_H - rectHeight / 2, THIRD_RECT_H - rectHeight / 2 };
	float upperBounds[] = { FIRST_RECT_H + rectHeight / 2, SECOND_RECT_H + rectHeight / 2, THIRD_RECT_H + rectHeight / 2 };

	for (int i = 0; i < NUM_OF_BRICKS; i++){
		if ((lowerBounds[i] <= yPos) && (upperBounds[i] >= yPos)){
			return i + 1;
		}

	}
	return 0;


}


void myKeyboardFunc(unsigned char key, int x, int y)
{


}

void mySpecialKeyFunc(int key, int x, int y)
{

	if (key == GLUT_KEY_RIGHT){
		if ((boardPosX + boardWidth / 2) < Xmax){
			boardPosX += boardDeltaX;
		}
	}
	if (key == GLUT_KEY_LEFT){
		if ((boardPosX - boardWidth / 2) > Xmin){
			boardPosX -= boardDeltaX;

		}

	}
	glutPostRedisplay();
}


void drawCircle(float radius, int numOfPoints){

	glColor3ub(255, 80, 0);
	glBegin(GL_POLYGON);
	float angle;
	for (int i = 0; i < numOfPoints; i++){
		angle = i * 2 * PI / numOfPoints;
		glVertex2f(radius * cos(angle), radius * sin(angle));

	}
	glEnd();


}


int detectCollision(){

	int hFlag = (yPos - RADIUS) <= (boardPosY + boardHeight / 2);
	int leftWFlag = (xPos + RADIUS) >= (boardPosX - boardWidth / 2);
	int rightWFlag = (xPos - RADIUS) <= (boardPosX + boardWidth / 2);
	return hFlag && leftWFlag && rightWFlag;

}
void adaptVector(){

	float topVal = yPos + RADIUS;
	float leftVal = xPos - RADIUS, rightVal = xPos + RADIUS;


	if (topVal >= Ymax || detectCollision()){
		yVect *= -1;
	}
	if (leftVal <= Xmin || rightVal >= Xmax){
		xVect *= -1;
	}

}

void drawRect(float width, float height, int r, int g, int b){

	glColor3ub(r, g, b);
	glBegin(GL_QUADS);
	glVertex2f(-width / 2, -height / 2);
	glVertex2f(-width / 2, height / 2);
	glVertex2f(width / 2, height / 2);
	glVertex2f(width / 2, -height / 2);

	glEnd();

}
void drawScene(void)
{


	adaptVector();


	xPos += xVect;
	yPos += yVect;


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/*ball*/
	glTranslatef(xPos, yPos, 0);
	drawCircle(0.1, 360);
	glLoadIdentity();

	/*board*/
	glTranslatef(boardPosX, boardPosY, 0);
	drawRect(boardWidth, boardHeight, 0, 255, 0);

	brickDestroyed = detectHBrickBreak() * detectVBrickBreak();
	if (!firstBrickDestroyed) firstBrickDestroyed = (brickDestroyed == 1);
	if (!secondBrickDestroyed) secondBrickDestroyed = (brickDestroyed == 2);
	if (!thirdBrickDestroyed) thirdBrickDestroyed = (brickDestroyed == 3);


	if (firstBrickDestroyed){
		COLORS[0][0] = COLORS[0][1] = COLORS[0][2] = 255;
	}
	if (secondBrickDestroyed){
		COLORS[1][0] = COLORS[1][1] = COLORS[1][2] = 255;
	}
	if (thirdBrickDestroyed){
		COLORS[2][0] = COLORS[2][1] = COLORS[2][2] = 255;
	}

	/*first target rect*/
	glLoadIdentity();
	glTranslatef(BRICK_XPOS, FIRST_RECT_H, 0);
	drawRect(rectWidth, rectHeight, COLORS[0][0], COLORS[0][1], COLORS[0][2]);
	
	/*second target rect*/
	glLoadIdentity();
	glTranslatef(BRICK_XPOS, SECOND_RECT_H, 0);
	drawRect(rectWidth, rectHeight, COLORS[1][0], COLORS[1][1], COLORS[1][2]);

	/*third target rect*/
	glLoadIdentity();
	glTranslatef(BRICK_XPOS, THIRD_RECT_H, 0);
	drawRect(rectWidth, rectHeight, COLORS[2][0], COLORS[2][1], COLORS[2][2]);

	glutPostRedisplay();
	if (yPos <= Ymin) exit(1);
	glutSwapBuffers();
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

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(10, 60);
	glutInitWindowSize(360, 360);

	glutCreateWindow("Kolokvijum_Nenad_Pantelic");

	initRendering();

	glutKeyboardFunc(myKeyboardFunc);
	glutSpecialFunc(mySpecialKeyFunc);


	glutReshapeFunc(resizeWindow);


	glutDisplayFunc(drawScene);

	glutMainLoop();

	return(0);
}

