//
// Created by Alexandre Laferrère on 31/05/2022.
//

#ifndef GALLERYJOURNEY_MATERIAL_H
#define GALLERYJOURNEY_MATERIAL_H
#include "Object.h"
#include <vector>
#include <tuple>
#include "pugixml.hpp"

class Material : public Object {
public:
    explicit Material(std::string name, std::string sprite_path, int nb_copies, std::vector<std::tuple<int,int>> shape);
    explicit Material(pugi::xml_node node);
    std::vector<std::tuple<int,int>> get_shape();
private :
    std::vector<std::tuple<int,int>> shape;
};

#endif //GALLERYJOURNEY_MATERIAL_H
