#include "Floor.hpp"

Floor::Floor(tle::I3DEngine* myEngine)
{
	floorMesh  = myEngine->LoadMesh("Floor.x");
	floorModel = floorMesh->CreateModel(0.0f, -0.01f, 0.0f);
}

Floor::~Floor()
{
	//delete(floorMesh);
}
