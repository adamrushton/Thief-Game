#include "State.hpp"

State::State(tle::I3DEngine* myEngine, tle::IModel* guard)
{
	stateMesh  = myEngine->LoadMesh("state.x");
	stateModel = stateMesh->CreateModel(0.0f, 3.0f, 0.0f);
	stateModel->SetSkin("blue.png"); // Start in blue state
	stateModel->AttachToParent(guard);
}

State::~State()
{
	//delete(stateMesh);
}
