//
// Created by Alexandre Laferrère on 01/06/2022.
//

#include "Material.h"

Material::Material(std::string name, std::string sprite_path, int nb_copies, std::vector<std::tuple<int, int>> shape) :
        Object(name, sprite_path, nb_copies),
        shape(shape)
        {}


