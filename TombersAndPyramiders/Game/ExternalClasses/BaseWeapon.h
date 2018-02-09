/*===================================================================================*//**
	BaseWeapon
	
	Abstract class for a base weapon.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

#pragma once

/*========================================================================================
	Dependencies
========================================================================================*/
#include "Updateable.h"
#include "BaseEquippableItem.h"
#include "DamagingRegion.h"

/*========================================================================================
	BaseWeapon	
========================================================================================*/
class BaseWeapon : public BaseEquippableItem, public Updateable
{
    /*----------------------------------------------------------------------------------------
		Instance Fields
    ----------------------------------------------------------------------------------------*/
	DamagingRegion _damagingRegion;

    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        /** Default constructor. */
        explicit BaseWeapon(float colliderWidth, float colliderHeight);

		virtual ~BaseWeapon() {};

	/*----------------------------------------------------------------------------------------
		Instance Methods
	----------------------------------------------------------------------------------------*/
    public:
		virtual void addToInventory(Inventory* inventory);
		virtual void onStart() = 0;
		virtual void onUpdate(int ticks) = 0;
		virtual void onEnd() = 0;
};
