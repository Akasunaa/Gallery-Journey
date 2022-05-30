#include "Excavation.h"
#include <iostream>

Excavation::Excavation(sf::RenderWindow* window) {
	this->rect.setSize(sf::Vector2f(widthExc, hightExc));
	this->rect.setFillColor(sf::Color::White);
	for (int i = 0; i < nb_case*nb_case; i++) {
		Case thisCase(i / nb_case,i%nb_case,hightExc,widthExc,nb_case);
		thisCase.setValue(i);
		cases.push_back(thisCase);

	}

}

void Excavation::clickMouse(sf::RenderWindow* window)
{
	sf::Vector2i position = sf::Mouse::getPosition(*window);
	int x = position.x / (hightExc/nb_case);
	int y = position.y / (widthExc / nb_case);
	std::cout << x << 'et' << y << '\n';
}

void Excavation::draw(sf::RenderWindow* window)
{
	//window->draw(rect);
	//sf::Vector2i position = sf::Mouse::getPosition(*window);
	clickMouse(window);
	//rect.setPosition(sf::Vector2f(0,0));
	for (int i = 0; i < nb_case*nb_case;i++) {
		cases[i].draw(window);
		
	}

}

