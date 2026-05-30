#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Shape.hpp"

class Square;

class Rectangle : public Shape {
private:
    uint width, height;

protected:
    virtual void write(ostream& os) const override;

public:
    // Constructeurs
    Rectangle(EZColor col, uint x, uint y, uint w, uint h, uint thick = 1, bool fill = false);
    Rectangle(istream& is);
    Rectangle(const Square& s); 

    // Destructeur
    virtual ~Rectangle();

    // Accesseurs et Mutateurs
    inline uint getWidth() const { return width; }
    inline uint getHeight() const { return height; }
    inline void setWidth(uint w) { width = w; }
    inline void setHeight(uint h) { height = h; }

    virtual string getTypeName() const override { return "Rectangle"; }
    virtual void draw(EZWindow& win) const override;
    virtual void modifyAttributes() override;
};

#endif