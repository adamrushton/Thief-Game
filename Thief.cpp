#include "Thief.hpp"

Thief::Thief(tle::I3DEngine* myEngine)
{
	thiefMesh     = myEngine->LoadMesh("sierra.x");
	thiefModel    = thiefMesh->CreateModel(0.0f, 0.0f, -50.0f);
	thiefState    = Alive;
	movementState = Run;
	speed         = RUN_SPEED;
	thiefTextFont = myEngine->LoadFont("Monotype Corsiva", 45);
}
stringstream thiefDebugInfo;

void Thief::SetThiefState(int value)
{
	(value == 0) ? thiefState = Alive : thiefState = Dead;
}

int Thief::Moving(tle::I3DEngine* myEngine)
{
	switch (thiefState)
	{
	case Alive:
		thiefDebugInfo << "Thief Alive";
		if (myEngine->KeyHeld(forwards))
		{
			thiefModel->MoveLocalZ(speed);
		}
		if (myEngine->KeyHeld(left))
		{
			thiefModel->MoveLocalX(-speed);
			thiefModel->RotateLocalY(-ROTATION_SPEED);
		}
		if (myEngine->KeyHeld(backwards))
		{
			thiefModel->MoveLocalZ(-speed);
		}
		if (myEngine->KeyHeld(right))
		{
			thiefModel->RotateLocalY(ROTATION_SPEED);
			thiefModel->MoveLocalX(speed);
		}

		if (myEngine->KeyHeld(key1))
		{
			speed = RUN_SPEED; 
			movementState = Run;
		}
		if (myEngine->KeyHeld(key2))
		{
			speed = WALK_SPEED; 
			movementState = Walk;
		}
		if (myEngine->KeyHeld(key3))
		{
			speed = CREEP_SPEED; 
			movementState = Creep;
		}
		break;

	case Dead:
		thiefDebugInfo << "Thief Dead";
		break;
	}
	thiefTextFont->Draw(thiefDebugInfo.str(), 800, 0);
	thiefDebugInfo.str("");

	return movementState;
}

Thief::~Thief()
{
	//delete(thiefMesh);
}
