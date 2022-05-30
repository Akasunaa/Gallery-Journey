#pragma once
#include "Case.h"
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <stdio.h>
#include <InteractableObject.h>


#define hightExc 400
#define widthExc 400

#define nb_case 4

class Excavation
{
public:
	explicit Excavation(sf::RenderWindow* window);
	void draw(sf::RenderWindow* window);
	void clickMouse(sf::RenderWindow* window);

private:
	sf::RectangleShape rect;
	std::vector<Case> cases;
};