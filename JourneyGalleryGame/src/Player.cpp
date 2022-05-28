#include "Player.h"
#include <iostream>

Player::Player(b2World* world, b2Vec2 pos)
{
	//box2d
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);
	body = world->CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(playerWidth / 2, playerHight / 2);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.f;
	body->CreateFixture(&fixtureDef);

	//sprite
	this->rect.setSize(sf::Vector2f(playerWidth, playerHight));
	this->rect.setFillColor(sf::Color::Cyan);
}



void Player::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		b2Vec2 impulse(-movHorizontal, 0.0f);
		body->ApplyForceToCenter(impulse, true);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		b2Vec2 impulse(movHorizontal, 0.0f);
		body->ApplyForceToCenter(impulse, true);

	}
	b2Vec2 velocity = body->GetLinearVelocity();
	if (velocity.LengthSquared() > maxSpeed * maxSpeed)
	{
		velocity.Normalize();
		velocity = b2Vec2(velocity.x * maxSpeed, velocity.y * maxSpeed);
		body->SetLinearVelocity(velocity);
	}
}

b2Vec2 Player::getPosition() const
{
	return body->GetPosition();
}

void Player::setposition(b2Vec2 pos)
{
	body->SetTransform(pos, 0.0f);
	body->SetLinearVelocity({ 0.0f,0.0f });
}

void Player::playerDraw(sf::RenderWindow* window)
{
	rect.setPosition(sf::Vector2f(getPosition().x, getPosition().y));
	window->draw(rect);
}


