#include "WallPiece.h"
#include <iostream>

WallPiece::WallPiece(b2World* world, b2Vec2 pos)
{
	//box2d
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(pos.x, pos.y);
	body = world->CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(heightWall/2,widthWall/2);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.f;
	fixtureDef.friction = 1.f;

	//Sensor
	fixtureDef.isSensor = true;


	body->CreateFixture(&fixtureDef);


	//sprite
	this->rect.setSize(sf::Vector2f(heightWall, widthWall));
	this->rect.setFillColor(sf::Color::Blue);
}

b2Vec2 WallPiece::getPosition() const
{
	return body->GetPosition();
}

void WallPiece::setposition(b2Vec2 pos)
{
	body->SetTransform(pos, 0.0f);
	body->SetLinearVelocity({ 0.0f,0.0f });
}


void WallPiece::drawWallPiece(sf::RenderWindow* window)
{
	rect.setPosition(sf::Vector2f(getPosition().x, getPosition().y));
	window->draw(rect);
}
