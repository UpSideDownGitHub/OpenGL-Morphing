#pragma once

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

class ResultsScreen
{
private:
public:
	// Constructor
	ResultsScreen();

	// Varaibles
	Text titleText;
	Text scoreText;
	Text actualScoreText;
	Text bestText;
	Text actualBestText;
	Text playAgainMessage;
	Text mainMenuMessage;


	// Methods
	void drawResultsScreen();
	void updateScores(int score, int bestScore);
};

