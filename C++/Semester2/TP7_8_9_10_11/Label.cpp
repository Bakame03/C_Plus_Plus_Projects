#include "Label.hpp"

// Constructeur
Label::Label(EZColor col, uint x, uint y, string txt, int font, uint thick)
    : Shape(col, x, y, thick, false), text(txt), fontNum(font) {}

// Chargement
Label::Label(istream& is) : Shape(is) {
    is >> text >> fontNum; // Lecture du texte et du numéro de police
}

Label::~Label() {}

void Label::write(ostream& os) const {
    os << text << " " << fontNum; // Sauvegarde des deux attributs
}

void Label::draw(EZWindow& win) const {
    win.setColor(getColor());
    win.setThickness(getThickness());
    win.drawText(getAnchor().getX(), getAnchor().getY(), text);
}

void Label::modifyAttributes() {
  char c; string t; int f;
  do {
    std::cout << "Current attributes values are:" << std::endl
    << "s - sub-menu Shape" << std::endl
    << "t - text = " << getText() << std::endl
    << "n - fontNum = " << getFontNum() << std::endl
    << "q - quit" << std::endl
    << "Choice?>"; std::cin >> c;
    
    switch(c) {
      case 's': Shape::modifyAttributes(); break;
      case 't': std::cout << "New text>"; std::cin >> t; setText(t); break;
      case 'n': std::cout << "New fontNum>"; std::cin >> f; setFontNum(f); break;
      case 'q': break;
      default: std::cout << "Error." << std::endl;
    }
  } while(c!='q');
}