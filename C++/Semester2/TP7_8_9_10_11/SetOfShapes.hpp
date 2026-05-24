#ifndef SETOFSHAPES_HPP
#define SETOFSHAPES_HPP

#include <vector>
#include <iostream>
#include "Shape.hpp"

class SetOfShapes {
private:
    std::vector<Shape*> shapes; 
    uint maxSize;               

public:
    SetOfShapes(uint max);
    ~SetOfShapes();
    void add(Shape* s);
    Shape* isOver(uint mouse_x, uint mouse_y) const;
    void draw(EZWindow& win) const;
    friend ostream& operator<<(ostream& os, const SetOfShapes& set);
    void save(ostream& os) const;
    void load(istream& is);
};

#endif