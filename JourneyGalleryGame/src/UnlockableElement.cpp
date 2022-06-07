#include "UnlockableElement.h"

UnlockableElement::UnlockableElement(std::unique_ptr<Inventory>& inventory) : 
	inventory(inventory)
{
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
