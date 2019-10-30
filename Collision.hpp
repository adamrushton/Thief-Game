#pragma once
#include "GameManager.hpp"
class Collision
{
private:
public:
	Collision();
	~Collision();
	float Collision::Distance(tle::IModel* firstModel, tle::IModel* secondModel);
};

