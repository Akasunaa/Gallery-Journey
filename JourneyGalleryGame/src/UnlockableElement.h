#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <stdio.h>
#include <Inventory.h>

class UnlockableElement
{
public:
	UnlockableElement(std::unique_ptr<Inventory>& inventory);
	bool isUnlockable();
	virtual void unlock();
private:
	std::vector<std::string> required;
	std::unique_ptr<Inventory>& inventory;
};