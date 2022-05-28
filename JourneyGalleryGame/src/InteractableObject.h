#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <stdio.h>

class InterractableObject {
public :
	explicit InterractableObject(b2World* world, b2Vec2 pos, float heigth, float width);
	void setposition(b2Vec2 pos);
	void draw(sf::RenderWindow* window);	
	b2Vec2 getPosition() const;
	void interact();


private:
	b2Body* body;
	b2BodyDef bodyDef;
	sf::RectangleShape rect;

};