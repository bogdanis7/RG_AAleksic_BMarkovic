//
// Created by andri on 25.12.20..
//

#include "Field.h"
#include <algorithm>

Field::Field(string place, int a) :  {}

float* Field::draw() {
    float A_x = this->get_x() - a/2;
    float A_y = this->get_y() + a/2;
    float A_z = this->get_z();

    float B_x = this->get_x() + a/2;
    float B_y = this->get_y() + a/2;
    float B_z = this->get_z();

    float C_x = this->get_x() + a/2;
    float C_y = this->get_y() - a/2;
    float C_z = this->get_z();

    float D_x = this->get_x() - a/2;
    float D_y = this->get_y() - a/2;
    float D_z = this->get_z();

    float helper_vertices[] = {
            A_x, A_y, A_z,
            B_x, B_y, B_z,
            C_x, C_y, C_z,
            A_x, A_y, A_z,
            C_x, C_y, C_z,
            D_x, D_y, D_z,
    };

    auto *vertices = new float[18];
    for (int i = 0; i < 18; i ++) {
        vertices[i] = helper_vertices[i];
    }

    return vertices;
}
