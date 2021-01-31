//
// Created by andri on 3.12.20..
//

#ifndef PROJECT_BASE_FIGURE_H
#define PROJECT_BASE_FIGURE_H

class Figure {
private:
    string field;
    bool draw;

public:
    ~Figure();
    Figure();
    Figure(string field,bool draw);
    string getField();
    void setField(string new_field);
    bool getdraw();
    void setdraw(bool draw);

};


#endif //PROJECT_BASE_FIGURE_H
