#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "glut.h"
#include "Vector3.h"



class Point
{
public:
	// Constructer
	Point(Vector3, Color, float, float);

	// variables
	Vector3 position;
	Color color;
	float scale;
	float rotation;

	Point operator * (float k) {
		return Point(position * k, color, scale, rotation);
	}

	Point operator + (Point p) {
		return Point(position + p.position, color, scale, rotation);
	}
};

