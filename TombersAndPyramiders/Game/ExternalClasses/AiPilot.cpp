#pragma

#include "AiPilot.h"
#include "CharacterController.h"
#include "Vector2.h"
#include "Inventory.h"

int attackCount = 0;
int attackNumber = rand();
void AiPilot::shouldFire()
{
	attackNumber = attackNumber % 6;
	attackCount = attackCount + 1;
	if (attackCount == 120)
	{
		attackNumber = rand();
		attackCount = 0;
	}
	if (attackNumber == 1)
	{
		currentState = attack;
		//attackNumber = rand();
	}

}

void AiPilot::setController(BaseController* controller)
{
	BasePilot::setController(controller);


	m_characterController = static_cast<CharacterController*>(controller);
}


void AiPilot::onStart()
{
	currentState = walk;
}

void AiPilot::onUpdate(int ticks)
{


	switch (currentState)
	{
	case walk:
		m_characterController->move(getMovement());
		shouldFire();
		break;
	case attack:
		m_characterController->useWeapon();
		currentState = walk;
		break;
	}


}

void AiPilot::onEnd()
{}

int coun = 0;
int randomNumber = rand();
Vector2 AiPilot::getMovement()
{
	randomNumber = randomNumber % 9;
	coun = coun + 1;
	Vector2 movement = Vector2(0, 0);
	if (coun == 60)
	{
		randomNumber = rand();
		coun = 0;
	}
	if (randomNumber == 1)
	{
		movement.setX(-0.2f);
	}
	else if (randomNumber == 2)
	{
		movement.setX(0.2f);

	}
	else if (randomNumber == 3)
	{
		movement.setY(0.2f);
	}
	else if (randomNumber == 4)
	{
		movement.setY(-0.2f);
	}
	else if (randomNumber == 5)
	{
		movement.setX(-0.2f);
		movement.setY(0.2f);
	}
	else if (randomNumber == 6)
	{
		movement.setX(0.2f);
		movement.setY(0.2f);
	}
	else if (randomNumber == 7)
	{
		movement.setX(-0.2f);
		movement.setY(-0.2f);
	}
	else if (randomNumber == 8)
	{
		movement.setX(0.2f);
		movement.setY(-0.2f);
	}

	return movement;
}