#include "MainMenu.h"

/*
	this class will set up all of the text for the main menu and also setup a button 
	that when clicked will play the game
*/
MainMenu::MainMenu() 
{ 
	this->titleText = Text(Vector3(250, 100, 0), Color(0, 255, 0, 255), "Shape Morphing");
	this->instructionsTitleText = Text(Vector3(20, 200, 0), Color(255, 255, 255, 255), "Instructions:");
	this->instructionsline1Text = Text(Vector3(30, 250, 0), Color(255, 255, 255, 255), "You must place all of the corners of the given shape,");
	this->instructionsline2Text = Text(Vector3(30, 275, 0), Color(255, 255, 255, 255), "you will have 5 seconds to learn the shape before it disapears,");
	this->instructionsline3Text = Text(Vector3(30, 300, 0), Color(255, 255, 255, 255), "then you will have to draw the corners of the shape,");
	this->instructionsline4Text = Text(Vector3(30, 325, 0), Color(255, 255, 255, 255), "the closer you get the better you do.");
	this->instructionsline5Text = Text(Vector3(30, 350, 0), Color(255, 255, 255, 255), "Lowest Score WINS over 5 shapes");
	this->instructionsline6Text = Text(Vector3(30, 400, 0), Color(255, 255, 255, 255), "NOTE:");
	this->instructionsline7Text = Text(Vector3(30, 425, 0), Color(255, 255, 255, 255), "the points you draw will in order go to there closest");
	this->instructionsline8Text = Text(Vector3(30, 450, 0), Color(255, 255, 255, 255), "point so i recommend doing them in order otherwise you");
	this->instructionsline9Text = Text(Vector3(30, 475, 0), Color(255, 255, 255, 255), "will lose alot of points, and it wont look");
	this->instructionsline10Text = Text(Vector3(30, 500, 0), Color(255, 255, 255, 255), "nice when it is finshed merging");
	this->clickToStartText = Text(Vector3(230, 550, 0), Color(255, 255, 255, 255), "(Click To Continue)");

/*
You must place all of the corners of the given shape,
you will have 5 seconds to learn the shape before it disapears,
then you will have to draw the corners of the shape, 
the closer you get the better you do. 
Lowest Score WINS over 5 shapes

NOTE:
the points you draw will in order go to there closest
point so i recommend doing them in order otherwise you
will lose alot of points, and it wont look
nice when it is finshed merging
*/
}

/*
	this function will draw all of the elements of the main menu to the
	screen
*/
void MainMenu::drawMainMenu()
{
	// clear the color and reset the Color & Depth Buffer bits
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set up Projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const double w = glutGet(GLUT_WINDOW_WIDTH);
	const double h = glutGet(GLUT_WINDOW_HEIGHT);
	glOrtho(0, w, h, 0, -100, 100);
	
	// Draw all of the elements to the screen
	titleText.drawText();
	instructionsTitleText.drawText();
	instructionsline1Text.drawText();
	instructionsline2Text.drawText();
	instructionsline3Text.drawText();
	instructionsline4Text.drawText();
	instructionsline5Text.drawText();
	instructionsline6Text.drawText();
	instructionsline7Text.drawText();
	instructionsline8Text.drawText();
	instructionsline9Text.drawText();
	instructionsline10Text.drawText();
	clickToStartText.drawText();
	
	// set the matrix mode and load the Identiy and swap buffers to finalize the drawing
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutSwapBuffers();
}
