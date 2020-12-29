#include "Figure.h"

Figure::Figure(string field) {
    this->field = field;
}

Figure::~Figure(){

}

Figure::Figure(){

};

string Figure::getField() { return this->field; }

void Figure::setField(string new_field) {
    this->field = new_field;
}


