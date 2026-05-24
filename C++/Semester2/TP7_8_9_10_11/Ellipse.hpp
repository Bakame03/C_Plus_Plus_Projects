#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP

#include "Shape.hpp"

class Circle;

class Ellipse : public Shape {
private:
    uint semiWidth, semiHeight;

protected:
    virtual void write(ostream& os) const override;

public:
    Ellipse(EZColor col, uint x, uint y, uint w, uint h, uint thick = 1, bool fill = false);
    Ellipse(istream& is);
    Ellipse(const Circle& c); 

    virtual ~Ellipse();

    inline uint getSemiWidth() const { return semiWidth; }
    inline uint getSemiHeight() const { return semiHeight; }
    inline void setSemiWidth(uint w) { semiWidth = w; }
    inline void setSemiHeight(uint h) { semiHeight = h; }

    virtual string getTypeName() const override { return "Ellipse"; }
    virtual void draw(EZWindow& win) const override;
    virtual void modifyAttributes() override;
};

#endif