#include "WallPiece.h"
#include <iostream>

WallPiece::WallPiece(b2World* world, float x, float y) : InterractableObject{world, x,y,heightWall, widthWall}
{
	canBeDug = true;
}

void WallPiece::setCanBeDug(bool state)
{
	canBeDug = state;
}

bool WallPiece::getCanBeDug()
{
	return canBeDug;
}

void WallPiece::draw(sf::RenderWindow* window)
{	
	if (!canBeDug) {
		this->rect.setFillColor(sf::Color::Red);
	}
	else {
		this->rect.setFillColor(sf::Color::Blue);
	}
	rect.setPosition(sf::Vector2f(getPosition().x, getPosition().y));
	window->draw(rect);
}




