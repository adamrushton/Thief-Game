// PlsWorkThief.cpp: A program using the TL-Engine

#include "GameManager.hpp"

void Run()
{
	std::unique_ptr<GameManager> thiefGame = std::make_unique<GameManager>();
	thiefGame->Start();
}

// This design is required so that smart pointers are memory-deallocated successfully. 
// The program does not know when the function is over otherwise.
void main()
{
	Run();
	_CrtDumpMemoryLeaks(); // Find and dump any memory leaks detected
}

