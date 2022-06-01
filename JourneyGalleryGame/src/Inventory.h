//
// Created by Alexandre Laferrère on 01/06/2022.
//


#ifndef GALLERYJOURNEY_INVENTORY_H
#define GALLERYJOURNEY_INVENTORY_H
#include <string>
#include <map>
#include <memory>
#include "pugixml.hpp"
#include "Material.h"
#include "Equipment.h"


class Inventory {
public:
    explicit Inventory();
    void init_inventory(pugi::xml_node node);
    void add_object_type(std::unique_ptr<Equipment> equip_type);
    void add_object_type(std::unique_ptr<Material> mat_type);
    void remove_object_type(const std::string & obj_key);
    void add_material(const std::string& mat_key, const int & nb_copies);
    void consume_material(const std::string & mat_key, const int & nb_copies);
    bool is_craftable(const std::string & equip_key);
    bool is_crafted(const std::string & equip_key);
    void craft(const std::string & equip_key);
    void display_equipment();
    void display_materials();
    void display_all();
private :
    std::map<std::string, std::unique_ptr<Material>> materials;
    std::map<std::string, std::unique_ptr<Equipment>> equipment;
};

#endif //GALLERYJOURNEY_INVENTORY_H
