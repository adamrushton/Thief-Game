#include "Collision.hpp"

Collision::Collision()
{
}

// Distance between two points is subtracting each coordinate from each other to find the difference between x and z
// Then sqrting to find the distance as a unit
float Collision::Distance(tle::IModel* firstModel, tle::IModel* secondModel)
{
	float firstModelX  = firstModel->GetX();
	float firstModelZ  = firstModel->GetZ();
	float secondModelX = secondModel->GetX();
	float secondModelZ = secondModel->GetZ();

	float xDifference = (firstModelX - secondModelX);
	float zDifference = (firstModelZ - secondModelZ);

	return sqrt((xDifference * xDifference) + zDifference * zDifference);
}

Collision::~Collision()
{
}
