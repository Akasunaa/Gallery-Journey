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
selected_item_inventory("None"),
material_just_found("None"){
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

    //On regarde si il y a des équipements nécessaire à l'amélioration, et si ils ont déjà été forgés.
    //(si il n'y en a pas, alors c'est un équipment de base)
    if(!is_previous_upgrade_done(equip_key)){
        return false;
    }

    //On vérifie si on dispose de tous les matériaux nécessaires et en quantité suffisante.
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

bool Inventory::is_previous_upgrade_done(const std::string &equip_key) {
    if(!equipment.contains(equip_key)){
        std::cout << "(is_previous_upgrade_done) ERROR : No equipment/collectible of this type defined \n" ;
        exit(1);
    }

    for(const auto & equip_for_upgrade : equipment[equip_key]->get_required_equip_upgrade()){
        if(!equipment.contains(equip_for_upgrade)){
            std::cout << "(is_previous_upgrade_done) ERROR : The required equipment for this upgrade of this type is not defined \n" ;
            exit(1);
        }
        if(!is_crafted(equip_for_upgrade)){
            return false;
        }
    }
    return true;
}

bool Inventory::is_one_of_previous_upgrade_done(const std::string &equip_key) {
    if(!equipment.contains(equip_key)){
        std::cout << "(is_one_of_previous_upgrade_done) ERROR : No equipment/collectible of this type defined \n" ;
        exit(1);
    }
    auto required_equip_upgrade = equipment[equip_key]->get_required_equip_upgrade();
    if(required_equip_upgrade.size() == 0){
        return true; //si il s'agit d'un équipement de base, on renvoit vrai aussi.
    }

    for(const auto & equip_for_upgrade : required_equip_upgrade){
        if(!equipment.contains(equip_for_upgrade)){
            std::cout << "(is_one_of_previous_upgrade_done) ERROR : The required equipment for this upgrade of this type is not defined \n" ;
            exit(1);
        }
        if(is_crafted(equip_for_upgrade)){
            return true;
        }
    }
    return false;
}

void Inventory::craft(const std::string & equip_key) {
    if(is_crafted(equip_key)){
        std::cout << "This object is already in your possession \n" ;
        return ;
    }

    if(is_craftable(equip_key)){
        for(const auto & previous_upgrade : equipment[equip_key]->get_required_equip_upgrade()){
            equipment[previous_upgrade]->set_obselete(true);
        }
        for(const auto & required : equipment[equip_key]->get_required_mats()) {
            std::string mat_req = std::get<0>(required);
            int nb_required = std::get<1>(required);
            consume_material(mat_req, nb_required);
        }
        clear_selected_item_inventory();
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

    ImGui::PushID("Selected_Equip");
    ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor::HSV(150.0f/360.0f ,0.3,0.9));
    ImGui::TextUnformatted(text.c_str());
    ImGui::PopStyleColor();
    ImGui::PopID();

    ImGui::Separator();
    ImGui::Indent();
    //TODO Sprite affichage
    //ImGui::SetWindowFontScale(1);
    ImGui::PushID((text + "##description").c_str());
    ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor::HSV(0.5,0.6,0.9));
    ImGui::TextWrapped("Texte de description à compléter un jour.");
    ImGui::PopStyleColor();
    ImGui::PopID();
}

void Inventory::draw_craft(std::string equip_key) {
    ImGui::PushID("Selected_Equip");
    ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor::HSV(150.0f/360.0f ,0.3,0.9));
    ImGui::TextUnformatted(equipment[equip_key]->get_name().c_str());
    ImGui::PopStyleColor();
    ImGui::PopID();
    ImGui::Indent();
    //TODO Sprite affichage
    //ImGui::SetWindowFontScale(1);


    auto req_for_upgrade = equipment[equip_key]->get_required_equip_upgrade();
    if(req_for_upgrade.size() > 0){
        ImGui::Separator();
        ImGui::Text("ÉQUIPEMENTS REQUIS :");
        for(const auto & req_equip: req_for_upgrade){
            ImGui::PushID((req_equip + "##TextRequiredForUpgrade").c_str());
            if (is_crafted(req_equip)) {
                ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4) ImColor::HSV(115.0f / 360.0f, 1, 1));
            } else {
                ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4) ImColor::HSV(0, 1, 1));
            }
            ImGui::BulletText(req_equip.c_str());
            ImGui::PopStyleColor();
            ImGui::PopID();

        }
    }
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
            ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4) ImColor::HSV(115.0f / 360.0f, 1, 1));
        } else {
            ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4) ImColor::HSV(0, 1, 1));
        }
        ImGui::BulletText(s.c_str());
        ImGui::PopStyleColor();
        ImGui::PopID();
    }

        ImGui::Separator();

        ImGui::PushID(equip_key.c_str());
        if(is_craftable(equip_key)){
            ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4) ImColor::HSV(115.0f / 360.0f, 1, 1));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4) ImColor::HSV(145.0f/360.0f, 0.6, 0.9));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4) ImColor::HSV(145.0f/360.0f, 0.6, 0.9));
        }else {
            ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4) ImColor::HSV(245.0f/ 360.0f , 0, 0.7));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4) ImColor::HSV(1, 1, 1));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4) ImColor::HSV(1, 1, 1));
        }


    if(ImGui::Button("FORGER") && is_craftable(equip_key)){

            //Si on clique sur le bouton "forger" et que l'équipement est craftable,alors on le craft
            craft(equip_key);
            //et on  affiche un pop-up pour dire que ça a été fait avec succès
            ImGui::OpenPopup("SUCCES");
    }
    if(ImGui::BeginPopupModal("SUCCES", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::SetWindowFontScale(3);
        ImGui::Text(("Craft réussi : " + equipment[equip_key]->get_name() + " ! ").c_str());
        ImGui::Separator();

        if(ImGui::Button("OK", ImVec2(120, 0))){
                    ImGui::CloseCurrentPopup();
                    clear_selected_equip_craft();
                }
        ImGui::EndPopup();
    }
    ImGui::PopStyleColor(3);
    ImGui::PopID();
}

void Inventory::draw_inventory_screen() {
    ImGui::Begin("Inventaire (Appuyez sur \"I\" ou \"Q\" pour quitter)",NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    ImGui::SetWindowPos(ImVec2(0,0));
    ImGui::SetWindowFontScale(3);
    ImGui::SetWindowSize(ImVec2(WINDOW_W,WINDOW_H));
    {
        ImGui::BeginChild("Inventory_Left",
                          ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, ImGui::GetWindowHeight()),
                          true, NULL);
        ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
        if(ImGui::BeginTabBar("Inventory_tab", tab_bar_flags)){
            if(ImGui::BeginTabItem("Équipements & Trésors")){

                for(const auto & [equip_key, equip_obj] : equipment ){

                    if(is_crafted(equip_key) && !(equipment[equip_key]->get_obselete()) ){
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
                        if(ImGui::Selectable((name_mat + "(" + std::to_string(mat_obj->get_nb_copies()) +")").c_str(),
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
    ImGui::Begin("Table de Craft (Appuyez sur \"Q\" pour quitter)",NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    ImGui::SetWindowPos(ImVec2(0,0));
    ImGui::SetWindowFontScale(3);
    ImGui::SetWindowSize(ImVec2(WINDOW_W,WINDOW_H));

    {
        ImGui::BeginChild("Craft_Screen_Left",
                          ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, ImGui::GetWindowHeight()),
                          true, NULL);

        ImGui::PushID("List");
        ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor::HSV(60.0f/360.0f ,0.5,0.9));
        ImGui::TextUnformatted("Listes des objets à forger");
        ImGui::PopStyleColor();
        ImGui::PopID();

        ImGui::Separator();
        for(const auto & [equip_key, equip_obj] : equipment ){

            if(! is_crafted(equip_key) && is_one_of_previous_upgrade_done(equip_key)){
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

void Inventory::draw_pop_up_found() {
    if(material_just_found.compare("None") == 0){
        return;
    }
    ImGui::Begin("Pop_up_found");
    ImGui::OpenPopup("Matériau obtenu !");
    if(ImGui::BeginPopupModal("Matériau obtenu !", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
    ImGui::SetWindowFontScale(3);
    ImGui::Text("Vous avez trouvé : ");
    ImGui::SameLine();
        ImGui::PushID("Founded material");
        ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor::HSV(60.0f/360.0f ,0.5,0.9));
        ImGui::Text((materials[material_just_found]->get_name()).c_str());
        ImGui::PopStyleColor();
        ImGui::PopID();
    ImGui::Separator();
        ImGui::PushID("Already in possession");
        ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor::HSV(20.0f/360.0f ,0.35,0.9));
        ImGui::Text("Vous en avez ");
        ImGui::SameLine();
            ImGui::PushID("Already in possession");
            ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor::HSV(320.0f/360.0f ,0.6,0.9));
            ImGui::Text((std::to_string(materials[material_just_found]->get_nb_copies())).c_str());
            ImGui::PopStyleColor();
            ImGui::PopID();
        ImGui::SameLine();
        ImGui::Text(" en votre possesssion ");
        ImGui::PopStyleColor();
        ImGui::PopID();

    ImGui::EndPopup();
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

void Inventory::set_just_found(std::string mat_found_key) {
    material_just_found = mat_found_key;
}

void Inventory::clear_just_found() {
    material_just_found = "None";
}

const std::string & Inventory::get_just_found() {
    return material_just_found;
}

std::unique_ptr<Equipment> &Inventory::get_specific_equip(std::string equip_key) {
    if(!equipment.contains(equip_key)){
        std::cout << "(get_specific_equip) ERROR : No equipment/collectible of this type defined \n" ;
        exit(1);
    }
    return equipment[equip_key];
}

