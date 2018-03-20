#pragma once

#include "Scene.h"
#include "GameObject.h"
#include "Shader.h"
#include "CameraFollow.h"
#include "Character.h"

class NetworkedGameScene : public Scene
{
private:

public:
	std::vector<time_t> mapSeeds;
	std::map<Uint32, Character> players;
	NetworkedGameScene();
	void onStart();
	void onResume() {};
	void onUpdate(int ticks);
	void onPause();
	void onEnd();

};