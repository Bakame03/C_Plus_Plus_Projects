#include "Point.hpp"

Point::Point(uint _x, uint _y) : x(_x), y(_y) {}

Point::Point(const Point& p) : x(p.x), y(p.y) {}

Point::Point(istream& is) : x(0), y(0) {
    is >> x >> y;
}

Point::~Point() {}

bool Point::isOver(uint mouseX, uint mouseY) const {
      // Avec une tolérance de 5 pixels (la taille du point)
    return (mouseX >= x - size && mouseX <= x + size && 
            mouseY >= y - size && mouseY <= y + size);
}

void Point::draw(EZWindow& win, bool filled) const {
    if (filled) {
        win.setColor(EZColor::red);
        win.fillRectangle(x - size, y - size, x + size, y + size);
    } else {
        win.setColor(EZColor::black);
        win.drawRectangle(x - size, y - size, x + size, y + size);
    }
}

ostream& operator<<(ostream& os, const Point& p) {
    os << p.x << " " << p.y;
    return os;
}

istream& operator>>(istream& is, Point& p) {
    is >> p.x >> p.y;
    return is;
}