#include "UnlockableElement.h"

/*
Classe qui rend un objet déblocables selon ce qu'il demande dans le xml
*/

UnlockableElement::UnlockableElement(std::unique_ptr<Inventory>& inventory) : 
	inventory(inventory)
{
	isUnlock = false;
}

bool UnlockableElement::isUnlockable()
{
	for (auto& equipKey : required) {
		if (!(inventory->is_crafted(equipKey))) {
			return false;
		}
	}
	return true;
}

void UnlockableElement::unlock()
{
}
