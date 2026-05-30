#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "Rectangle.hpp"

class Square : public Rectangle {
public:
    // Constructeur : on initialise width et height avec la même valeur 'size'
    Square(EZColor col, uint x, uint y, uint size, uint thick = 1, bool fill = false);
    Square(istream& is);
    
    virtual ~Square();

    // Accesseur et Mutateur
    inline uint getSize() const { return getWidth(); }
    void setSize(uint s);

protected:
    virtual void write(ostream& os) const override;

public:

    // Redéfinition des méthodes virtuelles
    virtual string getTypeName() const override { return "Square"; }
    virtual void modifyAttributes() override;
};

#endif