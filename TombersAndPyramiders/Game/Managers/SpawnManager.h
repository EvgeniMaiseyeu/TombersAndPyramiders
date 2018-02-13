#pragma once

#include <memory>
#include "MiscSquare.h"
#include "MovingSquare.h"
#include "Character.h"

class SpawnManager
{
private:
	static SpawnManager* s_instance;
	//GameObject* mGameObj;

	SpawnManager();
	~SpawnManager();

public:
	std::shared_ptr<MiscSquare> generateMiscSquare(float x, float y, float z, float scale, string spriteName);
	std::shared_ptr<MovingSquare> generateMovingSquare(float x, float y);
	std::shared_ptr<Character> generatePlayerCharacter(float x, float y);
	static SpawnManager* getInstance();
};