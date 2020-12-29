//
// Created by andri on 3.12.20..
//

#ifndef PROJECT_BASE_FIGURE_H
#define PROJECT_BASE_FIGURE_H

class Figure {
private:
    string field;

public:
    ~Figure();
    Figure();
    Figure(string field);
    string getField();
    void setField(string new_field);

};


#endif //PROJECT_BASE_FIGURE_H
