#pragma once
#include <math.h>
#include "Point.h"
#include "Vector3.h"

# define PI 3.14159265358979323846 

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

class Triangle : public Shape
{
public:
	// constructor
	Triangle(Vector3 pos, float width, float height);

	// variables
	float width, height;
};

class Star : public Shape
{
public:
	// constructor
	Star(Vector3 pos, float radius);

	//variables
	float radius;
};

class Pentagon : public Shape
{
public:
	// constructor
	Pentagon(Vector3 pos, float radius);

	// variables
	float radius;
};

class Cross : public Shape
{
public:
	// constructor
	Cross(Vector3 pos, float height, float width);

	// variables
	float height, width;
};

class Rhombus : public Shape
{
public:
	// constructor
	Rhombus(Vector3 pos, float height, float width);

	// variables
	float height, width;
};

class Trapezium : public Shape
{
public:
	// constructor
	Trapezium(Vector3 pos, float height, float width);

	// variables
	float height, width;
};

class Arrow : public Shape
{
public:
	// constructor
	Arrow(Vector3 pos, float height, float width);

	// variables
	float height, width;
};