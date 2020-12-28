//
// Created by andri on 25.12.20..
//

#include "Entity.h"
#include <algorithm>

Entity::Entity(float x, float y, float z, vector<float> id_color) : x(x), y(y), z(z) {
    for (unsigned i=0; i<id_color.size(); i++) {
        this->id_color.push_back(id_color[i]);
    }
}

virtual ~Entity(){}

float Entity::get_x() const { return this->x; }
float Entity::get_y() const { return this->y; }
float Entity::get_z() const { return this->z; }

vector<float> Entity::get_color() { return this->id_color; }

void Entity::set_position(float new_x, float new_y, float new_z) {
    this->x = new_x;
    this->y = new_y;
    this->z = new_z;
}
