
#include <Windows.h>
#include <iostream>
#include <vector>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "glut.h"
#include "Point.h"
#include "Shape.h"
#include "Vector3.h"

std::vector<Point>* startShape = new std::vector<Point>();
std::vector<Point>* endShape = new std::vector<Point>();
std::vector<Point>* currentShape = new std::vector<Point>();
std::vector<Square>* currentShapePoints = new std::vector<Square>();

Square mousePointer = Square(Vector3(0,0,0), 10, 10);

float mouseX;
float mouseY;

bool drawingFirstShape = true;
bool morphingShape = false;


void display() 
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const double w = glutGet(GLUT_WINDOW_WIDTH);
	const double h = glutGet(GLUT_WINDOW_HEIGHT);
	glOrtho(0, w, h, 0, -100, 100);

	// First Shape
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	for (size_t i = 0; i < currentShape->size(); i++)
	{
		glColor4f(currentShape->at(i).color.r, currentShape->at(i).color.g, currentShape->at(i).color.b, currentShape->at(i).color.a);
		glVertex3f(currentShape->at(i).position.x, currentShape->at(i).position.y, currentShape->at(i).position.z);
	}
	glEnd();
	glPopMatrix();

	// End Shape
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	for (size_t i = 0; i < endShape->size(); i++)
	{
		glColor4f(endShape->at(i).color.r, endShape->at(i).color.g, endShape->at(i).color.b, endShape->at(i).color.a);
		glVertex3f(endShape->at(i).position.x, endShape->at(i).position.y, endShape->at(i).position.z);
	}
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glColor4f(255, 255, 255, 255);
	for (size_t i = 0; i < currentShapePoints->size(); i++)
	{
		currentShapePoints->at(i).drawShape();
	}
	glPopMatrix();

	glPopMatrix();
	mousePointer.drawShape(Vector3(mouseX, mouseY, 0));
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutSwapBuffers();
}

void motion(int x, int y) 
{
	mouseX = x;
	mouseY = y;
}

void mouseClicks(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (drawingFirstShape)
		{
			Point point = Point(Vector3(x, y, 0), Color(255, 255, 255, 255), 1, 0);
			currentShape->push_back(point);
			Square position = Square(Vector3(x, y, 0), 10, 10);
			currentShapePoints->push_back(position);
		}
		else
		{
			Point point = Point(Vector3(x, y, 0), Color(255, 0, 0, 255), 1, 0);
			endShape->push_back(point);
		}
	}
	glutPostRedisplay();
}
void keyPressed(unsigned char key, int x, int y)
{
	if (key == 'p')
	{
		drawingFirstShape = false;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(600, 600);
	glutCreateWindow("GLUT");

	glutDisplayFunc(display);
	glutMouseFunc(mouseClicks);
	glutPassiveMotionFunc(motion);	
	glutKeyboardFunc(keyPressed);
	glutIdleFunc(display);

	// create a new mouse point object to see the position of the mouse

	glutMainLoop();
	return 0;
}

