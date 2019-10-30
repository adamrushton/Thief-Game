#pragma once
#include "GameManager.hpp"

class Guard
{
protected:
	enum MovingState { Location1, Location2, Location3, Location4, Location5, Location6 };
	enum GuardState { Idle, Alert, Dead };
	MovingState movingState;
	GuardState guardState;

	const float GUARD_SIZE			= 5.0f;
	const float MINIMUM_DISTANCE	= 1.0f;
	const float MAXIMUM_DISTANCE	= 8.0f;
	const float RETURN_DISTANCE		= 12.0f;
	const float LOCATION_1_MAX		= -0.5f;
	const float LOCATION_2_MAX		= -9.9f;
	const float LOCATION_3_MAX		= -19.0f;
	const float LOCATION_4_MAX		= -9.5f;
	const float LOCATION_5_MAX		= -14.5f;
	const float LOCATION_6_MAX		= -10.5f;
	const float ROTATION			= 90.0f;
	const float RED_SQUARE_DISTANCE = 4.0f;

	const int NUM_OF_GUARD_WAYPOINTS = 6;
	float speed = 0.001f;
	float distanceFromThief;
	float matrix[16], secondModelMatrix[16];
	bool detectingThieves;

	tle::IMesh*  guardMesh;
	void SetGuardWaypoints(tle::I3DEngine* myEngine);
	void LookAt(tle::IModel* secondModel);
public:
	tle::IModel* guardModel;
	Guard(tle::I3DEngine* myEngine);
	int Moving(tle::I3DEngine* myEngine, tle::IModel* thiefModel);
	void DetectingThieves(bool decision);
	~Guard();
};