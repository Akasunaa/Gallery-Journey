#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <stdio.h>

#define movHorizontal 10000
#define movVertical 10000
#define maxSpeed 100000

#define playerWidth 100
#define playerHight 100

class Player
{
public:
	explicit Player(b2World* world, b2Vec2 pos);
	void updateInput();
	void playerDraw(sf::RenderWindow* window, std::pair<float, float> limit);
	b2Vec2 getPosition() const;
	void setposition(b2Vec2 pos);

private:
	b2Body* body;
	b2BodyDef bodyDef;
	sf::RectangleShape rect;

};