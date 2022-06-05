#include "InteractableObject.h"
#include <iostream>

InterractableObject::InterractableObject(b2World* world,float x, float y, float width, float height, GameAssets* ga) :
	ga(ga)
{
	canInteract = false;

	//box2d
	bodyDef.type = b2_kinematicBody;
	b2Vec2 pos{ x,y };
	bodyDef.position.Set(pos.x, pos.y);
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>((InterractableObject*)this);


	body = world->CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox( width /2, height / 2); //Pourquoi ?
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.f;
	fixtureDef.friction = 1.f;



	//Sensor
	fixtureDef.isSensor = true;

	//Text
	fontInteract.loadFromFile("resources/font/ARIAL.ttf");
	textInteract.setFont(fontInteract);
	textInteract.setString("Press E");
	textInteract.setCharacterSize(24);
	textInteract.setPosition(x+width/2,y+height);

	body->CreateFixture(&fixtureDef);


}

void InterractableObject::setposition(b2Vec2 pos)
{
	body->SetTransform(pos, 0.0f);
	body->SetLinearVelocity({ 0.0f,0.0f });
}

b2Vec2 InterractableObject::getPosition() const
{
	return body->GetPosition();
}

void InterractableObject::interact()
{
	canInteract = true;
}

void InterractableObject::dontInteract()
{
	canInteract = false;
}

bool InterractableObject::checkInteract()
{
	return canInteract;
}

void InterractableObject::draw(sf::RenderWindow* window) {

}
