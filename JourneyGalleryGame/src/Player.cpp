#include "Player.h"
#include <iostream>

Player::Player()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0,0);

	this->rect.setSize(sf::Vector2f(100, 100));
	this->rect.setFillColor(sf::Color::Cyan);
}

void Player::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		std::cout << "hello";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		std::cout << "hello";
	}

}

void Player::playerDraw(sf::RenderWindow* window)
{
	rect.setPosition(200,200);
	window->draw(rect);
}
