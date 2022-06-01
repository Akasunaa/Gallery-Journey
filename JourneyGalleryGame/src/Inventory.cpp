//
// Created by Alexandre Laferrère on 01/06/2022.
//

#include "Inventory.h"
#include <iostream>

Inventory::Inventory(){
    materials = std::map<std::string, std::unique_ptr<Material>>();
    equipment = std::map<std::string, std::unique_ptr<Equipment>>();
}

void Inventory::add_object_type(std::unique_ptr<Material> mat_type) {
    materials[mat_type->get_name()] = std::move(mat_type);
}

void Inventory::add_object_type(std::unique_ptr<Equipment> equip_type) {
    equipment[equip_type->get_name()] = std::move(equip_type);
}

void Inventory::remove_object_type(const std::string & obj_key) {
    if(materials.contains(obj_key)){
        materials.erase(obj_key);
    }
    else if(equipment.contains(obj_key)){
        equipment.erase(obj_key);
    }
}


void Inventory::add_material(const std::string & mat_key, const int & nb_copies) {
    if(!materials.contains(mat_key)){
        std::cout << " (add) ERROR : No material of this type defined \n" ;
        exit(1);
    }
    materials[mat_key]->increase_copies(nb_copies);
}

void Inventory::consume_material(const std::string & mat_key, const int & nb_copies) {
    if(!materials.contains(mat_key)){
        std::cout << "(consume) ERROR : No material of this type defined \n" ;
        exit(1);
    }
    if(materials[mat_key]->has_enough(nb_copies)){
        materials[mat_key]->decrease_copies(nb_copies);
    }
}

bool Inventory::is_craftable(const std::string & equip_key) {
    if(!equipment.contains(equip_key)){
        std::cout << "(is_craftable) ERROR : No equipment/collectible of this type defined \n" ;
        exit(1);
    }

    for(const auto & required : equipment[equip_key]->get_required_mats()){
        std::string mat_req = std::get<0>(required);
        int nb_required = std::get<1>(required);
        if(!materials.contains(mat_req)){
            std::cout << "(is_craftable) ERROR : the required material " << mat_req << " is not defined \n" ;
            exit(1);
        }
        if( !materials[mat_req]->has_enough(nb_required) ){
            return false;
        }
    }
    return true;
}

bool Inventory::is_crafted(const std::string & equip_key) {
    if(!equipment.contains(equip_key)){
        std::cout << "(is_crafted) ERROR : No equipment/collectible of this type defined \n" ;
        exit(1);
    }

    return equipment[equip_key]->possessed();
}

void Inventory::craft(const std::string & equip_key) {
    if(is_crafted(equip_key)){
        std::cout << "This object is already in your possession \n" ;
        return ;
    }

    if(is_craftable(equip_key)){
        for(const auto & required : equipment[equip_key]->get_required_mats()) {
            std::string mat_req = std::get<0>(required);
            int nb_required = std::get<1>(required);
            consume_material(mat_req, nb_required);
        }
        equipment[equip_key]->increase_copies(1);
    }
}

void Inventory::display_equipment() {
    std::cout << "--------- Equipement & Trésors ---------" << std::endl ;
    for(const auto & equip : equipment ){
        std::cout << "• " << equip.first << " ( "  << equip.second->get_nb_copies() << " ) " << std::endl;
    }
    std::cout << std::endl;
}

void Inventory::display_materials() {
    std::cout << "--------- Matériaux ---------" << std::endl ;
    for(const auto & mat : materials ){
        std::cout << "• " << mat.first << " ( "  << mat.second->get_nb_copies() << " ) " << std::endl;
    }
    std::cout << std::endl;
}

void Inventory::display_all() {
    std::cout << "========== INVENTAIRE ==========" << std::endl;
    std::cout << std::endl;
    display_equipment();
    display_materials();
    std::cout << "================================" << std::endl;
}
