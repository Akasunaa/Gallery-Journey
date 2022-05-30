#include "Case.h"
#include <iostream>


Case::Case(int x, int y,float height, float width, float nb_case,int value)
{
	this->x = x;
	this->y = y;
	this->value = value;
	this->rect.setSize(sf::Vector2f(height/nb_case,width/nb_case));
	this->rect.setFillColor(sf::Color::Red);
	this->rect.setPosition(sf::Vector2f(x * height /nb_case, y * width/nb_case));
	this->rect.setOutlineColor(sf::Color::Black);
	this->rect.setOutlineThickness(-3);
	this->isDig = false;

}

void Case::draw(sf::RenderWindow* window)
{
	window->draw(rect);
}

void Case::dig()
{
	isDig = true;
	this->rect.setFillColor(sf::Color::Blue);

}



