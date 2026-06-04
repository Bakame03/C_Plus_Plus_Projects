#ifndef ENVELOPPE_HPP
#define ENVELOPPE_HPP

#include "Shape.hpp"

class Enveloppe : public Shape {
    private :
        uint L;
        bool recto;
    protected :
        virtual void write(ostream& os) const override;
    public:
        Enveloppe(EZColor col, uint x, uint y, uint L, bool recto = false, uint thick = 1, bool fill = false);
        Enveloppe(istream& is);
        virtual ~Enveloppe();

        inline bool isRecto() const { return recto; }
        inline void setRecto(bool r) { recto = r; }
        virtual string getTypeName() const override { return "Enveloppe"; }
        virtual void draw(EZWindow& win) const override;
        virtual void modifyAttributes() override;
};

#endif