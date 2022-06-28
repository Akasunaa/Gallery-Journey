#include "Door.h"

/*
Est debloquable et interractif, bloque le joueur s'il n'a pas l'objet demandé
*/

Door::Door(b2World* world, pugi::xml_node node, GameAssets* ga,
	std::unique_ptr<Inventory>& inventory) :
	UnlockableElement(inventory), InterractableObject{ world, node,widthDoor, heightDoor, ga }
{
	float x = node.attribute("posX").as_float();
	float y = node.attribute("posY").as_float();
	bodyDef.type = b2_staticBody; //Permet de bloquer le joueur 
	b2Vec2 pos{ x , y };
	bodyDef.position.Set(pos.x, pos.y);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(widthDoor / 2, heightDoor / 2);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	body->CreateFixture(&fixtureDef);

	body->SetEnabled(true);

	for (auto child : node.children()) {
		required.push_back(child.attribute("equipKey").value());
	}

	texture = ga->closeDoor;
	sprite.setScale((float)widthDoor / texture.getSize().x, (float)heightDoor / texture.getSize().y);
	sprite.setPosition(sf::Vector2f(x, y));

	textureOpenDoor = ga->openDoor;
	spriteOpenDoor.setScale((float)widthDoor / textureOpenDoor.getSize().x, (float)heightDoor / textureOpenDoor.getSize().y);
	spriteOpenDoor.setPosition(sf::Vector2f(x, y));
}

void Door::draw(sf::RenderWindow* window)
{
	if (!(isUnlock)) {
		sprite.setTexture(texture);
		window->draw(sprite);
	}
	else {
		spriteOpenDoor.setTexture(textureOpenDoor);
		window->draw(spriteOpenDoor);
	}
	if (canInteract) {
		window->draw(textInteract);
		draw_pop_up();
	}
}

void Door::unlock()
{
	body->SetEnabled(false);
	isUnlock = true;
}

void Door::draw_pop_up() {
	float width = WINDOW_W / 5;
	ImGui::Begin("Zone inaccessible", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);
	auto pos = this->getPosition();
	if (pos.x < WINDOW_W / 2) {
		ImGui::SetWindowPos(ImVec2(pos.x, pos.y));
	}
	else {
		ImGui::SetWindowPos(ImVec2(pos.x - width, pos.y));
	}
	ImGui::SetWindowFontScale(2);
	ImGui::SetWindowSize(ImVec2(width, 0));
	ImGui::Text("Équipements requis :");
	ImGui::Separator();

	const auto& equips = inventory->get_equipment();

	for (const auto& equip_req : required) {
		if (!equips.contains(equip_req)) {
			std::cout << "(is_craftable) ERROR : the required material " << equip_req << " is not defined \n";
			exit(1);
		}

		const auto& equip_obj = inventory->get_specific_equip(equip_req);

		ImGui::PushID((equip_req + "##TextRequired").c_str());
		std::string s = equip_obj->get_name();
		if (inventory->is_crafted(equip_req)) {
			s += " OK";
			ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor::HSV(115.0f / 360.0f, 1, 1));
		}
		else {
			s += " MANQUANT";
			ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor::HSV(0, 1, 1));
		}
		ImGui::BulletText(s.c_str());
		ImGui::PopStyleColor();
		ImGui::PopID();
	}

	ImGui::End();
}


