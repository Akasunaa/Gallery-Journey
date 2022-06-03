#include "Player.h"
#include <iostream>

Player::Player(b2World* world, b2Vec2 pos, pugi::xml_node inventory_xml)
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

    //inventory
    inventory = std::make_unique<Inventory>();
    inventory->init_inventory(inventory_xml);

	//sprite
	this->rect.setSize(sf::Vector2f(playerWidth, playerHight));
	this->rect.setFillColor(sf::Color::Cyan);
}



void Player::updateInput()
{
	b2Vec2 vel = body->GetLinearVelocity();
	float force = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (vel.x > -maxSpeed) force = -movHorizontal;
		body->ApplyForceToCenter(b2Vec2(force, 0), true);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (vel.x < maxSpeed) force = movHorizontal;
		body->ApplyForceToCenter(b2Vec2(force, 0), true);
	}
	force =0;
	body->SetLinearVelocity(b2Vec2(0, 0));
	body->ApplyForceToCenter(b2Vec2(force, 0), true);

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

std::unique_ptr<Inventory> &Player::get_inventory() {
    return inventory;
}

void Player::playerDraw(sf::RenderWindow* window)
{
	rect.setPosition(sf::Vector2f(getPosition().x, getPosition().y));
	window->draw(rect);
}


