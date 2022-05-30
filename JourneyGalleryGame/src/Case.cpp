#include "Case.h"
#include <iostream>


Case::Case(int x, int y,float height, float width, float nb_case)
{
	this->x = x;
	this->y = y;
	this->rect.setSize(sf::Vector2f(height/nb_case,width/nb_case));
	if (x % 2) {
		this->rect.setFillColor(sf::Color::Red);
	}
	else {
		this->rect.setFillColor(sf::Color::Blue);
	}

	this->rect.setPosition(sf::Vector2f(x * height /nb_case, y * width/nb_case));
	this->rect.setOutlineColor(sf::Color::Black);
	this->rect.setOutlineThickness(-3);

}

void Case::draw(sf::RenderWindow* window)
{
	window->draw(rect);
}

void Case::setValue(int val)
{
	value = val;
}


