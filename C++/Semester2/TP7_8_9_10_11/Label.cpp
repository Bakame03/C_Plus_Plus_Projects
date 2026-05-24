#include "Label.hpp"

// Constructeur
Label::Label(EZColor col, uint x, uint y, int font, string txt, uint thick)
    : Shape(col, x, y, thick, false), msg(txt), fontNum(font) {}

// Chargement
Label::Label(istream& is) : Shape(is) {
    is >> fontNum;
    char quote;
    is >> ws >> quote; // Read the first quote
    if (quote == '"') {
        getline(is, msg, '"'); // Read until the next quote
    } else {
        is.putback(quote);
        is >> msg;
    }
}

Label::~Label() {}

void Label::write(ostream& os) const {
    os << fontNum << " \"" << msg << "\""; // Sauvegarde avec guillemets pour supporter les espaces
}

void Label::draw(EZWindow& win) const {
    win.setColor(getColor());
    win.setThick(getThickness());
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
      case 'm': 
        std::cout << "New message>"; 
        std::cin.ignore(256, '\n');
        std::getline(std::cin, m); 
        setMessage(m); 
        break;
      case 'n': std::cout << "New fontNum>"; std::cin >> f; setFontNum(f); break;
      case 'q': break;
      default: std::cout << "Error." << std::endl;
    }
  } while(c!='q');
}