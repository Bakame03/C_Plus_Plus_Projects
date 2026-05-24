#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "Ellipse.hpp"

class Circle : public Ellipse {
public:
    // Constructeur : on initialise l'ellipse avec width = height = rayon * 2
    Circle(EZColor col, uint x, uint y, uint radius, uint thick = 1, bool fill = false);
    Circle(istream& is);
    
    virtual ~Circle();

    // Accesseur et Mutateur
    inline uint getRadius() const { return getWidth() / 2; }
    void setRadius(uint r);

    // Redéfinition des méthodes virtuelles
    virtual string getTypeName() const override { return "Circle"; }
    virtual void modifyAttributes() override;
};

#endif