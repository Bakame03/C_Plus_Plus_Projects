#include "Exercise.hpp"

Exercise::Exercise(EZColor col, uint x, uint y, uint L, uint thick, bool fill)
    : Shape(col, x, y, thick, fill), L(L) {}

Exercise::Exercise(istream& is) : Shape(is), L(0) {
    is >> L;
}

Exercise::~Exercise() {}

void Exercise::write(ostream& os) const {
    os << L;
}

void Exercise::draw(EZWindow& win) const {
    uint x = getAnchor().getX();
    uint y = getAnchor().getY();

    // pour la couleur rouge du drapeau
    win.setColor(getColor());
    win.fillRectangle(x, y, x + L, y + L);

    // pour la croix blanche
    win.setColor(EZColor::white);
    win.fillRectangle(x + L/5,   y + 2*L/5, x + 4*L/5, y + 3*L/5); // barre horizontale
    win.fillRectangle(x + 2*L/5, y + L/5,   x + 3*L/5, y + 4*L/5); // barre verticale
}