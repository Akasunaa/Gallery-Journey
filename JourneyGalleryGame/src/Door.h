#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <stdio.h>
#include <InteractableObject.h>
#include <Player.h>
#include <UnlockableElement.h>

#define heightDoor 360
#define widthDoor 240

class Door : UnlockableElement
{
public:
	explicit Door(b2World* world, pugi::xml_node node, GameAssets* ga, 
		std::unique_ptr<Inventory>& inventory);

	void draw(sf::RenderWindow* window);
	void setEnable(bool state);
	void unlock() override;

private:
	sf::RectangleShape rect;
	b2Body* body;
	b2BodyDef bodyDef;

	bool isEnable;

	sf::Sprite spriteOpenDoor;
	sf::Texture textureOpenDoor;

	sf::Sprite spriteCloseDoor;
	sf::Texture textureCloseDoor;
};