//
// Created by Alexandre Laferrère on 30/05/2022.
//
#include "Object.h"

Object::Object(std::string name, std::string sprite_path, int nb_copies) :
        name(name),
        sprite_path(sprite_path),
        nb_copies(nb_copies)
{}

void Object::decrease_copies(int nb) {
    nb_copies -= nb;
    if(nb_copies < 0){ nb_copies = 0; }
}

void Object::increase_copies(int nb) {
    nb_copies += nb;
}

bool Object::has_enough(int nb_cop) {
    return nb_copies >= nb_cop;
}

std::string Object::get_name() {
    return name;
}

std::string Object::get_sprite_path() {
    return sprite_path;
}

int Object::get_nb_copies() {
    return nb_copies;
}