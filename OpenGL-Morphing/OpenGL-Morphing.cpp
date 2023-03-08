
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
#include "Closest.h"

Closest closest = Closest();
std::vector<int> drawOrder;

// the shape to move to
std::vector<Point> targetShape = std::vector<Point>();

// the shape the player has drawn
std::vector<Point>* currentShape = new std::vector<Point>();
std::vector<Square>* currentShapePoints = new std::vector<Square>();

// mouse movement
Shape mousePointer = Square(Vector3(0,0,0), 10, 10);
float mouseX;
float mouseY;

// booleans
bool showOrignalShape = true;
bool showOrignalFinished = false;
bool mergeShapes = false;

// Gameplay Shapes
Shape currentGameShape = Square(Vector3(300, 300, 0), 100, 100);

// Points
std::chrono::system_clock::time_point learnStartTime;
int currentPoints;

// Timer
float learnTime = 5;

// interpolation
float morphTime = 0.0;

// score
int score = 0;

// Text
Text scoreText = Text(Vector3(275,20,0), Color(255,255,255,255), "Score");
Text playerScore = Text(Vector3(275,35,0), Color(255,255,255,255), "0");
Text pointsLeftText = Text(Vector3(250,575,0), Color(255,255,255,255), "Points Left");
Text currentPointsText = Text(Vector3(295,595,0), Color(255,255,255,255), "0");
Text learnText = Text(Vector3(275, 50, 0), Color(255,0,0,255), "Learn");
Text drawText = Text(Vector3(275, 50, 0), Color(0,255,0,255), "Draw");



void checkTime()
{
	auto elapsedTime = std::chrono::system_clock::now() - learnStartTime;

	if (std::chrono::duration<float>(elapsedTime).count() > learnTime)
	{
		// hide the orignal and let the player start pressing
		showOrignalShape = false;
	}
}

void idle()
{
	morphTime += 0.0000001;
}

void interpolateShape()
{
	// Interpolation of all of the potins of the shape
	for (size_t i = 0; i < currentShape->size(); i++)
	{
		currentShape->at(i) = currentShape->at(i) * (1.0 - morphTime) + targetShape.at(i) * morphTime;
	}	

	// TODO: need to change both of these loops so that they go in the order of the closest shape meanign a proper square will be drawn (hopefully)
	
	// draw the fill of the interpolating shape
	/*
	glPushMatrix();
	glBegin(GL_QUADS);
	for (size_t i = 0; i < currentShape->size(); i++)
	{
		glVertex3f(currentShape->at(i).position.x, currentShape->at(i).position.y, currentShape->at(i).position.z);
	}
	glEnd();
	glPopMatrix();
	*/

	// draw the outline of the interpolating shape
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f(255, 0, 0, 255); 
	for (size_t i = 0; i < currentShape->size(); i++)
	{
		glVertex3f(currentShape->at(i).position.x, currentShape->at(i).position.y, currentShape->at(i).position.z);
	}
	glEnd();
	glPopMatrix();
}

void display()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	checkTime();
	idle();

	// Set up Projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const double w = glutGet(GLUT_WINDOW_WIDTH);
	const double h = glutGet(GLUT_WINDOW_HEIGHT);
	glOrtho(0, w, h, 0, -100, 100);

	

	// Draw Text Objects
	scoreText.drawText();
	playerScore.drawText();
	pointsLeftText.drawText();
	currentPointsText.drawText();

	if (showOrignalShape || showOrignalFinished)
	{
		// Draw game objects
		learnText.drawText();
		currentGameShape.drawShapeOutline();
	}
	else
		drawText.drawText();


	// interpolate the shape from the one drawn to the correct shape
	if (mergeShapes)
	{
		if (morphTime > 1.0) morphTime = 1.0;
		interpolateShape();
	}
	else
	{
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
	}

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

			Point point = Point(Vector3(x, y, 0), Color(255, 0, 0, 255), 1, 0);
			currentShape->push_back(point);
			Square position = Square(Vector3(x, y, 0), 10, 10);
			currentShapePoints->push_back(position);

			currentPoints--;
			currentPointsText.setText(std::to_string(currentPoints));
		}

		if (currentPoints == 0 && !mergeShapes)
		{
			mergeShapes = true;
			showOrignalFinished = true;

			currentShapePoints->clear();

			// need to change the target potions so that they show the new point reorders to be thge closest values
			targetShape = closest.findClosest(*currentShape, *currentGameShape.points);
			drawOrder = closest.listOrder;

			// calculate the points for the player to earn based on the distance
			int runningTotal = 0;
			for (size_t i = 0; i < currentShape->size(); i++)
			{
				//Root ((x2 - x1)2 + (y2 - y1)2 + (z2 - z1)2 )
				int X1 = currentShape->at(i).position.x;
				int Y1 = currentShape->at(i).position.y;
				int Z1 = currentShape->at(i).position.z;
				int X2 = targetShape.at(i).position.x;
				int Y2 = targetShape.at(i).position.y;
				int Z2 = targetShape.at(i).position.z;
				
				int p1 = pow(X2 - X1, 2);
				int p2 = pow(Y2 - Y1, 2);
				int p3 = pow(Z2 - Z1, 2);
				int distance = sqrtf(p1 + p2 + p3);
				runningTotal += distance;
			}
			playerScore.setText(std::to_string(runningTotal));

		}
	}
	glutPostRedisplay();
}


void chooseShape()
{
	int ran = rand() % (7 - 0 + 1) + 0;
	switch (ran)
	{
	case 0:
		currentGameShape = Square(Vector3(300, 300, 0), 100, 100);
		break;
	case 1:
		currentGameShape = Triangle(Vector3(300, 300, 0), 100, 100);
		break;
	case 2:
		currentGameShape = Star(Vector3(300, 300, 0), 100);
		break;
	case 3:
		currentGameShape = Pentagon(Vector3(300, 300, 0), 100);
		break;
	case 4:
		currentGameShape = Cross(Vector3(300, 300, 0), 100, 100);
		break;
	case 5:
		currentGameShape = Rhombus(Vector3(300, 300, 0), 100, 100);
		break;
	case 6:
		currentGameShape = Trapezium(Vector3(300, 300, 0), 100, 100);
		break;
	case 7:
		currentGameShape = Arrow(Vector3(300, 300, 0), 100, 100);
		break;
	default:
		currentGameShape = Square(Vector3(300, 300, 0), 100, 100);
		break;
	}

}

void init()
{
	chooseShape();
	currentPoints = currentGameShape.points->size();
	currentPointsText.setText(std::to_string(currentPoints));

	learnStartTime = std::chrono::system_clock::now();
}

void keyPressed(unsigned char key, int x, int y)
{
	if (key == 'r')
	{
		// respawn a new object
		mergeShapes = false;
		showOrignalFinished = false;
		showOrignalShape = true;
		currentShape->clear();
		currentShapePoints->clear();
		init();

	}
}



int main(int argc, char** argv) {
	glutInit(&argc, argv);
	srand(time(NULL));
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

