﻿#include "Vector3.h"

/*
	this function will calcualte the magnitude of the vector
*/
float Vector3::magnitude()
{
	// √(x2 + y2 + z2)
	return sqrtf(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

// Constructors
Vector3::Vector3() {}
Vector3::Vector3(float X, float Y, float Z)
{
	this->x = X;
	this->y = Y;
	this->z = Z;
}

// Constructors for color
Color::Color() {}
Color::Color(float R, float G, float B, float A)
{
	this->r = R;
	this->g = G;
	this->b = B;
	this->a = A;
}