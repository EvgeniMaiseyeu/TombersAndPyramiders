#include "GhostController.h"
#include "BasePossessableController.h"
#include "GhostCharacter.h"

const float GhostController::MAX_POSSESSION_DISTANCE = 2.0f;

GhostController::GhostController(GameObject* parentGameobject, BasePilot* pilot) : BaseController(parentGameobject, pilot)
{
	m_movementSpeed.setX(0.15f);
	m_movementSpeed.setY(0.15f);
	m_toFollow = nullptr;
}

void GhostController::onStart()
{
	std::cout << "GhostController::OnStart" << std::endl;
}

//Update the pilot, and if we're following someone, follow them
void GhostController::onUpdate(int ticks)
{
	if (m_pilot != nullptr)
	{
		m_pilot->onUpdate(ticks);
	}
	if (m_toFollow != nullptr)
	{
		gameObject->getTransform()->setPosition(m_toFollow->getGameObject()->getTransform()->getX(), m_toFollow->getGameObject()->getTransform()->getY());
	}
}

//Try to possess an object. If they are close enough to possess, possess them and follow the object
bool GhostController::tryPossess(std::shared_ptr<BasePossessableController> toPossess)
{
	if (toPossess != nullptr)
	{
		Vector2 theirPos = Vector2(toPossess->getGameObject()->getTransform()->getX(), toPossess->getGameObject()->getTransform()->getY());
		Vector2 ourPos = Vector2(gameObject->getTransform()->getX(), gameObject->getTransform()->getY());
		Vector2 diffPos = *(theirPos - ourPos);
		float distance = sqrtf(diffPos.getX() * diffPos.getX() + diffPos.getY() + diffPos.getY());
		if (distance <= MAX_POSSESSION_DISTANCE)
		{
			GhostCharacter* ghost = dynamic_cast<GhostCharacter*>(gameObject);
			if (ghost != nullptr)
			{
				follow(toPossess);
				ghost->setMode(GhostCharacter::Mode::possessing);
				return true;
			}
		}
	}
	return false;
}

//Stop possessing objects and stop following them
void GhostController::stopPossessing()
{
	follow(nullptr);
	GhostCharacter* ghost = dynamic_cast<GhostCharacter*>(gameObject);
	if (ghost != nullptr)
	{
		ghost->setMode(GhostCharacter::Mode::ghost);
	}
}

//Follow an object
void GhostController::follow(std::shared_ptr<BasePossessableController>  toFollow)
{
	m_toFollow = toFollow;
}

//Take in a delta vector, turn it into a direcitonal movespeed vector and determine which direction to move
void GhostController::move(Vector2 delta)
{
	delta.setX(delta.getX() * m_movementSpeed.getX());
	delta.setY(delta.getY() * m_movementSpeed.getY());

	if (delta.getMagnitude() == 0)
	{
	}
	else
	{
		gameObject->getTransform()->setRotation(delta.getRotationInDegrees());
	}

	gameObject->getTransform()->addTranslation(delta.getX(), delta.getY());
}
