#include "Enveloppe.hpp"    

Enveloppe::Enveloppe(EZColor col, uint x, uint y, uint L, bool recto, uint thick, bool fill)
    : Shape(col, x, y, thick, fill), L(L), recto(recto) {}

Enveloppe::Enveloppe(istream& is) : Shape(is), L(0), recto(false) {
    is >> L >> recto;
}

Enveloppe::~Enveloppe() {}

void Enveloppe::write(ostream& os) const {
    os << L << " " << recto;
}

void Enveloppe::draw(EZWindow& win) const {
    win.setColor(getColor());
    win.setThick(getThickness());
    uint x = getAnchor().getX();
    uint y = getAnchor().getY();
    uint w = L;       // largeur
    uint h = L / 2;   // hauteur = L/2
    // 1) Le corps de l'enveloppe : un rectangle
    win.drawRectangle(x, y, x + w, y + h);
    if (recto) {
        // RECTO : petit rectangle "adresse" au centre
        win.drawRectangle(x + w/4, y + h/2, x + 3*w/4, y + 3*h/4);
    }
    else {
        // VERSO : le rabat (un "V" depuis les deux coins du haut vers le centre)
        win.drawLine(x,     y, x + w/2, y + h/2);   // coin haut-gauche -> centre
        win.drawLine(x + w, y, x + w/2, y + h/2);   // coin haut-droit  -> centre
    }
}

void Enveloppe::modifyAttributes() {
    char c; uint l;
    do {
        std::cout << "Current attributes values are:" << std::endl
        << "s - sub-menu Shape" << std::endl
        << "L - L (width) = " << L << std::endl
        << "r - toggle recto/verso (currently " << (recto?"recto":"verso") << ")" << std::endl
        << "q - quit" << std::endl
        << "Choice?>"; std::cin >> c;
        switch(c) {
            case 's': Shape::modifyAttributes(); break;
            case 'L': std::cout << "New L>"; std::cin >> l; L = l; break;
            case 'r': recto = !recto; break;
            case 'q': break;
            default: std::cout << "Error." << std::endl;
        }
    } while(c != 'q');
}