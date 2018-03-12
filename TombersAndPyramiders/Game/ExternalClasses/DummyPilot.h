#pragma once

#include "BasePilot.h"

class DummyPilot : public BasePilot
{
public:
	void onStart() {}
	void onUpdate(int ticks) {}
	void onEnd() {}
};
