#include "HostCharacter.h"
#include "CharacterController.h"
#include "Inventory.h"
#include "Receiver.h"

HostCharacter::HostCharacter(BasePilot* basePilot, int networkingID) :
	Character(basePilot)
{
	std::shared_ptr<Receiver> receiver = addComponent<Receiver>(this, std::to_string(networkingID));
	receiver->Subscribe("ATTACK", [](std::map<std::string, void*> data) -> void 
	{
		((HostCharacter*)data["this"])->getComponent<CharacterController>()->useWeapon();
	}, this);
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
void HostCharacter::onUpdate(int ticks)
{
	updateFrames(ticks);
}
