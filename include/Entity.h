//
// Created by andri on 25.12.20..
//

#ifndef PROJECT_BASE_ENTITY_H
#define PROJECT_BASE_ENTITY_H
#include <vector>

#define COLOR_SHAPE 4

using namespace std;

class Entity {

private:
    vector<float> id_color;
    float x, y, z;

public:

    Entity(float x, float y, float z, vector<float> id_color);
     ~Entity();
    void set_position(float new_x, float new_y, float new_z);
    vector<float> get_color();
    float get_x() const;
    float get_y() const;
    float get_z() const;
    virtual float* draw() = 0;

};


#endif //PROJECT_BASE_ENTITY_H
