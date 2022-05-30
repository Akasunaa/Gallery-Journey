#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <stdio.h>
#include <InteractableObject.h>
enum class Contenu {vide, plein};
enum class Etat {intact, creuse};

class Case
{
public:
	explicit Case();

private:
	sf::RectangleShape rect;
	int x;
	int y;
};