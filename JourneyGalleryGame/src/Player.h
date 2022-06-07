#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include "pugixml.hpp"
#include "Inventory.h"
#include <stdio.h>
#include <memory>
#include <GameAssets.h>

#define movHorizontal 1000000000
#define maxSpeed 10000

#define playerHeight 240
#define playerWidth 120

class Player
{
public:
	explicit Player(b2World* world, b2Vec2 pos, pugi::xml_node inventory_xml,GameAssets* ga);
	void updateInput();
	void playerDraw(sf::RenderWindow* window);
	b2Vec2 getPosition() const;
	void setPosition(b2Vec2 pos);
	void stop();
    std::unique_ptr<Inventory> & get_inventory();

private:
	b2Body* body;
	b2BodyDef bodyDef;

    std::unique_ptr<Inventory> inventory;

	GameAssets* ga;
	sf::Sprite sprite;
	sf::Texture texture;
};