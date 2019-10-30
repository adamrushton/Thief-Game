#pragma once
#include "GameManager.hpp"

class State
{
protected:
	tle::IMesh*  stateMesh;
public:
	tle::IModel* stateModel;
	State(tle::I3DEngine* myEngine, tle::IModel* guard);
	~State();
};

