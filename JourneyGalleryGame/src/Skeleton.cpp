#include "Skeleton.h"

Skeleton::Skeleton(b2World* world, pugi::xml_node node, GameAssets* ga,
	std::unique_ptr<Inventory>& inventory) : UnlockableElement{ inventory }
{
	isEnable = false;
	float x = node.attribute("posX").as_float();
	float y = node.attribute("posY").as_float();

	textureTrex = ga->TRex;
	textureSocle = ga->socle;
	spriteTRex.setScale((float)widthSkeleton / textureTrex.getSize().x, (float)heightSkeleton / textureTrex.getSize().y);
	spriteSocle.setPosition(x, y);
	spriteSocle.setScale((float)widthSkeleton / textureTrex.getSize().x, 1);
	spriteTRex.setPosition(x, y);
}

void Skeleton::draw(sf::RenderWindow* window)
{
	if (isEnable) {
		spriteTRex.setTexture(textureTrex);
		window->draw(spriteTRex);
	}
	else {

		spriteSocle.setTexture(textureSocle);
		window->draw(spriteSocle);
	}

}


