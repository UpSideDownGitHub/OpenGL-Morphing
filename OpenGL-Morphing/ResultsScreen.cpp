#include "ResultsScreen.h"

ResultsScreen::ResultsScreen()
{
	this->titleText = Text(Vector3(260, 100, 0), Color(0, 255, 0, 255), "Results");
	this->scoreText = Text(Vector3(262, 200, 0), Color(0, 255, 0, 255), "Score:");
	this->actualScoreText = Text(Vector3(264, 220, 0), Color(0, 255, 0, 255), "1000");
	this->bestText = Text(Vector3(245, 300, 0), Color(0, 255, 0, 255), "Best Score:");
	this->actualBestText = Text(Vector3(264, 320, 0), Color(0, 255, 0, 255), "1000");
	this->playAgainMessage = Text(Vector3(10, 550, 0), Color(0, 255, 0, 255), "(Left Click For Play Again)");
	this->mainMenuMessage = Text(Vector3(350, 550, 0), Color(0, 255, 0, 255), "(Right Click For Main Menu)");
}

void ResultsScreen::updateScores(int score, int bestScore)
{
	actualScoreText.setText(std::to_string(score));
	actualBestText.setText(std::to_string(bestScore));
}

void ResultsScreen::drawResultsScreen()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set up Projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const double w = glutGet(GLUT_WINDOW_WIDTH);
	const double h = glutGet(GLUT_WINDOW_HEIGHT);
	glOrtho(0, w, h, 0, -100, 100);

	titleText.drawText();
	scoreText.drawText();
	actualScoreText.drawText();
	bestText.drawText();
	actualBestText.drawText();
	playAgainMessage.drawText();
	mainMenuMessage.drawText();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutSwapBuffers();
}