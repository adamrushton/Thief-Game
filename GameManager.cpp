#include "GameManager.hpp"

GameManager::GameManager()
{
	myEngine = tle::New3DEngine(tle::kTLX);
	myEngine->StartWindowed();
	myEngine->SetWindowCaption("Thief Game");
	myEngine->AddMediaFolder("./Media");
	myCamera = myEngine->CreateCamera(tle::kManual, 0.0f, 3.0f, -10.0f);
}
std::unique_ptr<Floor> ground;
std::unique_ptr<Thief> thief;
std::unique_ptr<Guard> guard;

const void GameManager::CreateObjects()
{
	ground = std::make_unique<Floor>(myEngine);
	thief  = std::make_unique<Thief>(myEngine);
	guard  = std::make_unique<Guard>(myEngine);
	myCamera->AttachToParent(thief->thiefModel);
}

const void GameManager::Start()
{
	CreateObjects();

	while (myEngine->IsRunning())
	{
		myEngine->DrawScene();
		if (guard->Moving(myEngine, thief->thiefModel) == thief->THIEF_DEAD_STATE) 
			thief->SetThiefState(thief->THIEF_DEAD_STATE);

		// If thief is creeping, guard is going to try and detect a thief
		(thief->Moving(myEngine) == thief->THIEF_CREEPING_STATE) ? guard->DetectingThieves(false) : guard->DetectingThieves(true);

		if (myEngine->KeyHit(quitKey))
			myEngine->Stop();
	}
	myEngine->Delete();
}

GameManager::~GameManager()
{	
	//myEngine->Delete(); // Could not create I3DEngine as a smart pointer because it is an abstract class. Must delete it once finished with to free the memory
}
