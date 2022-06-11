#include "Skeleton.h"

/*
Les squelettes sont des éléments déblocables
*/

Skeleton::Skeleton(b2World* world, pugi::xml_node node, GameAssets* ga,
	std::unique_ptr<Inventory>& inventory) : UnlockableElement{ inventory }
{

	float x = node.attribute("posX").as_float();
	float y = node.attribute("posY").as_float();
	std::string stringSprite = node.attribute("sprite").as_string();


	for (auto child : node.children()) {
		required.push_back(child.attribute("equipKey").value());
	}

	textureSkeleton.loadFromFile("resources/images/" + stringSprite);
	textureSocle = ga->socle;
	spriteSkeleton.setScale((float)widthSkeleton / textureSkeleton.getSize().x, (float)heightSkeleton / textureSkeleton.getSize().y);
	spriteSocle.setPosition(x, y+200);
	spriteSocle.setScale((float)widthSkeleton / textureSkeleton.getSize().x, 1);
	spriteSkeleton.setPosition(x, y);
}

void Skeleton::draw(sf::RenderWindow* window)
{
	if (isUnlock) {
		spriteSkeleton.setTexture(textureSkeleton);
		window->draw(spriteSkeleton);
	}
	else {

		spriteSocle.setTexture(textureSocle);
		window->draw(spriteSocle);
	}

}

void Skeleton::unlock() {
isUnlock = true;
}


