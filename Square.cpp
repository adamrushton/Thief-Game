#include "Square.hpp"

Square::Square(tle::I3DEngine* myEngine, const int numOfWaypoints)
{
	total = numOfWaypoints;
	waypoints[numOfWaypoints];
	squareMesh = myEngine->LoadMesh("Square.x");
	for (int i = 0; i < numOfWaypoints; i++) 
	{
		waypoints[i] = squareMesh->CreateModel();
		waypoints[i]->SetSkin("Red.png");
	}
}
// Bounding box of geometry = (-0.5,0,-0.5) to (0.5,0,0.5).

void Square::SetPosition(int index, float x, float z)
{
	waypoints[index]->SetLocalPosition(x, 0.0f, z);
	minX[index] = x - 0.5f;
	maxX[index] = x + 0.5f;
	minZ[index] = z - 0.5f;
	maxZ[index] = z + 0.5f;
}

bool Square::CheckCollision(tle::IModel* model1)
{	// Go through all of the square bounding boxes and if a model is in any return true, otherwise return false
	for (int i = 0; i < total; i++)
	{
		if (model1->GetX() < maxX[i] && model1->GetX() > minX[i] &&
			model1->GetZ() < maxZ[i] && model1->GetZ() > minZ[i])
		{
			return true;
		}
	}
	return false;
}

float Square::GetLocalX(int index)
{
	return waypoints[index]->GetLocalX();
}


float Square::GetLocalZ(int index)
{
	return waypoints[index]->GetLocalZ();
}

Square::~Square()
{
}
