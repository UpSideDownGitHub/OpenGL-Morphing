#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "glut.h"


class Vector3
{
public:
	// Constructer
	Vector3();
	Vector3(float, float, float);
	
	// Variables
	float x;
	float y;
	float z;

	// Functions
	float magnitude();
};

class Color
{
public:
	// Constructor
	Color();
	Color(float, float, float, float);

	// Varaibles
	float r;
	float g;
	float b;
	float a;
};

