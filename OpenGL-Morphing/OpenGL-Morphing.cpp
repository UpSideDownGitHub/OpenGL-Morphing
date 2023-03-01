
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "glut.h"
#include "Point.h"
#include "Shape.h"
#include "Vector3.h"
#include "Text.h"

std::vector<Point>* startShape = new std::vector<Point>();
std::vector<Point>* endShape = new std::vector<Point>();
std::vector<Point>* currentShape = new std::vector<Point>();
std::vector<Square>* currentShapePoints = new std::vector<Square>();

// mouse movement
Square mousePointer = Square(Vector3(0,0,0), 10, 10);
float mouseX;
float mouseY;

// booleans
bool showOrignalShape = true;

// Gameplay Shapes
Square gameSquare = Square(Vector3(300, 300, 0), 200, 200);

// Points
std::chrono::system_clock::time_point learnStartTime;
int currentPoints;

// Timer
float learnTime = 5;

// Text
Text scoreText = Text(Vector3(275,20,0), Color(255,255,255,255), "Score");
Text pointsLeftText = Text(Vector3(250,575,0), Color(255,255,255,255), "Points Left");
Text currentPointsText = Text(Vector3(295,595,0), Color(255,255,255,255), " ");
Text learnText = Text(Vector3(275, 50, 0), Color(255,0,0,255), "Learn");
Text drawText = Text(Vector3(275, 50, 0), Color(0,255,0,255), "Draw");



void idle()
{
	auto elapsedTime = std::chrono::system_clock::now() - learnStartTime;

	if (std::chrono::duration<float>(elapsedTime).count() > learnTime)
	{
		// hide the orignal and let the player start pressing
		showOrignalShape = false;
	}
}

void display()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	idle();

	// Set up Projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const double w = glutGet(GLUT_WINDOW_WIDTH);
	const double h = glutGet(GLUT_WINDOW_HEIGHT);
	glOrtho(0, w, h, 0, -100, 100);


	// Draw Text Objects
	scoreText.drawText();
	pointsLeftText.drawText();
	currentPointsText.drawText();

	if (showOrignalShape)
	{
		// Draw game objects
		learnText.drawText();
		gameSquare.drawShapeOutline();
	}
	else
		drawText.drawText();


	// Draw the player drawn shape
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	for (size_t i = 0; i < currentShape->size(); i++)
	{
		glColor4f(currentShape->at(i).color.r, currentShape->at(i).color.g, currentShape->at(i).color.b, currentShape->at(i).color.a);
		glVertex3f(currentShape->at(i).position.x, currentShape->at(i).position.y, currentShape->at(i).position.z);
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


	// Draw the mouse pointer
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
	// If left mouse button pressed
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (currentPoints > 0)
		{
			showOrignalShape = false;

			Point point = Point(Vector3(x, y, 0), Color(255, 255, 255, 255), 1, 0);
			currentShape->push_back(point);
			Square position = Square(Vector3(x, y, 0), 10, 10);
			currentShapePoints->push_back(position);

			currentPoints--;
			currentPointsText.setText(std::to_string(currentPoints));
		}
	}
	glutPostRedisplay();
}
void keyPressed(unsigned char key, int x, int y)
{

}

void init()
{
	currentPoints = gameSquare.points->size();
	currentPointsText.setText(std::to_string(currentPoints));

	learnStartTime = std::chrono::system_clock::now();
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
	init();

	glutMainLoop();
	return 0;
}

