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
	explicit WallPiece(b2World* world, b2Vec2 pos);
	void setposition(b2Vec2 pos);
	void drawWallPiece(sf::RenderWindow* window);	
	b2Vec2 getPosition() const;

private:
	b2Body* body;
	b2BodyDef bodyDef;
	sf::RectangleShape rect;

};