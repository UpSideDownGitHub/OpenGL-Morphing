#include "Point.h"

Point::Point(Vector3 pos, Color col, float sca, float rot)
{
	this->position = pos;
	this->color = col;
	this->scale = sca;
	this->rotation = rot;
}
