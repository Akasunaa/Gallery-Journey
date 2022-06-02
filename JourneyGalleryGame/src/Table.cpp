#include "Table.h"
#include <iostream>

Table::Table(b2World* world, float x, float y) : InterractableObject{ world, x,y,heightTable, widthTable }
{

}

void Table::draw(sf::RenderWindow* window)
{
	this->rect.setFillColor(sf::Color::Red);
	rect.setPosition(sf::Vector2f(getPosition().x, getPosition().y));
	window->draw(rect);
}
