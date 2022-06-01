//
// Created by Alexandre Laferrère on 30/05/2022.
//

#ifndef GALLERYJOURNEY_OBJECT_H
#define GALLERYJOURNEY_OBJECT_H

#include <stdio.h>
#include <string>

class Object {
public:
    explicit Object(std::string name, std::string sprite_path, int nb_copies);
    void increase_copies(int nb);
    void decrease_copies(int nb);
    bool has_enough(int nb_copies);
    std::string get_name();
    int get_nb_copies();
protected:
    std::string name;
    std::string sprite_path;
    int nb_copies;
};

#endif //GALLERYJOURNEY_OBJECT_H
