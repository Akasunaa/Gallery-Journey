//
// Created by Alexandre Laferrère on 01/06/2022.
//

#include "Equipment.h"
#include <string_view>
#include <iostream>

using namespace std::literals;

Equipment::Equipment(std::string name, std::string sprite_path, int nb_copies,
                     std::vector<std::tuple<std::string, int>> required_mats,
                     std::vector<std::string> required_equip_upgrade) :
        Object(name, sprite_path, nb_copies),
        required_mats(required_mats),
        required_equip_upgrade(required_equip_upgrade)
{}

Equipment::Equipment(pugi::xml_node node) :
Object{node.attribute("name").value(),
        node.attribute("sprite").value(),
        node.attribute("nb").as_int()}{


    required_mats = std::vector<std::tuple<std::string, int>>();
    for(auto child : node.children()){
        if (child.name() == "Required"sv) {
            required_mats.push_back({child.attribute("mat").value(), child.attribute("need").as_int()});
        }
        if(child.name() == "UpgradeReq"sv){
            required_equip_upgrade.push_back(child.attribute("equip").value());
        }
    }
}


std::vector<std::tuple<std::string, int>> & Equipment::get_required_mats() {
    return required_mats;
}

std::vector<std::string> &Equipment::get_required_equip_upgrade() {
    return required_equip_upgrade;
}

bool Equipment::possessed() {
    return get_nb_copies() > 0;
}