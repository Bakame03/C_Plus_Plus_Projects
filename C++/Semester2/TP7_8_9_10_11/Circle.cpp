#include "Circle.hpp"

// On appelle le constructeur de Ellipse avec width = height = radius * 2
Circle::Circle(EZColor col, uint x, uint y, uint radius, uint thick, bool fill)
    : Ellipse(col, x, y, radius * 2, radius * 2, thick, fill) {}

// Constructeur depuis flux : on appelle le constructeur de Ellipse
Circle::Circle(istream& is) : Ellipse(is) {}

Circle::~Circle() {}

void Circle::setRadius(uint r) {
    setSemiWidth(r * 2);
    setSemiHeight(r * 2);
}

void Circle::modifyAttributes() {
  char c; uint r;
  do {
    std::cout << "Current attributes values are:" << std::endl
    << "s - sub-menu Shape" << std::endl
    << "r - radius = " << getRadius() << std::endl
    << "q - quit" << std::endl
    << "Choice?>"; std::cin >> c;
    
    switch(c) {
      case 's': Shape::modifyAttributes(); break;
      case 'r': std::cout << "New radius>"; std::cin >> r; setRadius(r); break;
      case 'q': break;
      default: std::cout << "Error." << std::endl;
    }
  } while(c!='q');
}