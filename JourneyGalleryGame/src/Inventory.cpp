//
// Created by Alexandre Laferrère on 01/06/2022.
//

#include "Inventory.h"

Inventory::Inventory(){
    materials = std::map<std::string, std::unique_ptr<Material>>();
    equipment = std::map<std::string, std::unique_ptr<Equipment>>();
}
