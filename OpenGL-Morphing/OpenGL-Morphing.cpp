
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
#include "MainMenu.h"
#include "ResultsScreen.h"

// method definitions
void init();
void reset();
void newShape();
void mainGameLoop();
void mainGameMouseClicked(int button, int state, int x, int y);
void mainMenuMouseClicked(int button, int state, int x, int y);
void resultsMenuMouseClicked(int button, int state, int x, int y);
	
// instance of the closest function
Closest closest = Closest();
// create the list of the draw order
std::vector<int> drawOrder;

// the shape to move to
std::vector<Point> targetShape = std::vector<Point>();
std::vector<Point> oldShapePoints = std::vector<Point>();
std::vector<Point> newShapePoints = std::vector<Point>();

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
bool changingShapes = false;

// Gameplay Shapes
Shape currentGameShape = Square(Vector3(300, 300, 0), 100, 100);

// Points
std::chrono::system_clock::time_point learnStartTime;
int currentPoints;

// changing shape
std::chrono::system_clock::time_point changeShapeStartTime;
float shapeChangeTime = 5;

// Timer
float learnTime = 5;

// interpolation
float morphTime = 0.0;

// score
int score = 0;
int bestScore = 9999;

// Level Systsem
int level = 0, maxLevels = 8;
float levelStartTime = 2;
int previousShape = 0;
std::chrono::system_clock::time_point endStartTime;

// Text that will be shown on screen
Text scoreText = Text(Vector3(275,20,0), Color(255,255,255,255), "Score");
Text playerScore = Text(Vector3(275,35,0), Color(255,255,255,255), "0");
Text pointsLeftText = Text(Vector3(250,575,0), Color(255,255,255,255), "Points Left");
Text currentPointsText = Text(Vector3(295,595,0), Color(255,255,255,255), "0");
Text learnText = Text(Vector3(265, 50, 0), Color(255,0,0,255), "Learn");
Text drawText = Text(Vector3(270, 50, 0), Color(0,255,0,255), "Draw");
Text welldoneText = Text(Vector3(255, 50, 0), Color(0,0,255,255), "Well Done");
Text nextShapeText = Text(Vector3(255, 50, 0), Color(0,255,255,255), "Next Shape");
Text currentLevelText = Text(Vector3(10, 20, 0), Color(255, 255, 255, 255), "Level: ");
Text currentLevel = Text(Vector3(30, 35, 0), Color(255, 255, 255, 255), "1");


// Main Menu
bool inMainMenu = true;
MainMenu mainMenu = MainMenu();

// Results Screen
bool inResultsScreen = false;
ResultsScreen resultsScreen = ResultsScreen();


/*
	this will check if enough time has passed for the learning time
	then if there is it will start the memorisation phase of the game
*/
void checkTime()
{
	// get the current elasped time
	auto elapsedTime = std::chrono::system_clock::now() - learnStartTime;
	
	// if enogh time has passed
	if (std::chrono::duration<float>(elapsedTime).count() > learnTime)
	{
		// hide the orignal and let the player start pressing
		showOrignalShape = false;
	}
}

float ROT_TEST = 0;

/*
	this function is called on each idleing frame
*/
void idle()
{
	// increase the morph time & and rotation test
	morphTime += 0.0000001;
	ROT_TEST += 0.05;
}

/*
	this function will interpolate through the drawn shape and the actual shape
	showing the player how close there where to the actual shape
*/
void interpolateShape()
{
	// Interpolation of all of the potins of the shape
	// to create the merging of the shapes
	for (size_t i = 0; i < currentShape->size(); i++)
	{
		currentShape->at(i) = currentShape->at(i) * (1.0 - morphTime) + targetShape.at(i) * morphTime;
	}	

	// draw the outline of the interpolating shape
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f(255 , 0, 0, 255); 
	// draw all of the new position of the new shape
	for (size_t i = 0; i < currentShape->size(); i++)
	{
		glVertex3f(currentShape->at(i).position.x, currentShape->at(i).position.y, currentShape->at(i).position.z);
	}
	glEnd();
	glPopMatrix();
}

/*
	interpolate through the current shape and the next shape to show,
	there will also be a rotation applied
*/
void interpolateToNextShape()
{
	// if there is more points in the oldShape then remove enough
	// to match the new shape (so the merge can be done)
	if (oldShapePoints.size() > newShapePoints.size())
	{
		// for the ammount of differences
		int tempCount = oldShapePoints.size() - newShapePoints.size();
		for (size_t i = 0; i < tempCount; i++)
		{
			// remove an item from the oldShapePoints
			oldShapePoints.pop_back();
		}
	}
	// if there is more points in the new shape then add points
	// to the old shape to match the new shape
	if (newShapePoints.size() > oldShapePoints.size())
	{
		// find the ammount of points there is difference
		int oldLast = oldShapePoints.size() - 1;
		int tempCount = newShapePoints.size() - oldShapePoints.size();
		// for the ammount of items
		for (size_t i = 0; i < tempCount; i++)
		{
			// ad another point at the position of the last item in the list
			oldShapePoints.push_back(Point(oldShapePoints.at(oldLast).position, oldShapePoints.at(oldLast).color,
				oldShapePoints.at(oldLast).scale, oldShapePoints.at(oldLast).rotation));
		}
	}

	// Interpolation of all of the points of the shape
	for (size_t i = 0; i < oldShapePoints.size(); i++)
	{
		oldShapePoints.at(i) = oldShapePoints.at(i) * (1.0 - morphTime/3) + newShapePoints.at(i) * morphTime * 0.33;
	}

	// draw the outline of the interpolating shape
	glPushMatrix();
	// rotate the object (to do this around the correct center move to position
	// rotate then move back)
	glTranslatef(300, 300, 0);
	glRotatef(ROT_TEST, 0, 0, 1);
	glTranslatef(-300, -300, -0);
	
	// begin the line loop
	glBegin(GL_LINE_LOOP);
	glColor4f(255, 0, 0, 255);
	
	// move all & draw all of the old shape points
	for (size_t i = 0; i < oldShapePoints.size(); i++)
	{
		glVertex3f(oldShapePoints.at(i).position.x, oldShapePoints.at(i).position.y, oldShapePoints.at(i).position.z);
	}
	// end the line loop and finish drawning the matrix
	glEnd();
	glPopMatrix();
}
	
/*
	when this is called it will manage drawning all elements to the screen
*/
void display()
{
	// if in the main menu then draw the main menu
	if (inMainMenu)
		mainMenu.drawMainMenu();
	// if in the results screen then draw the results screen
	else if (inResultsScreen)
		resultsScreen.drawResultsScreen();
	// if in the main game then draw the main game loop
	else
		mainGameLoop();
}

/*
	this function will handle the main game loop and draw all of the 
	required elements
*/
void mainGameLoop()
{
	// clear the color and reset the Color & Depth Buffer bits
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// call checkTime & idle
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
	currentLevelText.drawText();
	currentLevel.drawText();

	// changing shape to the next shape
	if (changingShapes)
	{
		// if allready changed the stop changing
		if (morphTime > 1.0) morphTime = 1.0;
		
		// call interpolate to the next shape
		interpolateToNextShape();
		
		// update the learn start time
		learnStartTime = std::chrono::system_clock::now();
		
		// calculate the total elapsed time
		auto elapsedTime = std::chrono::system_clock::now() - changeShapeStartTime;
		// if enough time has passed to stop showing the shape
		if (std::chrono::duration<float>(elapsedTime).count() > shapeChangeTime)
			changingShapes = false;
		
		// draw next shape text
		nextShapeText.drawText();

		// Draw the mouse pointer
		glPopMatrix();
		glColor4f(255, 255, 255, 255);
		mousePointer.drawShape(Vector3(mouseX, mouseY, 0));
		glPopMatrix();
	
		// set the matrix mode and load the Identiy and swap buffers to finalize the drawing
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glutSwapBuffers();
		return;
	}

	// check for time and then respawn the game
	if (showOrignalFinished)
	{
		// draw the well done text to the screen
		welldoneText.drawText();
		
		// calcualte the elapsed time
		auto elapsedTime = std::chrono::system_clock::now() - endStartTime;

		// if it is time to show a new shape
		if (std::chrono::duration<float>(elapsedTime).count() > levelStartTime)
		{
			// increase the level 
			level++;
			// and update the level text
			currentLevel.setText(std::to_string(level+1));
			// if not the last level call new shape to load new level
			if (level < maxLevels)
				newShape();
			// otherwise end the game 
			else
			{
				// if they achived a new best score then update the best score
				if (score < bestScore)
					bestScore = score;
				// show the results screen
				resultsScreen.updateScores(score, bestScore);
				inResultsScreen = true;
				reset();
			}
		}
	}

	// if showing the orignal shape or showing the finished shape
	if (showOrignalShape || showOrignalFinished)
	{
		// draw the current game shape and if learning then draw the learn text
		if (!showOrignalFinished)
			learnText.drawText();
		currentGameShape.drawShapeOutline();
	}
	// draw the drawning text 
	else
		drawText.drawText();


	// interpolate the shape from the one drawn to the correct shape
	if (mergeShapes)
	{
		// if finished morphing then stop morphing
		if (morphTime > 1.0) morphTime = 1.0;
		
		// call interpolate shapes
		interpolateShape();
	}
	// draw the player shape
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

		// draw the current shape to the screen
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
	glColor4f(255, 255, 255, 255);
	mousePointer.drawShape(Vector3(mouseX, mouseY, 0));
	glPopMatrix();

	// set the matrix mode and load the Identiy and swap buffers to finalize the drawing
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutSwapBuffers();
}

/*
	this will record the motion of the mouse pointer and save its position
*/
void motion(int x, int y) 
{
	mouseX = x;
	mouseY = y;
}

/*
	this function will be called when the mount button is clicked
*/
void mouseClicks(int button, int state, int x, int y)
{
	// if chaning shapes then do nothing
	if (changingShapes)
		return;
	// if in the main menu call the main menu check mouse clicked 
	if (inMainMenu)
		mainMenuMouseClicked(button, state, x, y);
	// if in the results screen call the results screen mouse clicked
	else if (inResultsScreen)
		resultsMenuMouseClicked(button, state, x, y);
	// if in the game call game mouse clicked function
	else
		mainGameMouseClicked(button, state, x, y);
}

/*
	this function will check for mouse buttons pressed in the results menu
*/
void resultsMenuMouseClicked(int button, int state, int x, int y)
{
	// If left mouse button pressed
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		// reload the game
		inMainMenu = false;
		inResultsScreen = false;
		learnStartTime = std::chrono::system_clock::now();
	}
	// if the right mouse button is pressed 
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		// load the main menu
		inMainMenu = true;
		inResultsScreen = false;
	}
}

/*
	the function will check for mouse buttons pressed in the main menu
*/
void mainMenuMouseClicked(int button, int state, int x, int y)
{
	// If left mouse button pressed
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		// this will load the main menu
		inMainMenu = false;
		learnStartTime = std::chrono::system_clock::now();
	}
	glutPostRedisplay();
}

/*
	the function will check for mouse buttons pressed in the main game
*/
void mainGameMouseClicked(int button, int state, int x, int y)
{
	// If left mouse button pressed
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		// if there have been no points pressed
		if (currentPoints > 0)
		{
			// turn off the orignal shape
			showOrignalShape = false;
			
			// make a point in the position of the mouse
			Point point = Point(Vector3(x, y, 0), Color(255, 0, 0, 255), 1, 0);
			currentShape->push_back(point);
			Square position = Square(Vector3(x, y, 0), 10, 10);
			currentShapePoints->push_back(position);
			
			// take one of the points of the player
			currentPoints--;
			currentPointsText.setText(std::to_string(currentPoints));
		}
		
		// if the player has no more points
		if (currentPoints == 0 && !mergeShapes)
		{
			// end of the current level
			mergeShapes = true;
			showOrignalFinished = true;

			// remove the player placed points
			currentShapePoints->clear();

			// start the timer to end the round
			endStartTime = std::chrono::system_clock::now();

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
			// add the score to the total and update the text
			score += runningTotal;
			playerScore.setText(std::to_string(score));

		}
	}
	glutPostRedisplay();
}

/*
	this function will select the current shape to show to the player
*/
void chooseShape()
{
	// change the shape based on the level
	switch (level)
	{
	case 0:
		currentGameShape = Triangle(Vector3(300, 300, 0), 100, 100);
		break;
	case 1:
		currentGameShape = Square(Vector3(300, 300, 0), 100, 100);
		break;
	case 2:
		currentGameShape = Trapezium(Vector3(300, 300, 0), 100, 100);
		break;
	case 3:
		currentGameShape = Rhombus(Vector3(300, 300, 0), 100, 100);
		break;
	case 4:
		currentGameShape = Pentagon(Vector3(300, 300, 0), 100);
		break;
	case 5:
		currentGameShape = Arrow(Vector3(300, 300, 0), 100, 100);
		break;
	case 6:
		currentGameShape = Star(Vector3(300, 300, 0), 100);		
		break;
	case 7:
		currentGameShape = Cross(Vector3(300, 300, 0), 100, 100);
		break;
	default:
		currentGameShape = Triangle(Vector3(300, 300, 0), 100, 100);
		break;
	}

}

/*
	this is called to inisile the game
*/
void init()
{
	// pick a new shape
	chooseShape();
	// get all of the points that will be used and update the start time
	newShapePoints = *currentGameShape.points;
	currentPoints = currentGameShape.points->size();
	currentPointsText.setText(std::to_string(currentPoints));
	learnStartTime = std::chrono::system_clock::now();
}

/*
	reset the game so it is ready to play again
*/
void reset()
{
	// pick the new shape
	chooseShape();
	// get all of the current points
	currentPoints = currentGameShape.points->size();
	currentPointsText.setText(std::to_string(currentPoints));
	learnStartTime = std::chrono::system_clock::now();
	// reset all of the varaibles
	showOrignalShape = true;
	showOrignalFinished = false;
	mergeShapes = false;
	morphTime = 0.0;
	score = 0;
	playerScore.setText(std::to_string(score));
	level = 0;
	levelStartTime = 2;
	currentShape->clear();
}

/*
	when this is called a new shape will be spawned
*/
void newShape()
{
	// change to the new shape
	changingShapes = true;
	oldShapePoints = *currentGameShape.points;
	changeShapeStartTime = std::chrono::system_clock::now();
	ROT_TEST = 0;
	morphTime = 0;

	// respawn a new object
	mergeShapes = false;
	showOrignalFinished = false;
	showOrignalShape = true;
	currentShape->clear();
	currentShapePoints->clear();
	init();
}

/*
	used for testing
*/
void keyPressed(unsigned char key, int x, int y)
{
}

/*
	the main function of the game
*/
int main(int argc, char** argv) {
	// set up the GLUT window
	glutInit(&argc, argv);
	srand(time(NULL));
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(600, 600);
	glutCreateWindow("GLUT");
	
	// setup all basic functions
	glutDisplayFunc(display);
	glutMouseFunc(mouseClicks);
	glutPassiveMotionFunc(motion);	
	glutKeyboardFunc(keyPressed);
	glutIdleFunc(display);
	init();
	
	// set the main loop
	glutMainLoop();
	return 0;
}