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

#define heightDoor 360
#define widthDoor 240

class Door : public UnlockableElement, public InterractableObject
{
public:
	explicit Door(b2World* world, pugi::xml_node node, GameAssets* ga, 
		std::unique_ptr<Inventory>& inventory);

	void draw(sf::RenderWindow* window);
	void setEnable(bool state);
	void unlock() override;


private:

	bool isEnable;

	sf::Sprite spriteOpenDoor;
	sf::Texture textureOpenDoor;

};