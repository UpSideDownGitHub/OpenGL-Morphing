﻿#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "glut.h"
#include "Vector3.h"

#ifndef POINTDEFINTION
#define POINTDEFINTION

class Point
{
public:
	// Constructer
	Point(Vector3 pos, Color col, float sca, float rot);

	// variables
	Vector3 position;
	Color color;
	float scale;
	float rotation;
	
	// Operators
	Point operator * (float k) {
		return Point(position * k, color, scale, rotation);
	}
	Point operator + (Point p) {
		return Point(position + p.position, color, scale, rotation);
	}
	Point operator - (Point p) {
		return Point(position - p.position, color, scale, rotation);
	}
};
#endif
