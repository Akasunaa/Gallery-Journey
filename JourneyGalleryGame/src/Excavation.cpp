#include "Excavation.h"
#include <iostream>

Excavation::Excavation(sf::RenderWindow* window) {
	this->rect.setSize(sf::Vector2f(widthExc, hightExc));
	this->rect.setFillColor(sf::Color::White);
	for (int i = 0; i < 4; i++) {

	}

}

void Excavation::draw(sf::RenderWindow* window)
{
	sf::Vector2i position = sf::Mouse::getPosition(*window);
	std::cout << position.x;
	std::cout << '\n';
	rect.setPosition(sf::Vector2f(0,0));
	window->draw(rect);
}
