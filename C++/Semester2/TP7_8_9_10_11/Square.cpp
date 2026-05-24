#include "Square.hpp"

// On appelle le constructeur de Rectangle avec width=size et height=size
Square::Square(EZColor col, uint x, uint y, uint size, uint thick, bool fill)
    : Rectangle(col, x, y, size, size, thick, fill) {}

// Constructeur depuis flux : on utilise le constructeur de Rectangle
Square::Square(istream& is) : Rectangle(is) {}

Square::~Square() {}

void Square::setSize(uint s) {
    setWidth(s);
    setHeight(s);
}

void Square::modifyAttributes() {
  char c; uint s;
  do {
    std::cout << "Current attributes values are:" << std::endl
    << "s - sub-menu Shape" << std::endl
    << "z - size = " << getSize() << std::endl
    << "q - quit" << std::endl
    << "Choice?>"; std::cin >> c;
    
    switch(c) {
      case 's': Shape::modifyAttributes(); break;
      case 'z': std::cout << "New size>"; std::cin >> s; setSize(s); break;
      case 'q': break;
      default: std::cout << "Error." << std::endl;
    }
  } while(c!='q');
}