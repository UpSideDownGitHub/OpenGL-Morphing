
#include <Windows.h>
#include <iostream>
#include <vector>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "glut.h"
#include "Point.h"

std::vector<Point>* startShape = new std::vector<Point>();
std::vector<Point>* endShape = new std::vector<Point>();
std::vector<Point>* currentShape = new std::vector<Point>();

void renderBitmapString(
	float x,
	float y,
	float z,
	void* font,
	char* string) 
{
	glMatrixMode(GL_PROJECTION);    //Select projection matrix
	glPushMatrix();                 //save it
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);    //Select modelview matrix
	glPushMatrix();                //save it
	glLoadIdentity();

	const double w = glutGet(GLUT_WINDOW_WIDTH);
	const double h = glutGet(GLUT_WINDOW_HEIGHT);
	glOrtho(0, w, h, 0, -100, 100);

	// set up ur glOrtho
	char* c;
	glRasterPos3f(x, y, z);

	for (c = string; *c != '\0'; c++)
	{
		//std::cout << *c;
		glutBitmapCharacter(font, *c);
	}

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();                //Restore your old projection matrix

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();


}

void display() 
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const double w = glutGet(GLUT_WINDOW_WIDTH);
	const double h = glutGet(GLUT_WINDOW_HEIGHT);
	glOrtho(0, w, h, 0, -100, 100);

	// NEED TO LOOP THROUGH POINTS AND DRAW EACH OF THEM 
	// WILL ALSO NEED TO DO THE LINEAR INTERPOLATION EVENTUALLY

	glBegin(GL_LINE_LOOP);

	for (size_t i = 0; i < currentShape->size(); i++)
	{
		glVertex3f(currentShape->at(i).position.x, currentShape->at(i).position.y, currentShape->at(i).position.z);
	}

	glEnd();

	// Test on showing test
	char theString[] = "HELLO THERE";
	renderBitmapString(0, 0, 0, GLUT_BITMAP_9_BY_15, theString);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutSwapBuffers();
}

void mouseClicks(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		Point point = Point(Vector3(x, y, 0), Color(0, 0, 0, 255), 1, 0);
		currentShape->push_back(point);
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(600, 600);
	glutCreateWindow("GLUT");

	glutDisplayFunc(display);
	glutMouseFunc(mouseClicks);
	//glutPassiveMotionFunc(motion);	MOUSE MOVEMENT
	glutIdleFunc(display);

	glutMainLoop();
	return 0;
}

