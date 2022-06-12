#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <stdio.h>
#include <InteractableObject.h>
#include <Player.h>
#include <UnlockableElement.h>
#include <InteractableObject.h>

#define heightSkeleton 360
#define widthSkeleton 240

class Skeleton : public UnlockableElement
{
public:
	explicit Skeleton(b2World* world, pugi::xml_node node, GameAssets* ga,std::unique_ptr<Inventory>& inventory);

	void draw(sf::RenderWindow* window);
	void unlock() override;

private:

	sf::Sprite spriteSocle;
	sf::Texture textureSocle;
	sf::Sprite spriteSkeleton;
	sf::Texture textureSkeleton;

};