#include "Label.hpp"

// Constructeur
Label::Label(EZColor col, uint x, uint y, int font, string txt, uint thick)
    : Shape(col, x, y, thick, false), msg(txt), fontNum(font) {}

// Chargement
Label::Label(istream& is) : Shape(is) {
    is >> fontNum >> msg; // Lecture du numéro de police et du message
}

Label::~Label() {}

void Label::write(ostream& os) const {
    os << fontNum << " " << msg; // Sauvegarde des deux attributs
}

void Label::draw(EZWindow& win) const {
    win.setColor(getColor());
    win.setThickness(getThickness());
    win.setFont(fontNum);
    win.drawText(EZAlign::TL, getAnchor().getX(), getAnchor().getY(), msg);
}

void Label::modifyAttributes() {
  char c; string m; int f;
  do {
    std::cout << "Current attributes values are:" << std::endl
    << "s - sub-menu Shape" << std::endl
    << "m - message = " << getMessage() << std::endl
    << "n - fontNum = " << getFontNum() << std::endl
    << "q - quit" << std::endl
    << "Choice?>"; std::cin >> c;
    
    switch(c) {
      case 's': Shape::modifyAttributes(); break;
      case 'm': std::cout << "New message>"; std::cin >> m; setMessage(m); break;
      case 'n': std::cout << "New fontNum>"; std::cin >> f; setFontNum(f); break;
      case 'q': break;
      default: std::cout << "Error." << std::endl;
    }
  } while(c!='q');
}