#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
#include "Vector2.h"
#include "AiPilot.h"
#include "CharacterController.h"
#include "SimpleSprite.h"

class Monster : public SimpleSprite
	//public Component
{
private:
	
	Transform *myTransform;
	Vector2 *targetPosition;
	void GetTarget();
	Vector2* GetTargetPosition();

	

public: 

	void OnUpdate(int ticks);
	
	Monster();
	void OnStart() ;

	enum Target {
		
		position = 0,
	
	}currentTarget;
	
};

