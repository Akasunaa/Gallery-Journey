#include "Player.h"
#include <iostream>

Player::Player(b2World* world, b2Vec2 pos, pugi::xml_node inventory_xml, GameAssets* ga)
{
	//box2d
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);
	body = world->CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(playerWidth / 2, playerHeight / 2);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 1.f;
	body->CreateFixture(&fixtureDef);

    //inventory
    inventory = std::make_unique<Inventory>();
    inventory->init_inventory(inventory_xml);

	//sprite
	texture = ga->player;
	sprite.setOrigin({300, 0}); //Pourquoi cette valeur, pourquoi la vie?
	sprite.setScale((float)playerWidth / texture.getSize().x, (float)playerHeight / texture.getSize().y);
	sprite.setPosition(sf::Vector2f(0,0));
	
}



void Player::updateInput()
{
	b2Vec2 vel = body->GetLinearVelocity();
	float force = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (vel.x > -maxSpeed) force = -movHorizontal;
		body->ApplyForceToCenter(b2Vec2(force, 0), true);
		sprite.setScale((float)playerWidth / texture.getSize().x, (float)playerHeight / texture.getSize().y);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (vel.x < maxSpeed) force = movHorizontal;
		body->ApplyForceToCenter(b2Vec2(force, 0), true);
		sprite.setScale(-(float)playerWidth / texture.getSize().x, (float)playerHeight / texture.getSize().y);
	}
	force =0;
	body->SetLinearVelocity(b2Vec2(0, 0));
	body->ApplyForceToCenter(b2Vec2(force, 0), true);

}

b2Vec2 Player::getPosition() const
{
	return body->GetPosition();
}

void Player::setPosition(b2Vec2 pos)
{
	body->SetTransform(pos, 0.0f);
	body->SetLinearVelocity(b2Vec2(0, 0));
	body->ApplyForceToCenter(b2Vec2(0, 0), true);
}

void Player::stop()
{
	body->SetLinearVelocity(b2Vec2(0, 0));
}

std::unique_ptr<Inventory> &Player::get_inventory() {
    return inventory;
}

void Player::setEnable(bool state)
{
	body->SetEnabled(state);
	
}

void Player::playerDraw(sf::RenderWindow* window)
{
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(getPosition().x, getPosition().y));
	window->draw(sprite);
}


