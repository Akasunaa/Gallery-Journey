//
// Created by Alexandre Laferrère on 01/06/2022.
//

#include "Material.h"

Material::Material(std::string name, std::string sprite_path, int nb_copies, std::vector<std::tuple<int, int>> shape) :
        Object(name, sprite_path, nb_copies),
        shape(shape)
        {}


Material::Material(pugi::xml_node node) :
Object{node.attribute("name").value(),
       node.attribute("sprite").value(),
       node.attribute("nb").as_int()} {
    shape = std::vector<std::tuple<int,int>>();
    for(auto child : node.children()){
        shape.push_back({child.attribute("x").as_int(), child.attribute("y").as_int()});
    }
}

std::vector<std::tuple<int, int>> Material::get_shape() {
    return shape;
}