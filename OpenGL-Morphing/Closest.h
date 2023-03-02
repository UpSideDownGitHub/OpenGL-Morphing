#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "glut.h"
#include "Point.h"
#include "Shape.h"
#include "Vector3.h"
#include "Text.h"

class Closest
{
private:

public:
	// Constructor
	Closest();

	// Variables
	std::vector<int> listOrder;

	// Methods
	std::vector<Point> findClosest(std::vector<Point> playerPoints, std::vector<Point> targetPoints);
	float distance(Vector3 point1, Vector3 point2);


	// Getters & Setters
};

