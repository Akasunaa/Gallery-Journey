//
// Created by Alexandre Laferrère on 01/06/2022.
//

#include "Equipment.h"

Equipment::Equipment(std::string name, std::string sprite_path, int nb_copies,
                     std::vector<std::tuple<std::string, int>> required_mats) :
                     Object(name, sprite_path, nb_copies),
                     required_mats(required_mats)
                     {}

bool Equipment::possessed() {
    return get_nb_copies() > 0;
}