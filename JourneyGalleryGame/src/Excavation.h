#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <stdio.h>
#include <InteractableObject.h>
#include <Case.h>

#define widthExc 400
#define hightExc 400

class Excavation
{
public:
	explicit Excavation(sf::RenderWindow* window);
	void draw(sf::RenderWindow* window);

private:
	sf::RectangleShape rect;
	std::vector<Case> cases;
};