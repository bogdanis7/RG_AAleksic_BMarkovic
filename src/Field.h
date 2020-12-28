//
// Created by andri on 25.12.20..
//

#ifndef PROJECT_BASE_FIELD_H
#define PROJECT_BASE_FIELD_H
#include "Entity.h"

class Field {
private:
    string place;
public:
    Field(string place);
    float* draw() ;
};


#endif //PROJECT_BASE_FIELD_H
