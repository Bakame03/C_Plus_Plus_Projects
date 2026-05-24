#include "SetOfShapes.hpp"

// Constructeur : on initialise la taille max
SetOfShapes::SetOfShapes(uint max) : maxSize(max) {}

SetOfShapes::~SetOfShapes() {
    for (Shape* s : shapes) {
        delete s;
    }
}

void SetOfShapes::add(Shape* s) {
    if (shapes.size() < maxSize) {
        shapes.push_back(s);
    }
}

void SetOfShapes::draw(EZWindow& win) const {
    for (Shape* s : shapes) {
        s->draw(win);
        s->getAnchor().draw(win, false);
    }
}

Shape* SetOfShapes::isOver(uint mouse_x, uint mouse_y) const {
    for (int i = shapes.size() - 1; i >= 0; i--) {
        if (shapes[i]->isOver(mouse_x, mouse_y)) {
            return shapes[i];
        }
    }
    return nullptr;
}

ostream& operator<<(ostream& os, const SetOfShapes& set) {
    os << set.shapes.size() << std::endl;
    for (Shape* s : set.shapes) {
        os << *s << std::endl; 
    }
    return os;
}

void SetOfShapes::save(ostream& os) const {
    os << *this;
}

void SetOfShapes::load(istream& is) {
    uint count;
    is >> count;
    for(uint i = 0; i < count; i++) {
        Shape* s = Shape::load(is);
        if (s != nullptr) {
            add(s);
        }
    }
}