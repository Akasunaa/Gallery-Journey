#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <stdio.h>
#include <InteractableObject.h>

#define heightTable 100
#define widthTable 100

class Table : public InterractableObject
{
public:
	explicit Table(b2World* world, float x, float y, GameAssets* ga);
	void draw(sf::RenderWindow* window) override;

private:

};