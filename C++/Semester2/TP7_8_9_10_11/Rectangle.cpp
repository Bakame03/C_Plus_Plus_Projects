#include "Rectangle.hpp"
#include "Square.hpp" 

// Constructeur principal
Rectangle::Rectangle(EZColor col, uint x, uint y, uint w, uint h, uint thick, bool fill)
    : Shape(col, x, y, thick, fill), width(w), height(h) {}

// Constructeur depuis un flux 
Rectangle::Rectangle(istream& is) : Shape(is), width(0), height(0) {
    is >> width >> height;
}

// Constructeur à l'identique d'un Square
Rectangle::Rectangle(const Square& s) 
    : Shape(s.getColor(), s.getAnchor().getX(), s.getAnchor().getY(), s.getThickness(), s.isFilled()), 
      width(s.getWidth()), height(s.getWidth()) {} // Square a même largeur et hauteur

// Destructeur
Rectangle::~Rectangle() {}

// Implémentation de write
void Rectangle::write(ostream& os) const {
    os << width << " " << height;
}

// Implémentation du dessin
void Rectangle::draw(EZWindow& win) const {
    win.setColor(getColor());
    win.setThickness(getThickness());
    
    // Le point d'ancrage (x, y) est le coin haut-gauche
    uint x1 = getAnchor().getX();
    uint y1 = getAnchor().getY();
    uint x2 = x1 + width;
    uint y2 = y1 + height;

    if (isFilled()) {
        win.fillRectangle(x1, y1, x2, y2);
    } else {
        win.drawRectangle(x1, y1, x2, y2);
    }
}

// Menu interactif
void Rectangle::modifyAttributes() {
  char c; uint w, h;
  do {
    std::cout << "Current attributes values are:" << std::endl
    << "s - go to the sub-menu for the attributes of the Shape" << std::endl
    << "w - width  = " << getWidth() << std::endl
    << "h - height = " << getHeight() << std::endl
    << "q - quit or go back one level" << std::endl
    << "Choice?>"; std::cin >> c;
    
    switch(c) {
      case 's': Shape::modifyAttributes(); break; // Appel de la méthode de la classe mère
      case 'w': std::cout << "Give the new width value>"; std::cin >> w; setWidth(w); break;
      case 'h': std::cout << "Give the new height value>"; std::cin >> h; setHeight(h); break;
      case 'q': break;
      default:
        std::cout << "Error this choice does not exist. Try again." << std::endl;
    }
  } while(c!='q');
}