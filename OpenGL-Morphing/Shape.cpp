#include "Shape.h"

Square::Square(Vector3 pos, float width, float height)
{
	// need to find the point for the square shape
	/*
	* (-,+) (+,+)
	*   .    .
	* 
	*   .    .
	* (-,-) (+,-)
	* 
	* Point point = Point(Vector3(x, y, 0), Color(0, 0, 0, 255), 1, 0);
		currentShape->push_back(point);
	*/

	this->width = width;
	this->height = height;

	//Vector3 pos, Color col, float sca, float rot
	Point point = Point(Vector3(pos.x - width/2, pos.y + height/2, pos.z), Color(0, 0, 0, 255), 1, 0);
	points->push_back(point);

	point = Point(Vector3(pos.x + width/2, pos.y + height/2, pos.z), Color(0, 0, 0, 255), 1, 0);
	points->push_back(point);

	point = Point(Vector3(pos.x - width/2, pos.y - height/2, pos.z), Color(0, 0, 0, 255), 1, 0);
	points->push_back(point);

	point = Point(Vector3(pos.x + width/2, pos.y - height/2, pos.z), Color(0, 0, 0, 255), 1, 0);
	points->push_back(point);
}

void Square::drawShape(Vector3 newPos)
{
	glTranslatef(newPos.x, newPos.y, newPos.z);

	glBegin(GL_QUAD_STRIP);
	for (size_t i = 0; i < points->size(); i++)
	{
		glVertex3f(points->at(i).position.x, points->at(i).position.y, points->at(i).position.z);
	}
	glEnd();
}
void Square::drawShape()
{
	glBegin(GL_QUAD_STRIP);
	for (size_t i = 0; i < points->size(); i++)
	{
		glVertex3f(points->at(i).position.x, points->at(i).position.y, points->at(i).position.z);
	}
	glEnd();
}
