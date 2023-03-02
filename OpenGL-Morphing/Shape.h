#pragma once
#include "Point.h"
#include "Vector3.h"

class Shape
{
private:

public:
	Shape();
	// variables
	std::vector<Point>* points = new std::vector<Point>();

	//functions
	void drawShape(Vector3);
	void drawShape();
	void drawShapeOutline();

};

class Square : public Shape
{
public:
	// constructor
	Square(Vector3 pos, float width, float height);

	// variables
	float width;
	float height;
};

