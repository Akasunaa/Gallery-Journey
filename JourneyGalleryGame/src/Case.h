#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <stdio.h>
#include <InteractableObject.h>


class Case
{
public:
	explicit Case(int x,int y, float height, float width, float nb_case, int value);
	void draw(sf::RenderWindow* window);
	void setDig();
	bool getDig();
	void setTresure();
	bool getTresure();

private:
	sf::RectangleShape rect;
	int x;
	int y;
	int value;
	bool asTresure;
	bool isDig;
};