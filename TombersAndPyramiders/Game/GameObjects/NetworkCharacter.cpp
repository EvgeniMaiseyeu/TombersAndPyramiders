#include "NetworkCharacter.h"
#include "CharacterController.h"
#include "Inventory.h"
#include "Receiver.h"

NetworkCharacter::NetworkCharacter(BasePilot* basePilot) :
	Character(basePilot)
{
	setFPS(12);
	addComponent<Inventory>(this);
	addComponent<CharacterController>(this, getComponent<Inventory>().get(), basePilot);
	addComponent<Receiver>(this, std::to_string(this->getId()));
}

/*----------------------------------------------------------------------------------------
Instance Getter Methods
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
Instance Setter Methods
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
Instance Methods
----------------------------------------------------------------------------------------*/
void NetworkCharacter::onUpdate(int ticks)
{
	updateFrames(ticks);
}

// Private generation logic for describing the sprite sheet relationships for this player
std::shared_ptr<ComplexSpriteinfo> NetworkCharacter::generateComplexSpriteInfo()
{
	std::shared_ptr<ComplexSpriteinfo> spriteInfo = std::make_shared<ComplexSpriteinfo>();

	spriteInfo->addInfo("squareIdle.png", 8, 1);
	spriteInfo->addInfo("squareRun.png", 8, 1);
	spriteInfo->addInfo("squareRedAttack.png", 8, 1);
	spriteInfo->addInfo("squareWhiteAttack.png", 8, 1);

	return spriteInfo;
}

// Changes the sprite animation to running
void NetworkCharacter::playRunAnimation()
{
	changeSprite(ANIMATION_RUN);
}


// Changes the sprite animation to idling
void NetworkCharacter::endRunAnimation()
{
	changeSprite(ANIMATION_IDLE);
}


// Changes the sprite animation to the melee attack for one animation then returns back to idle
void NetworkCharacter::playMeleeAttackAnimation()
{
	changeSprite(ANIMATION_ATTACK_MELEE, ANIMATION_IDLE);
}


// Changes the sprite animation to the range attack for one animation then returns back to idle
void NetworkCharacter::playRangeAttackAnimation()
{
	changeSprite(ANIMATION_ATTACK_RANGE, ANIMATION_IDLE);
}
