#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include "pugixml.hpp"
#include "Inventory.h"
#include <stdio.h>
#include <memory>

#define movHorizontal 10000
#define movVertical 10000
#define maxSpeed 1000

#define playerWidth 100
#define playerHight 100

class Player
{
public:
	explicit Player(b2World* world, b2Vec2 pos, pugi::xml_node inventory_xml);
	void updateInput();
	void playerDraw(sf::RenderWindow* window);
	b2Vec2 getPosition() const;
	void setposition(b2Vec2 pos);
    std::unique_ptr<Inventory> & get_inventory();

private:
	b2Body* body;
	b2BodyDef bodyDef;
	sf::RectangleShape rect;
    std::unique_ptr<Inventory> inventory;
};