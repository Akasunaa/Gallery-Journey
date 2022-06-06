#include "Door.h"

Door::Door(b2World* world, float x, float y, GameAssets* ga):
	InterractableObject{ world, x,y, widthDoor,heightDoor, ga }
{
	bodyDef.type = b2_dynamicBody;
	rect.setPosition(x, y);
	rect.setSize(sf::Vector2f(widthDoor,heightDoor));
	rect.setFillColor(sf::Color::Black);
}

void Door::draw(sf::RenderWindow* window)
{
	if (canInteract) {

	}

	window->draw(rect);
}
