//
// Created by Alexandre Laferrère on 01/06/2022.
//

#ifndef GALLERYJOURNEY_EQUIPMENT_H
#define GALLERYJOURNEY_EQUIPMENT_H

#include "Object.h"
#include <vector>
#include <tuple>
#include "pugixml.hpp"

class Equipment : public Object {
public:
    explicit Equipment(std::string name, std::string sprite_path, int nb_copies,
              std::vector<std::tuple<std::string, int>> required_mats);
    explicit Equipment(pugi::xml_node node);
    std::vector<std::tuple<std::string, int>> & get_required_mats();
    bool possessed();
private:
    std::vector<std::tuple<std::string, int>> required_mats;
};

#endif //GALLERYJOURNEY_EQUIPMENT_H
