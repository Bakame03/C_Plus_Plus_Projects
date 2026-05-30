#include "Point.hpp"

Point::Point(uint _x, uint _y) : x(_x), y(_y) {}

Point::Point(const Point& p) : x(p.x), y(p.y) {}

Point::Point(istream& is) : x(0), y(0) {
    is >> x >> y;
}

Point::~Point() {}

bool Point::isOver(uint mouseX, uint mouseY) const {
    // Le carré s'étend de size pixels vers la droite et le bas
    return (mouseX >= x && mouseX <= x + size && 
            mouseY >= y && mouseY <= y + size);
}

void Point::draw(EZWindow& win, bool isActive) const {
    if (isActive) {
        win.setColor(EZColor::red);
        win.fillRectangle(x, y, x + size, y + size);
    } else {
        win.setColor(EZColor::black);
        win.drawRectangle(x, y, x + size, y + size);
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