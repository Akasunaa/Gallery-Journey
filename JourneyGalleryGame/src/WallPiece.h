#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <stdio.h>
#include <InteractableObject.h>

#define heightWall 100
#define widthWall 100

class WallPiece : public InterractableObject
{
public:
	explicit WallPiece(b2World* world, float x,float y);
	void setCanBeDug(bool state);
	bool getCanBeDug();
	void draw(sf::RenderWindow* window) override;

private:
	bool canBeDug;
};