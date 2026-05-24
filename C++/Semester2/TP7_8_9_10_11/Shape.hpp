#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <string>
#include "ez-draw++.hpp"
#include "point.hpp"

using namespace std;

class Shape {
private:
    EZColor color;
    Point anchor;
    bool filled;
    uint thickness;

protected:
    virtual void write(ostream& os) const = 0; 

public:
    Shape(EZColor col, uint x, uint y, uint thick = 1, bool fill = false);
    Shape(istream& is);
    virtual ~Shape();

    // Accesseurs (Getters)
    inline const EZColor& getColor() const { return color; }
    inline const Point& getAnchor() const { return anchor; }
    inline bool isFilled() const { return filled; }
    inline uint getThickness() const { return thickness; }

    // Mutateurs (Setters)
    inline void setColor(const EZColor& col) { color = col; }
    inline void setAnchor(uint x, uint y) { anchor.setXY(x, y); }
    inline void setFilled(bool fill) { filled = fill; }
    inline void setThickness(uint thick) { thickness = thick; }

    // Méthodes Virtuelles Pures (le "= 0" signifie qu'elles sont abstraites)
    virtual string getTypeName() const = 0; 
    virtual void draw(EZWindow& win) const = 0;

    // Méthodes Virtuelles avec implémentation par défaut
    virtual bool isOver(uint mouseX, uint mouseY) const;
    virtual void modifyAttributes();

    // Surcharge de l'opérateur de flux (pour la sauvegarde)
    friend ostream& operator<<(ostream& os, const Shape& s);
    
    // Méthode statique 
    static Shape* load(istream& is);
};

#endif