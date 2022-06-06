#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <stdio.h>
#include <InteractableObject.h>
#include <Player.h>

#define heightDoor 180
#define widthDoor 270

class Door : public InterractableObject
{
public:
	explicit Door(b2World* world, float x, float y, GameAssets* ga,Player* player);
	void draw(sf::RenderWindow* window) override;

private:
	sf::RectangleShape rect;
};