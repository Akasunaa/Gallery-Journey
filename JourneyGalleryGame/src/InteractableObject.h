#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <stdio.h>
#include <GameAssets.h>
#include <pugixml.hpp>

class InterractableObject {
public :
	explicit InterractableObject(b2World* world, float x, float y, float width, float height,GameAssets* ga);
	explicit InterractableObject(b2World* world, pugi::xml_node node, float width, float height, GameAssets* ga);

	void setposition(b2Vec2 pos);
	virtual void draw(sf::RenderWindow* window);	
	b2Vec2 getPosition() const;
	virtual void interact();
	virtual void dontInteract();
	virtual bool checkInteract();
	b2Body* getBodyPointer();

protected:
	b2Body* body=nullptr;
	b2BodyDef bodyDef;
	bool canInteract;

	GameAssets* ga;
	sf::Texture texture;
	sf::Sprite sprite;


	sf::Font fontInteract;
	sf::Text textInteract;

};