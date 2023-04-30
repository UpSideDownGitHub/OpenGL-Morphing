#include "Shape.h"

Shape::Shape(){}

/*
	this will handle drawning the shape to the screen at given position
*/
void Shape::drawShape(Vector3 newPos)
{
	// move the shape to the given poisition
	glTranslatef(newPos.x, newPos.y, newPos.z);
	
	// draw the shape using quads
	glBegin(GL_QUADS);
	// draw each point of the shape
	for (size_t i = 0; i < points->size(); i++)
	{
		glVertex3f(points->at(i).position.x, points->at(i).position.y, points->at(i).position.z);
	}
	glEnd();
}
/*
	this is used to draw the shape where it is 
*/
void Shape::drawShape()
{
	// draw with quads
	glBegin(GL_QUADS);
	// draw each position to the screen
	for (size_t i = 0; i < points->size(); i++)
	{
		glVertex3f(points->at(i).position.x, points->at(i).position.y, points->at(i).position.z);
	}
	glEnd();
}
/*
	this function will handle drawning the outline of the shape
*/
void Shape::drawShapeOutline()
{
	glPushMatrix();
	// draw using a line loop
	glBegin(GL_LINE_LOOP);
	glColor4f(255, 255, 255, 255);
	// draw each point of the shape
	for (size_t i = 0; i < points->size(); i++)
	{
		glVertex3f(points->at(i).position.x, points->at(i).position.y, points->at(i).position.z);
	}
	glEnd();
	glPopMatrix();
}

/*
	draw the outline of the shape with a rotation
*/
void Shape::drawShapeOutline(float rot)
{
	glPushMatrix();
	
	// rotate the shape
	glTranslatef(300, 300, 0);
	glRotatef(rot, 0, 0, 1);
	glTranslatef(-300, -300, -0);

	// draw the shape with a line loop
	glBegin(GL_LINE_LOOP);
	glColor4f(255, 255, 255, 255);
	// draw all of the points of the shape
	for (size_t i = 0; i < points->size(); i++)
	{
		glVertex3f(points->at(i).position.x, points->at(i).position.y, points->at(i).position.z);
	}
	glEnd();
	glPopMatrix();
}

// Sqaure
Square::Square(Vector3 pos, float width, float height)
{
	// need to find the point for the square shape
	/*
	* (-,+) (+,+)
	*   .    .
	* 
	*   .    .
	* (-,-) (+,-)
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

// Triangle
Triangle::Triangle(Vector3 pos, float width, float height)
{
	// need to find the point for the square shape
	/*
	*    (0,+)
	*      .  
	*
	*   .    .
	* (-,+) (+,+)
	*/
	this->width = width;
	this->height = height;

	//Vector3 pos, Color col, float sca, float rot
	Point point = Point(Vector3(pos.x, pos.y - height/2, pos.z), Color(255, 255, 255, 255), 1, 0);
	points->push_back(point);
	point = Point(Vector3(pos.x - width/2, pos.y + height/2, pos.z), Color(255, 255, 255, 255), 1, 0);
	points->push_back(point);
	point = Point(Vector3(pos.x + width / 2, pos.y + height/2, pos.z), Color(255, 255, 255, 255), 1, 0);
	points->push_back(point);
}

// Start
Star::Star(Vector3 pos, float radius)
{
	// equation for the points on a start
	//(rcos(2PIk/5+PI/2),rsin(2PIk/5+PI/2))

	this->radius = radius;
	std::vector<Point>* outsidePoints = new std::vector<Point>();
	std::vector<Point>* insidePoints = new std::vector<Point>();

	// Draw the outer 5 Points
	for (size_t i = 0; i < 5; i++)
	{
		float X = radius * cos((2 * PI * i / 5) + (PI / 2));
		float Y = radius * sin((2 * PI * i / 5) + (PI / 2));
		Point point = Point(Vector3(X + pos.x, Y + pos.y, pos.z), Color(255, 255, 255, 255), 1, 0);
		outsidePoints->push_back(point);
	}
	// Draw the inner 5 Points
	for (size_t i = 0; i < 5; i++)
	{
		float X = (radius / 2) * cos((2 * PI * i / 5) + (PI / 2) + (PI / 5));
		float Y = (radius / 2) * sin((2 * PI * i / 5) + (PI / 2) + (PI / 5));
		Point point = Point(Vector3(X + pos.x, Y + pos.y, pos.z), Color(255, 255, 255, 255), 1, 0);
		insidePoints->push_back(point);
	}
	// Connect all of the points
	for (size_t i = 0; i < 5; i++)
	{
		points->push_back(outsidePoints->at(i));
		points->push_back(insidePoints->at(i));
	}
}

// Pentagon
Pentagon::Pentagon(Vector3 pos, float radius)
{
	// equation for the points on a start
	//(rcos(2PIk/5+PI/2),rsin(2PIk/5+PI/2))

	this->radius = radius;

	// Draw the outer 5 Points
	for (size_t i = 0; i < 5; i++)
	{
		float X = radius * cos((2 * PI * i / 5) +(80*PI / 267)); // values make point at top
		float Y = radius * sin((2 * PI * i / 5) +(80*PI / 267));
		Point point = Point(Vector3(X + pos.x, Y + pos.y, pos.z), Color(255, 255, 255, 255), 1, 0);
		points->push_back(point);
	}
}

// Cross
Cross::Cross(Vector3 pos, float height, float width)
{
	// need to find the point for the cross shape
	/*
	*      (-,+2)(+,+2)
	*        .    .   
	*(-2,+)(-,+)(+,+)(+2,+)
	*   .    .    .    .	
	*(-2,-)(-.-)(+,-)(+2,-)
	*   .    .    .    .
	*     (-,-2)(+,-2)
	*        .    .
	*/
	this->height = height;
	this->width = width;

	//Vector3 pos, Color col, float sca, float rot
	Point point = Point(Vector3(pos.x - width / 3, pos.y + height, pos.z), Color(0, 0, 0, 255), 1, 0); // 1
	points->push_back(point);
	point = Point(Vector3(pos.x + width / 3, pos.y + height, pos.z), Color(0, 0, 0, 255), 1, 0);// 2
	points->push_back(point);
	point = Point(Vector3(pos.x + width / 3, pos.y + height/3, pos.z), Color(0, 0, 0, 255), 1, 0);// 3
	points->push_back(point);
	point = Point(Vector3(pos.x + width, pos.y + height/3, pos.z), Color(0, 0, 0, 255), 1, 0);// 4
	points->push_back(point);
	point = Point(Vector3(pos.x + width, pos.y - height/3 , pos.z), Color(0, 0, 0, 255), 1, 0);// 5
	points->push_back(point);
	point = Point(Vector3(pos.x + width/3, pos.y - height / 3, pos.z), Color(0, 0, 0, 255), 1, 0);// 6
	points->push_back(point);
	point = Point(Vector3(pos.x + width/3, pos.y - height, pos.z), Color(0, 0, 0, 255), 1, 0);// 7
	points->push_back(point);
	point = Point(Vector3(pos.x - width / 3, pos.y - height, pos.z), Color(0, 0, 0, 255), 1, 0);// 8
	points->push_back(point);
	point = Point(Vector3(pos.x - width / 3, pos.y - height / 3, pos.z), Color(0, 0, 0, 255), 1, 0);// 9
	points->push_back(point);
	point = Point(Vector3(pos.x - width, pos.y - height / 3, pos.z), Color(0, 0, 0, 255), 1, 0);// 10
	points->push_back(point);
	point = Point(Vector3(pos.x - width, pos.y + height / 3, pos.z), Color(0, 0, 0, 255), 1, 0);// 11
	points->push_back(point);
	point = Point(Vector3(pos.x - width/3, pos.y + height / 3, pos.z), Color(0, 0, 0, 255), 1, 0);// 12
	points->push_back(point);
}

// Phombus
Rhombus::Rhombus(Vector3 pos, float height, float width)
{
	// need to find the point for the cross shape
	/*
	*      (0,+)
	*         .   
	* 
	*   
	*(-,0).       .(+,0)
	* 
	*
	*         .    
	*       (0,-)
	*/
	this->height = height;
	this->width = width;

	//Vector3 pos, Color col, float sca, float rot
	Point point = Point(Vector3(pos.x, pos.y + height, pos.z), Color(0, 0, 0, 255), 1, 0); // 1
	points->push_back(point);
	point = Point(Vector3(pos.x + width / 2, pos.y, pos.z), Color(0, 0, 0, 255), 1, 0);// 2
	points->push_back(point);
	point = Point(Vector3(pos.x, pos.y - height, pos.z), Color(0, 0, 0, 255), 1, 0);// 3
	points->push_back(point);
	point = Point(Vector3(pos.x - width/2, pos.y, pos.z), Color(0, 0, 0, 255), 1, 0);// 4
	points->push_back(point);
}

//Trapezium
Trapezium::Trapezium(Vector3 pos, float height, float width)
{
	// need to find the point for the cross shape
	/*
	*      (-,+)  (+,+) 
	*         .    .
	*
	*
	* (-2,-).          .(+2,-)
	*/
	this->height = height;
	this->width = width;

	//Vector3 pos, Color col, float sca, float rot
	Point point = Point(Vector3(pos.x - width/2, pos.y - height/2, pos.z), Color(0, 0, 0, 255), 1, 0); // 1
	points->push_back(point);
	point = Point(Vector3(pos.x + width / 2, pos.y - height/2, pos.z), Color(0, 0, 0, 255), 1, 0);// 2
	points->push_back(point);
	point = Point(Vector3(pos.x + width, pos.y + height/2, pos.z), Color(0, 0, 0, 255), 1, 0);// 3
	points->push_back(point);
	point = Point(Vector3(pos.x - width , pos.y + height/2, pos.z), Color(0, 0, 0, 255), 1, 0);// 4
	points->push_back(point);
}

// Arrow
Arrow::Arrow(Vector3 pos, float height, float width)
{
	// need to find the point for the cross shape
	/*
	*           0\ 
	*           | \
  	*   0-------0  \ 
	*   |           0
	*   0-------0  /
	*           | /
	*           0/
	*/
	this->height = height;
	this->width = width;
	
	//Vector3 pos, Color col, float sca, float rot
	Point point = Point(Vector3(pos.x, pos.y - height/3, pos.z), Color(0, 0, 0, 255), 1, 0); // 1
	points->push_back(point);
	point = Point(Vector3(pos.x, pos.y - height, pos.z), Color(0, 0, 0, 255), 1, 0);// 2
	points->push_back(point);
	point = Point(Vector3(pos.x + width, pos.y, pos.z), Color(0, 0, 0, 255), 1, 0);// 3
	points->push_back(point);
	point = Point(Vector3(pos.x, pos.y + height, pos.z), Color(0, 0, 0, 255), 1, 0);// 4
	points->push_back(point);
	point = Point(Vector3(pos.x, pos.y + height/3, pos.z), Color(0, 0, 0, 255), 1, 0);// 5
	points->push_back(point);
	point = Point(Vector3(pos.x - width, pos.y + height / 3, pos.z), Color(0, 0, 0, 255), 1, 0);// 6
	points->push_back(point);
	point = Point(Vector3(pos.x - width, pos.y - height / 3, pos.z), Color(0, 0, 0, 255), 1, 0);// 7
	points->push_back(point);
}