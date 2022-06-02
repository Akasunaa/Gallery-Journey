//
// Created by Alexandre Laferrère on 01/06/2022.
//

#include "Equipment.h"

Equipment::Equipment(std::string name, std::string sprite_path, int nb_copies,
                     std::vector<std::tuple<std::string, int>> required_mats) :
        Object(name, sprite_path, nb_copies),
        required_mats(required_mats)
{}

Equipment::Equipment(pugi::xml_node node) :
Object{node.attribute("name").value(),
        node.attribute("sprite").value(),
        node.attribute("nb").as_int()}{


    required_mats = std::vector<std::tuple<std::string, int>>();
    for(auto child : node.children()){
        required_mats.push_back({child.attribute("mat").value(), child.attribute("need").as_int()});
    }
}


std::vector<std::tuple<std::string, int>> & Equipment::get_required_mats() {
    return required_mats;
}
bool Equipment::possessed() {
    return get_nb_copies() > 0;
}