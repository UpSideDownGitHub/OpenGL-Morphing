#include "Text.h"

// Constructor
Text::Text(){}
Text::Text(Vector3 val1, Color val2, std::string val3)
{
	position = val1;
	color = val2;
	text = val3;
}


// Methods
void Text::drawText()
{
	glPushMatrix();
	glColor4f(color.r, color.g, color.b, color.a);
	glRasterPos2i(position.x, position.y);
	void* font = GLUT_BITMAP_9_BY_15;
	for (std::string::iterator i = text.begin(); i != text.end(); ++i)
	{
		char c = *i;
		glutBitmapCharacter(font, c);
	}

	glPopMatrix();
	glClearColor(0, 0, 0, 1);
}

// getters & setters
Vector3 Text::getPosition() { return position; }
void Text::setPosition(Vector3 val) { position = val; }
Color Text::getColor() { return color; }
void Text::setColor(Color val) { color = val; }
std::string Text::getText() { return text; }
void Text::setText(std::string val) { text = val; }
