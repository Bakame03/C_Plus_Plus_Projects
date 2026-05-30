#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include "ez-draw++.hpp"
using namespace std;

typedef unsigned int uint;

class Point {
    private:
        static const uint size = 5;
        uint x, y;
    public:
        Point(uint _x, uint _y);
        Point(const Point& p);
        Point(istream& is);
        ~Point();
        inline uint getX() const { return x; }
        inline uint getY() const { return y; }
        inline void setXY(uint _x, uint _y) { x = _x; y = _y; }
        bool isOver(uint mouseX, uint mouseY) const;
        void draw(EZWindow& win, bool filled = false) const;
        friend ostream& operator<<(ostream& os, const Point& p);
        friend istream& operator>>(istream& is, Point& p);
};

#endif