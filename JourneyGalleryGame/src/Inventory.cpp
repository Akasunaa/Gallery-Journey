//
// Created by Alexandre Laferrère on 01/06/2022.
//

#include "Inventory.h"
#include <string_view>
#include <iostream>


using namespace std::literals;

Inventory::Inventory() :
materials(std::map<std::string, std::unique_ptr<Material>>()),
equipment(std::map<std::string, std::unique_ptr<Equipment>>()),
selected_equip_craft("None"),
selected_item_inventory("None"){
}

void Inventory::init_inventory(pugi::xml_node node) {
    for(auto child : node.children()){
        if (child.name() == "Material"sv)
        {
            std::cout << "Adding " << child.attribute("name").value() << " to materials\n";
            add_object_type(std::make_unique<Material>(child));
        }
        else if (child.name() == "Equipment"sv)
        {
            std::cout << "Adding " << child.attribute("name").value() << " to equipment\n";
            add_object_type(std::make_unique<Equipment>(child));
        }
    }
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

bool Inventory::is_equip_craft_selected() {
    return(! (selected_equip_craft.compare("None") == 0) );
}

bool Inventory::is_item_inventory_selected() {
    return(! (selected_item_inventory.compare("None") == 0) );
}

void Inventory::display_equipment(int mode) {
    std::cout << "----- Equipement & Trésors -----" << std::endl ;
    for(const auto & equip : equipment ){

        if(mode == DISPLAY_ALL_EQUIP
        || (mode == DISPLAY_ACQUIRED_EQUIP && is_crafted(equip.first))
        || (mode == DISPLAY_NOT_ACQUIRED_EQUIP && !(is_crafted(equip.first)) ) ){

            std::cout << "• " << equip.first ;
            if(mode == DISPLAY_ALL_EQUIP){
                std::cout << " ( "  << equip.second->get_nb_copies() << " ) ";
            }
            std::cout << std::endl;

        }

    }
}

void Inventory::display_required(const std::string & equip_key) {
    if(!equipment.contains(equip_key)){
        std::cout << "(display_required) ERROR : No equipment/collectible of this type defined \n" ;
        exit(1);
    }
    std::cout << "----- Matériaux requis -----" << std::endl;
    for(const auto & [mat_req, nb_required] : equipment[equip_key]->get_required_mats()){
        if(!materials.contains(mat_req)){
            std::cout << "(is_craftable) ERROR : the required material " << mat_req << " is not defined \n" ;
            exit(1);
        }
        const auto & material = materials[mat_req];
        std::cout << "• " << material->get_name() << " "
        << material->get_nb_copies() << "/" << nb_required << std::endl;
    }
}

void Inventory::display_materials(int mode) {
    std::cout << "---------- Matériaux ----------" << std::endl ;
    for(const auto & mat : materials ){
        if(mode == DISPLAY_ALL_MAT
        ||(mode == DISPLAY_POSSESSED_MAT && mat.second->has_enough(1)) ) {
            std::cout << "• " << mat.first << " ( " << mat.second->get_nb_copies() << " ) " << std::endl;
        }
    }
}

void Inventory::display_all(int mode_material, int mode_equipment) {
    std::cout << "========== INVENTAIRE ==========" << std::endl;
    display_equipment(mode_equipment);
    display_materials(mode_material);
    std::cout << "================================" << std::endl;
}

void Inventory::draw_object_info(std::string object_key) {
    std::string text;
    std::string sprite_path;

    if(materials.contains(object_key)){
        text =  materials[object_key]->get_name();
        sprite_path = materials[object_key]->get_sprite_path();
    }
    else if(equipment.contains(object_key)){
        text =  equipment[object_key]->get_name();
        sprite_path = equipment[object_key]->get_sprite_path();
    }

    ImGui::TextUnformatted(text.c_str());
    ImGui::Indent();
    //TODO Sprite affichage
    //ImGui::SetWindowFontScale(1);
    ImGui::TextColored((ImVec4)ImColor::HSV(190,80,100),"Texte de description à compléter.");
}

void Inventory::draw_craft(std::string equip_key) {
    ImGui::TextUnformatted(equipment[equip_key]->get_name().c_str());
    ImGui::Indent();
    //TODO Sprite affichage
    //ImGui::SetWindowFontScale(1);
    ImGui::Separator();
    ImGui::Text("MATÉRIAUX REQUIS :");

    for(const auto & [mat_req, nb_required] : equipment[equip_key]->get_required_mats()) {
        if (!materials.contains(mat_req)) {
            std::cout << "(is_craftable) ERROR : the required material " << mat_req << " is not defined \n";
            exit(1);
        }
        const auto &material = materials[mat_req];
        std::string s = material->get_name() + " " + std::to_string(material->get_nb_copies())
                        + "/" + std::to_string(nb_required);

        ImGui::PushID((mat_req + "##TextRequired").c_str());
        if (material->has_enough(nb_required)) {
            ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4) ImColor::HSV(120, 100, 100));

        } else {
            ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4) ImColor::HSV(0, 100, 100));
        }
        ImGui::BulletText(s.c_str());
        ImGui::PopStyleColor();
        ImGui::PopID();
    }

        ImGui::Separator();

        //TODO BOUTON FORGER

        ImGui::PushID(equip_key.c_str());
        if(is_craftable(equip_key)){
            ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4) ImColor::HSV(120, 100, 100));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4) ImColor::HSV(120, 100, 100));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4) ImColor::HSV(120, 100, 100));
        }else {
            ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4) ImColor::HSV(120, 100, 100));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4) ImColor::HSV(120, 100, 100));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4) ImColor::HSV(120, 100, 100));
        }
        if(ImGui::Button("FORGER") && is_craftable(equip_key)){
            //Si on clique sur le bouton "forger" et que l'équipement est craftable,alors on le craft
            craft(equip_key);
            //et on  affiche un pop-up pour dire que ça a été fait avec succès
            ImGui::OpenPopup("Craft réussi");
            if(ImGui::BeginPopupModal("Craft", NULL, ImGuiWindowFlags_AlwaysAutoResize)){
                ImGui::Text(("Craft réussi : " + equipment[equip_key]->get_name() + " ! ").c_str());
                if(ImGui::Button("OK")){
                    ImGui::CloseCurrentPopup();
                }
                clear_selected_equip_craft();
            }

        }
        ImGui::PopStyleColor(3);
        ImGui::PopID();
}

void Inventory::draw_inventory_screen() {
    ImGui::Begin("Inventaire",NULL);
    ImGui::SetWindowPos(ImVec2(0,0));
    //ImGui::SetWindowFontScale(1);
    ImGui::SetWindowSize(ImVec2(WINDOW_W,WINDOW_H));
    {
        ImGui::BeginChild("Inventory_Left",
                          ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, ImGui::GetWindowHeight()),
                          true, NULL);
        ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
        if(ImGui::BeginTabBar("Inventory_tab", tab_bar_flags)){
            if(ImGui::BeginTabItem("Équipements & Trésors")){

                for(const auto & [equip_key, equip_obj] : equipment ){

                    if(is_crafted(equip_key)){
                        std::string name_equip = equip_obj->get_name();
                        if(ImGui::Selectable(name_equip.c_str(),
                                             (selected_item_inventory.compare(name_equip) == 0))){
                            selected_item_inventory = name_equip;
                        }
                    }

                }
                ImGui::EndTabItem();
            }
            if(ImGui::BeginTabItem("Matériaux")){

                for(const auto & [mat_key, mat_obj] : materials ){

                    if(mat_obj->has_enough(1)){
                        std::string name_mat = mat_obj->get_name();
                        if(ImGui::Selectable(name_mat.c_str(),
                                             (selected_item_inventory.compare(name_mat) == 0))){
                            selected_item_inventory = name_mat;
                        }
                    }

                }
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
        ImGui::EndChild();
    }
    ImGui::SameLine();
    if(is_item_inventory_selected()){
        ImGui::BeginChild("Inventory_Right",
                          ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, ImGui::GetWindowHeight()),
                          true, NULL);
        draw_object_info(selected_item_inventory);
        ImGui::EndChild();
    }
    ImGui::End();
}

void Inventory::draw_craft_screen() {
    ImGui::Begin("Craft_Screen",NULL);
    ImGui::SetWindowPos(ImVec2(0,0));
    //ImGui::SetWindowFontScale(1);
    ImGui::SetWindowSize(ImVec2(WINDOW_W,WINDOW_H));

    {
        ImGui::BeginChild("Craft_Screen_Left",
                          ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, ImGui::GetWindowHeight()),
                          true, NULL);
        ImGui::TextUnformatted("Listes des objets à forger");
        for(const auto & [equip_key, equip_obj] : equipment ){

            if(! is_crafted(equip_key)){
                std::string name_equip = equip_obj->get_name();
                if(ImGui::Selectable(name_equip.c_str(),
                                     (selected_equip_craft.compare(name_equip) == 0))){
                    selected_equip_craft = name_equip;
                }
            }

        }
        ImGui::EndChild();
    }
    ImGui::SameLine();

    if(is_equip_craft_selected()){
        ImGui::BeginChild("Craft_Screen_Right",
                          ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, ImGui::GetWindowHeight()),
                          true, NULL);
        draw_craft(selected_equip_craft);
        ImGui::EndChild();
    }
    ImGui::End();

}

std::map<std::string, std::unique_ptr<Material>> &Inventory::get_materials() {
    return materials;
}

std::map<std::string, std::unique_ptr<Equipment>> &Inventory::get_equipment() {
    return equipment;
}

void Inventory::clear_selected_equip_craft() {
    selected_equip_craft = "None";
}

void Inventory::clear_selected_item_inventory() {
    selected_item_inventory = "None";
}

