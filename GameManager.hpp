#pragma once
// Including header files
#include "TL-Engine.h"
#include "Floor.hpp"
#include "Thief.hpp"
#include "Guard.hpp"
#include "State.hpp"
#include "Square.hpp"
#include "Collision.hpp"
#include "Visible.hpp"

#include <memory>  // Required for unique ptr
#include <sstream> // Required for writing to screen
class GameManager
{
protected:
	tle::I3DEngine* myEngine;
	tle::ICamera* myCamera;
	const void CreateObjects();
	const tle::EKeyCode quitKey = tle::Key_Escape;
public:
	GameManager();
	~GameManager();
	const void Start();

};