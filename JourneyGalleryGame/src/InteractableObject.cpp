#include "InteractableObject.h"
#include <iostream>

InterractableObject::InterractableObject(b2World* world,float x, float y, float height, float width)
{
	canInteract = false;
	//box2d
	bodyDef.type = b2_kinematicBody;
	b2Vec2 pos{ x,y };
	bodyDef.position.Set(pos.x, pos.y);
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>((InterractableObject*)this);


	body = world->CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(height / 2, width / 2);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.f;
	fixtureDef.friction = 1.f;



	//Sensor
	fixtureDef.isSensor = true;


	body->CreateFixture(&fixtureDef);


	//sprite
	this->rect.setSize(sf::Vector2f(height, width));
	this->rect.setFillColor(sf::Color::Blue);
}

void InterractableObject::setposition(b2Vec2 pos)
{
	body->SetTransform(pos, 0.0f);
	body->SetLinearVelocity({ 0.0f,0.0f });
}

b2Vec2 InterractableObject::getPosition() const
{
	return b2Vec2();
}

void InterractableObject::interact()
{
	std::cout << "miaou";
}

void InterractableObject::dontInteract()
{
	std::cout << "not miaou";
}

void InterractableObject::checkInteract()
{
}

void InterractableObject::draw(sf::RenderWindow* window) {
	rect.setPosition(sf::Vector2f(getPosition().x, getPosition().y));
	window->draw(rect);
}
