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
              std::vector<std::tuple<std::string, int>> required_mats,
              std::vector<std::string> required_equip_upgrade);
    explicit Equipment(pugi::xml_node node);
    std::vector<std::tuple<std::string, int>> & get_required_mats();
    std::vector<std::string> & get_required_equip_upgrade();
    bool possessed();
    bool get_obselete();
    void set_obselete(bool obs);
private:
    std::vector<std::tuple<std::string, int>> required_mats;
    std::vector<std::string> required_equip_upgrade;
    bool obselete;
};

#endif //GALLERYJOURNEY_EQUIPMENT_H
