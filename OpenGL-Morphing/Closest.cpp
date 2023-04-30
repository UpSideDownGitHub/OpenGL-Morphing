#include "Closest.h"

// Constructor for the Closest class
Closest::Closest(){}


/*
	this class will return the cloest target point from the given list
*/
std::vector<Point> Closest::findClosest(std::vector<Point> playerPoints, std::vector<Point> targetPoints)
{
	// pre create the resorted & used points so that they can be returned
	std::vector<Point> resorted;
	std::vector<int> used;
	
	// loop through the player points and for each point find the closest value then add it to the list
	// this function will output a new list of the target potions that should be used
	for (size_t i = 0; i < playerPoints.size(); i++)
	{
		float closest = FLT_MAX;
		int positionToAdd = 0;
		// for all of the target points 
		for (size_t j = 0; j < targetPoints.size(); j++)
		{
			// if the target point is allready being used then move to the next 
			// point
			if (std::find(used.begin(), used.end(), j) != used.end())
				continue;
			
			// find the distance between the two points and if the distance is closer than the
			// closest then add it to the closest
			float dist = distance(playerPoints[i].position, targetPoints[j].position);
			if (dist < closest)
			{
				closest = dist;
				positionToAdd = j;
			}
		}
		// add the current closest point to the list of points
		resorted.push_back(targetPoints[positionToAdd]);
		used.push_back(positionToAdd);
	}
	// return the found list
	listOrder = used;
	return resorted;
}

/*
	this will calculate the distance between two given points
*/
float Closest::distance(Vector3 point1, Vector3 point2)
{
	int X1 = point1.x;
	int Y1 = point1.y;
	int Z1 = point1.z;
	int X2 = point2.x;
	int Y2 = point2.y;
	int Z2 = point2.z;
	int p1 = pow(X2 - X1, 2);
	int p2 = pow(Y2 - Y1, 2);
	int p3 = pow(Z2 - Z1, 2);
	// return the distance between the points
	return sqrtf(p1 + p2 + p3);
	
}
