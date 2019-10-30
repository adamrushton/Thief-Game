#pragma once
#include "GameManager.hpp"
#include "vector"

class Square
{
protected:
	tle::IMesh* squareMesh;
	float minX[6];
	float maxX[6];
	float minZ[6];
	float maxZ[6];
	int total;
public:
	tle::IModel* waypoints[];
	void SetPosition(int index, float x, float z);
	float GetLocalX(int index);
	float GetLocalZ(int index);
	bool CheckCollision(tle::IModel* model1);
	Square(tle::I3DEngine* myEngine, const int numOfWaypoints);
	~Square();
};

