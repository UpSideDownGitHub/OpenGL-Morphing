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
	Point point = Point(Vector3(pos.x - width / 2, pos.y + height / 2, pos.z), Color(0, 0, 0, 255), 1, 0);
	points->push_back(point);
	point = Point(Vector3(pos.x + width / 2, pos.y + height / 2, pos.z), Color(0, 0, 0, 255), 1, 0);
	points->push_back(point);
	point = Point(Vector3(pos.x + width / 2, pos.y - height / 2, pos.z), Color(0, 0, 0, 255), 1, 0);
	points->push_back(point);
	point = Point(Vector3(pos.x - width / 2, pos.y - height / 2, pos.z), Color(0, 0, 0, 255), 1, 0);
	points->push_back(point);
	
}

void Square::drawShape(Vector3 newPos)
{
	glTranslatef(newPos.x, newPos.y, newPos.z);

	glBegin(GL_QUADS);
	for (size_t i = 0; i < points->size(); i++)
	{
		glVertex3f(points->at(i).position.x, points->at(i).position.y, points->at(i).position.z);
	}
	glEnd();
}
void Square::drawShape()
{
	glBegin(GL_QUADS);
	for (size_t i = 0; i < points->size(); i++)
	{
		glVertex3f(points->at(i).position.x, points->at(i).position.y, points->at(i).position.z);
	}
	glEnd();
}
void Square::drawShapeOutline()
{
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f(255, 255, 255, 255);
	glVertex3f(points->at(0).position.x, points->at(0).position.y, points->at(0).position.z);
	glVertex3f(points->at(1).position.x, points->at(1).position.y, points->at(1).position.z);
	glVertex3f(points->at(2).position.x, points->at(2).position.y, points->at(2).position.z);
	glVertex3f(points->at(3).position.x, points->at(3).position.y, points->at(3).position.z);

	glEnd();
	glPopMatrix();
}
