#include "ClientCharacter.h"
#include "CharacterController.h"
#include "Inventory.h"
#include "Sender.h"

ClientCharacter::ClientCharacter(BasePilot* basePilot, int networkingID) :
	Character(basePilot)
{
	addComponent<Sender>(this, std::to_string(networkingID));
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
void ClientCharacter::onUpdate(int ticks)
{
	updateFrames(ticks);
}