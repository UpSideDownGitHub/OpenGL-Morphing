#pragma once

#include "Point.h"
#include "Shape.h"
#include "Vector3.h"

class Text
{
private:
	//Variables
	Vector3 position;
	Color color;
	std::string text;
public:
	// Constructor
	Text();
	Text(Vector3, Color, std::string);

	// Methods
	void drawText();

	// Getters & Setters
	Vector3 getPosition();
	void setPosition(Vector3);
	Color getColor();
	void setColor(Color);
	std::string getText();
	void setText(std::string);
};

