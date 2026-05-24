#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP

#include "Shape.hpp"

class Circle;

class Ellipse : public Shape {
private:
    uint width, height;

protected:
    virtual void write(ostream& os) const override;

public:
    Ellipse(EZColor col, uint x, uint y, uint w, uint h, uint thick = 1, bool fill = false);
    Ellipse(istream& is);
    Ellipse(const Circle& c); 

    virtual ~Ellipse();

    inline uint getWidth() const { return width; }
    inline uint getHeight() const { return height; }
    inline void setWidth(uint w) { width = w; }
    inline void setHeight(uint h) { height = h; }

    virtual string getTypeName() const override { return "Ellipse"; }
    virtual void draw(EZWindow& win) const override;
    virtual void modifyAttributes() override;
};

#endif