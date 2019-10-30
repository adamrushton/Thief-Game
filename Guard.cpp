#include "Guard.hpp"
#include "CVector3cut.hpp"
#include "CMatrix4x4cut.hpp"

std::unique_ptr<Square> waypoints;
std::unique_ptr<Visible> visible;
std::unique_ptr<Collision> collision;
std::unique_ptr<State> state;
tle::IFont* guardTextFont;
stringstream guardDebugInfo;

Guard::Guard(tle::I3DEngine* myEngine)
{
	collision        = std::make_unique<Collision>();
	visible          = std::make_unique<Visible>();
	waypoints	     = std::make_unique<Square>(myEngine, 6);
	guardMesh		 = myEngine->LoadMesh("casual_a.x");
	guardModel		 = guardMesh->CreateModel(-10.0f, 0.0f, 0.0f);
	state			 = std::make_unique<State>(myEngine, guardModel);
	movingState		 = Location1;
	guardState		 = Idle;
	detectingThieves = true;
	guardTextFont    = myEngine->LoadFont("Monotype Corsiva", 45);

	SetGuardWaypoints(myEngine);
	guardModel->Scale(GUARD_SIZE);
}

void Guard::SetGuardWaypoints(tle::I3DEngine* myEngine)
{
	waypoints->SetPosition(0, -10.0f,  0.0f);
	waypoints->SetPosition(1,  0.0f,   0.0f);
	waypoints->SetPosition(2,  5.0f,  -10.0f);
	waypoints->SetPosition(3,  0.0f,  -20.0f);
	waypoints->SetPosition(4, -10.0f, -20.0f);
	waypoints->SetPosition(5, -15.0f, -10.0f);
}

void Guard::LookAt(tle::IModel* secondModel)
{
	guardModel->GetMatrix(matrix);
	secondModel->GetMatrix(secondModelMatrix);
	CVector3 guardPosition, secondModelPosition;

	guardPosition.Set(&matrix[12]);
	secondModelPosition.Set(&secondModelMatrix[12]);

	CVector3 vectorZ = Normalise(Subtract(secondModelPosition, guardPosition));
	CVector3 vectorX = Normalise(Cross(kYAxis, vectorZ));
	CVector3 vectorY = Cross(vectorZ, vectorX);

	CMatrix4x4 guardMatrix;
	guardMatrix.MakeIdentity();
	guardMatrix.SetRow(0, vectorX);
	guardMatrix.SetRow(1, vectorY);
	guardMatrix.SetRow(2, vectorZ);
	guardMatrix.SetRow(3, guardPosition);

	// Set the guards position 
	guardModel->SetMatrix(&guardMatrix.e00);
}

void Guard::DetectingThieves(bool decision)
{
	detectingThieves = decision;
}

int Guard::Moving(tle::I3DEngine* myEngine, tle::IModel* thiefModel)
{
	guardModel->MoveLocalZ(speed);

	distanceFromThief = collision->Distance(guardModel, thiefModel);

	// Debug info on screen
	guardDebugInfo << "Detecting for a thief? " << detectingThieves;
	//guardDebugInfo << "Guard X: " << guardModel->GetLocalX() << " Y: " << guardModel->GetLocalY() << " Z: " << guardModel->GetLocalZ() << " STATE: " << movingState;
	//guardDebugInfo << "Distance from Thief: " << distanceFromThief;
	guardTextFont->Draw(guardDebugInfo.str(), 100, 0);
	guardDebugInfo.str("");
	// End 

	switch (guardState)
	{
	case Idle:
		// Alert guard if thief goes over a red square and is within 4 distance of the guard
		if (detectingThieves && visible->IsVisible(guardModel, thiefModel))
		{
			if (waypoints->CheckCollision(thiefModel) && distanceFromThief < RED_SQUARE_DISTANCE)
			{
				state->stateModel->SetSkin("Red.png");
				guardState = Alert;
			}

			// Set thief to alert mode when within 8 units
			if (distanceFromThief > MINIMUM_DISTANCE && distanceFromThief <= MAXIMUM_DISTANCE)
			{
				state->stateModel->SetSkin("Red.png");
				guardState = Alert;
				return 0;
			}
		}
		if (distanceFromThief <= 1.0f)
		{	// Transition to Dead state
			state->stateModel->SetSkin("Purple.png");
			guardState = Dead;
			return 0; // Do not continue running anything in this function on the current loop
		}
		
		switch (movingState)
		{
		case Location1:
			(guardModel->GetX() <= LOCATION_1_MAX) ? LookAt(waypoints->waypoints[Location2]) : movingState = Location2;
			break;
		case Location2:
			(guardModel->GetZ() >= LOCATION_2_MAX) ? LookAt(waypoints->waypoints[Location3]) : movingState = Location3;
			break;
		case Location3:
			(guardModel->GetZ() >= LOCATION_3_MAX) ? LookAt(waypoints->waypoints[Location4]) : movingState = Location4;
			break;
		case Location4:
			(guardModel->GetX() >= LOCATION_4_MAX) ? LookAt(waypoints->waypoints[Location5]) : movingState = Location5;
			break;
		case Location5:
			(guardModel->GetX() >= LOCATION_5_MAX) ? LookAt(waypoints->waypoints[Location6]) : movingState = Location6;
			break;
		case Location6:
			(guardModel->GetX() <= LOCATION_6_MAX) ? LookAt(waypoints->waypoints[Location1]) : movingState = Location1;
			break;
		}
	break;

	case Alert:
		LookAt(thiefModel);
		if (distanceFromThief <= MINIMUM_DISTANCE)
		{	// Kills thief
			speed = 0.0f;
			return 1;
		}
		if (distanceFromThief >= RETURN_DISTANCE || !detectingThieves)
		{
			state->stateModel->SetSkin("Blue.png");
			guardState = Idle;
			return 0;
		}
		break;

	case Dead:
		speed = 0.0f;
		guardDebugInfo << "Guard Dead";
		guardTextFont->Draw(guardDebugInfo.str(), 100, 0);
		guardDebugInfo.str("");
		break;
	}
	return 0;
}

Guard::~Guard()
{
	//delete(guardMesh);
}
