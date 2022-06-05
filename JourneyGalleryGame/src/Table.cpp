#include "Table.h"
#include <iostream>

Table::Table(b2World* world, float x, float y, GameAssets* ga) : 
	InterractableObject{ world, x,y,heightTable, widthTable, ga }
{
	texture = ga->table;
	sprite.setPosition(sf::Vector2f(getPosition().x, getPosition().y));
	sprite.setScale((float)widthTable/ texture.getSize().x, (float)heightTable / texture.getSize().y);
}

void Table::draw(sf::RenderWindow* window)
{

	sprite.setTexture(texture);
	window->draw(sprite);
}
