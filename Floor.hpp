#pragma once
#include "GameManager.hpp"
class Floor
{
protected:
	tle::IMesh*  floorMesh;
	tle::IModel* floorModel;
public:
	Floor(tle::I3DEngine* myEngine);
	~Floor();
};

