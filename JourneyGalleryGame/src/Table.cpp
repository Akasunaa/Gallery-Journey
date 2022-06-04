#include "Table.h"
#include <iostream>

Table::Table(b2World* world, float x, float y, GameAssets* ga) : 
	InterractableObject{ world, x,y,heightTable, widthTable, ga }
{

}

void Table::draw(sf::RenderWindow* window)
{

	//rect.setPosition(sf::Vector2f(getPosition().x, getPosition().y));
	//window->draw(rect);
}
