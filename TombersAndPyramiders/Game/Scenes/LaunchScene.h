#pragma once

#include "Scene.h"
#include "GameObject.h"
#include "Shader.h"

class LaunchScene : public Scene
{
private:

public:
	LaunchScene();
	void onStart();
	void onResume() {};
	void onUpdate(int ticks);
	void onPause();
	void onEnd();

};