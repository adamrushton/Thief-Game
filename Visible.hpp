#pragma once
#include "GameManager.hpp"

class Visible
{
private:
public:
	Visible();
	~Visible();
	void FacingVector(tle::IModel* model, float &x, float &y, float &z);
	bool Visible::IsVisible(tle::IModel* firstModel, tle::IModel* secondModel);
};

