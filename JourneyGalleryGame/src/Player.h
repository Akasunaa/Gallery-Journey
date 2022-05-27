#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <stdio.h>

#define movHorizontal 10000000
#define movVertical 10000000
#define maxSpeed 1000

class Player
{
public:
	explicit Player();
	void updateInput();
	void playerDraw(sf::RenderWindow* window);

private:
	b2Body* body;
	sf::RectangleShape rect;

};