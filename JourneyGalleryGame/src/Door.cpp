#include "Door.h"

Door::Door(b2World* world, float x, float y, GameAssets* ga, std::unique_ptr<Inventory>& inventory) :
	UnlockableElement(inventory)
{

	bodyDef.type = b2_staticBody;
	b2Vec2 pos{ x,y };
	bodyDef.position.Set(pos.x, pos.y);


	body = world->CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(widthDoor/2, heightDoor/2);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.f;
	fixtureDef.friction = 1.f;
	body->CreateFixture(&fixtureDef);

	body->SetEnabled(true);
	
	rect.setPosition(x, y);
	rect.setSize(sf::Vector2f(widthDoor, heightDoor));
	rect.setFillColor(sf::Color::Black);

	isEnable = true;
}

void Door::draw(sf::RenderWindow* window)
{
	if(isEnable){ window->draw(rect); }

}

void Door::setEnable(bool state)
{
	body->SetEnabled(state);
	isEnable = state;
}

void Door::unlock()
{
	setEnable(false);
}
