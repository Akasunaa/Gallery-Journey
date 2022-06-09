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
#include <../imgui_lib/imgui.h>
#include <../imgui_lib/imgui-SFML.h>
#define DISPLAY_ALL_MAT 0
#define DISPLAY_POSSESSED_MAT 1
#define DISPLAY_ALL_EQUIP 0
#define DISPLAY_ACQUIRED_EQUIP 1
#define DISPLAY_NOT_ACQUIRED_EQUIP 2
#define WINDOW_W 1920
#define WINDOW_H 1080


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
    bool is_item_inventory_selected();
    bool is_equip_craft_selected();

    std::map<std::string, std::unique_ptr<Material>> & get_materials();
    std::map<std::string, std::unique_ptr<Equipment>> & get_equipment();
    std::unique_ptr<Equipment> & get_specific_equip(std::string equip_key);
    void clear_selected_item_inventory();
    void clear_selected_equip_craft();
    void set_just_found(std::string mat_found_key);
    const std::string & get_just_found();


    void display_equipment(int mode);
    void display_required(const std::string & equip_key);
    void display_materials(int mode);
    void display_all(int material_mode, int equipement_mode);

    void draw_object_info(std::string object_key);
    void draw_craft(std::string equip_key);
    void draw_inventory_screen();
    void draw_craft_screen();
    void draw_pop_up_found();

private :
    std::map<std::string, std::unique_ptr<Material>> materials;
    std::map<std::string, std::unique_ptr<Equipment>> equipment;
    std::string selected_item_inventory;
    std::string selected_equip_craft;
    std::string material_just_found;
};

#endif //GALLERYJOURNEY_INVENTORY_H
