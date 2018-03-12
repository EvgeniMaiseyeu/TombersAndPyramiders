#pragma once



#include "BasePilot.h"
class CharacterController;
class Vector2;

class AiPilot : public BasePilot
{

private:

	CharacterController* m_characterController;

public:
	void shouldFire();
	enum state
	{
		walk = 0,
		attack = 1
	}currentState;

	explicit AiPilot() = default;

public:

	void setController(BaseController* controller);

public:
	void onStart();
	void onUpdate(int ticks);
	void onEnd();

public:

	Vector2 getMovement();
};
