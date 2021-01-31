#include "Figure.h"

Figure::Figure(string field,bool draw) {
    this->field = field;
    this->draw = draw;
}

Figure::~Figure(){

}

Figure::Figure(){

};

string Figure::getField() { return this->field; }

bool Figure::getdraw(){return this->draw;}

void Figure::setField(string new_field) {
    this->field = new_field;
}

void Figure::setdraw(bool draw) {
    this->draw = draw;
}



