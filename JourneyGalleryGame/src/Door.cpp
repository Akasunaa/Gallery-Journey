#include "Door.h"



Door::Door(b2World* world, pugi::xml_node node, GameAssets* ga, 
	std::unique_ptr<Inventory>& inventory) :
	UnlockableElement(inventory)
{
	float x= node.attribute("posX").as_float();
	float y= node.attribute("posY").as_float();
	bodyDef.type = b2_staticBody;
	b2Vec2 pos{x , y};
	bodyDef.position.Set(pos.x, pos.y);


	body = world->CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(widthDoor / 2, heightDoor / 2);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.f;
	fixtureDef.friction = 1.f;
	body->CreateFixture(&fixtureDef);

	body->SetEnabled(true);

	rect.setPosition(node.attribute("posX").as_float(), node.attribute("posY").as_float());
	rect.setSize(sf::Vector2f(widthDoor, heightDoor));
	rect.setFillColor(sf::Color::Black);

	isEnable = true;

	for (auto child : node.children()) {
		required.push_back(child.attribute("equipKey").value());
	}

	textureCloseDoor = ga->closeDoor;
	spriteCloseDoor.setScale((float)widthDoor / textureCloseDoor.getSize().x, (float)heightDoor / textureCloseDoor.getSize().y);
	spriteCloseDoor.setPosition(sf::Vector2f(x,y));

	textureOpenDoor = ga->player;
	spriteOpenDoor.setScale((float)widthDoor / textureCloseDoor.getSize().x, (float)heightDoor / textureCloseDoor.getSize().y);
	spriteOpenDoor.setPosition(sf::Vector2f(x,y));
}

void Door::draw(sf::RenderWindow* window)
{
	if(isEnable){
		spriteCloseDoor.setTexture(textureCloseDoor);
		window->draw(spriteCloseDoor);
	}
	else{
		spriteOpenDoor.setTexture(textureOpenDoor);
		window->draw(spriteOpenDoor);
	}
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
