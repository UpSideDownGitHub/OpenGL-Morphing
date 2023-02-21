#pragma once
#include "Point.h"
#include "Vector3.h"

class Shape
{
private:

public:

};

class Square : Shape
{
public:
	// constructor
	Square(Vector3 pos, float width, float height);

	// variables
	std::vector<Point>* points = new std::vector<Point>();
	float width;
	float height;

	//functions
	void drawShape(Vector3);

	// operator
};

