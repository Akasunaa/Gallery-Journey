#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <stdio.h>

class InterractableObject {
public :
	explicit InterractableObject(b2World* world, float x, float y, float height, float width);
	void setposition(b2Vec2 pos);
	void draw(sf::RenderWindow* window);	
	b2Vec2 getPosition() const;
	virtual void interact();
	virtual void dontInteract();
	virtual void checkInteract();


private:
	b2Body* body;
	b2BodyDef bodyDef;
	sf::RectangleShape rect;

protected:
	bool canInteract;

};