

#pragma once
#include "ComplexSprite.h"
#include "BasePilot.h"
#include "Character.h"

#define ANIMATION_IDLE 0
#define ANIMATION_RUN 1
#define ANIMATION_ATTACK_MELEE 2
#define ANIMATION_ATTACK_RANGE 2

class NetworkCharacter : public Character
{
	/*----------------------------------------------------------------------------------------
	Instance Fields
	----------------------------------------------------------------------------------------*/
private:


	/*----------------------------------------------------------------------------------------
	Resource Management
	----------------------------------------------------------------------------------------*/
public:
	/** Default constructor. */
	explicit NetworkCharacter(BasePilot* basePilot);

	/*----------------------------------------------------------------------------------------
	Instance Getter Methods
	----------------------------------------------------------------------------------------*/
public:


	/*----------------------------------------------------------------------------------------
	Instance Setter Methods
	----------------------------------------------------------------------------------------*/
public:


	/*----------------------------------------------------------------------------------------
	Instance Methods
	----------------------------------------------------------------------------------------*/
public:
	void onUpdate(int ticks);
	void playRunAnimation();
	void endRunAnimation();
	void playMeleeAttackAnimation();
	void playRangeAttackAnimation();

private:
	/*--------------------
	Player Animation Logic
	--------------------*/
	std::shared_ptr<ComplexSpriteinfo> generateComplexSpriteInfo();
};
