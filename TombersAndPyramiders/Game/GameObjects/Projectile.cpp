/*===================================================================================*//**
	Projectile
	
	A Damaging region that is fired by a projectile weapon, moves, and destroys itself 
	after a set duration or after hitting something.
    
    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include <memory>
#include "Projectile.h"
#include "BaseItem.h"
#include "CharacterController.h"

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
Projectile::Projectile(int damage, string imageName, float colliderWidth, float colliderHeight, bool destroyOnCollision, 
	float spawnXPosition, float spawnYPosition, float spriteScale, float xVelociy, float yVelocity, float lifespan) :
	DamagingRegion{ damage, imageName, colliderWidth, colliderHeight, destroyOnCollision, spawnXPosition, spawnYPosition, spriteScale },
	m_velocity{ Vector2(xVelociy, yVelocity) },
	m_lifespan{ lifespan }
{}

Projectile::~Projectile()
{}

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
void Projectile::onUpdate(int ticks)
{
	updatePosition(ticks);
	DamagingRegion::handleCollisions();
	updateLifespan(ticks);
}

/**
	Handles collisions for projectile damaging regions.
*/
void Projectile::handleSingleCollision(GameObject* other)
{
	auto otherId = other->getId();

	/* Ensure you don't collide with the thing that created you. */
	if (otherId != m_ownerId)
	{
		/* If the other thing is a character, damage it. */
		std::shared_ptr<CharacterController> ccOther = other->getComponent<CharacterController>();
		if (ccOther != nullptr)
		{
			m_hitList.insert(otherId);

			ccOther->takeDamage(m_damage);

			if (m_destroyOnCollision)
			{
				destroy(getId());
			}

			return;
		}

		/* TODO Handle collisions with walls? */
	}
}

void Projectile::updatePosition(int ticks)
{
	float deltaTime = ticks / BaseItem::TICKS_PER_SECOND;
	float xDelta = m_velocity.getX() * deltaTime;
	float yDelta = m_velocity.getY() * deltaTime;

	getTransform()->setPosition(
		getTransform()->getX() + xDelta,
		getTransform()->getY() + yDelta
	);
}

void Projectile::updateLifespan(int ticks)
{
	m_lifespan -= ticks / BaseItem::TICKS_PER_SECOND;

	if (m_lifespan <= 0)
	{
		destroy(getId());
	}
}
