#include "Door.h"



Door::Door(b2World* world, pugi::xml_node node, GameAssets* ga, 
	std::unique_ptr<Inventory>& inventory) :
	UnlockableElement(inventory), InterractableObject{ world, node,widthDoor, heightDoor, ga }
{
	float x= node.attribute("posX").as_float();
	float y= node.attribute("posY").as_float();
	bodyDef.type = b2_staticBody;
	b2Vec2 pos{x , y};
	bodyDef.position.Set(pos.x, pos.y);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(widthDoor / 2, heightDoor / 2);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	body->CreateFixture(&fixtureDef);

	body->SetEnabled(true);



	isEnable = true;

	for (auto child : node.children()) {
		required.push_back(child.attribute("equipKey").value());
	}

	texture = ga->closeDoor;
	sprite.setScale((float)widthDoor / texture.getSize().x, (float)heightDoor / texture.getSize().y);
	sprite.setPosition(sf::Vector2f(x,y));

	textureOpenDoor = ga->openDoor;
	spriteOpenDoor.setScale((float)widthDoor / textureOpenDoor.getSize().x, (float)heightDoor / textureOpenDoor.getSize().y);
	spriteOpenDoor.setPosition(sf::Vector2f(x,y));
}

void Door::draw(sf::RenderWindow* window)
{
	if(isEnable){
		sprite.setTexture(texture);
		window->draw(sprite);
	}
	else{
		spriteOpenDoor.setTexture(textureOpenDoor);
		window->draw(spriteOpenDoor);
	}
	if (canInteract) {
		window->draw(textInteract);
	}
}

void Door::setEnable(bool state)
{
	body->SetEnabled(state);
	isEnable = state;
}


