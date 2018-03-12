#include "HostPilot.h"
#include "CharacterController.h"
#include "InputManager.h"
#include "Vector2.h"

void HostPilot::setController(BaseController* controller)
{
	BasePilot::setController(controller);

	/* Store a correctly typed pointer to the controller for convenience. */
	m_characterController = static_cast<CharacterController*>(controller);
}

/*----------------------------------------------------------------------------------------
Instance Methods
----------------------------------------------------------------------------------------*/
void HostPilot::onStart()
{}

void HostPilot::onUpdate(int ticks)
{
	/*
	if (m_characterController != nullptr)
	{
		m_characterController->move(getMovement());
	}

	if (getWeaponInput())
	{
		m_characterController->useWeapon();
	}
	*/
}

void HostPilot::onEnd()
{}

Vector2 HostPilot::getMovement()
{
	Vector2 movement = Vector2(0, 0);

	/* Move up. */
	if (InputManager::getInstance()->onKey(SDLK_w))
	{
		movement.setY(movement.getY() + 1);
	}

	/* Move down. */
	if (InputManager::getInstance()->onKey(SDLK_s))
	{
		movement.setY(movement.getY() - 1);
	}

	/* Move left. */
	if (InputManager::getInstance()->onKey(SDLK_a))
	{
		movement.setX(movement.getX() - 1);
	}

	/* Move right. */
	if (InputManager::getInstance()->onKey(SDLK_d))
	{
		movement.setX(movement.getX() + 1);
	}

	return movement;
}

bool HostPilot::getWeaponInput()
{
	return InputManager::getInstance()->onKey(SDLK_i);
}
