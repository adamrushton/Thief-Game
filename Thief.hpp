#pragma once
#include "GameManager.hpp"
class Thief
{
protected:
	tle::IMesh*  thiefMesh;
	enum ThiefState { Alive, Dead };
	enum MovementState { Run, Walk, Creep };
	MovementState movementState;
	ThiefState thiefState;
	tle::IFont* thiefTextFont;
	const float RUN_SPEED = 0.08f;
	const float WALK_SPEED = 0.06f;
	const float CREEP_SPEED = 0.04f;
	float speed;
	const float ROTATION_SPEED = 0.25f;
	const tle::EKeyCode forwards = tle::Key_W;
	const tle::EKeyCode backwards = tle::Key_S;
	const tle::EKeyCode left = tle::Key_A;
	const tle::EKeyCode right = tle::Key_D;
	const tle::EKeyCode key1 = tle::Key_1;
	const tle::EKeyCode key2 = tle::Key_2;
	const tle::EKeyCode key3 = tle::Key_3;
public:
	const int THIEF_CREEPING_STATE = 2;
	const int THIEF_DEAD_STATE = 1;
	tle::IModel* thiefModel;
	void SetThiefState(int value);
	int Moving(tle::I3DEngine* myEngine);
	Thief(tle::I3DEngine* myEngine);
	~Thief();
};

