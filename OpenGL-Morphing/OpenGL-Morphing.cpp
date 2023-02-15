
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

