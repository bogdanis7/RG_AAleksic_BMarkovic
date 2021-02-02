//
// Created by andri on 3.12.20..
//
#ifndef PROJECT_BASE_FIGURE_H
#define PROJECT_BASE_FIGURE_H
#include<string>

class Figure {
private:
    std::string field;
    bool draw;

public:
    ~Figure();
    Figure();
    Figure(std::string field,bool draw);
    std::string getField();
    void setField(std::string new_field);
    bool getdraw();
    void setdraw(bool draw);

};


#endif //PROJECT_BASE_FIGURE_H
