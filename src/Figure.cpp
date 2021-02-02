#include "Figure.h"

Figure::Figure(std::string field,bool draw) {
    this->field = field;
    this->draw = draw;
}

Figure::~Figure(){

}

Figure::Figure(){

};

std::string Figure::getField() { return this->field; }

bool Figure::getdraw(){return this->draw;}

void Figure::setField(std::string new_field) {
    this->field = new_field;
}

void Figure::setdraw(bool draw) {
    this->draw = draw;
}



