#include "Ellipse.hpp"
#include "Circle.hpp"

// Constructeur
Ellipse::Ellipse(EZColor col, uint x, uint y, uint w, uint h, uint thick, bool fill)
    : Shape(col, x, y, thick, fill), semiWidth(w), semiHeight(h) {}

// Chargement
Ellipse::Ellipse(istream& is) : Shape(is), semiWidth(0), semiHeight(0) {
    is >> semiWidth >> semiHeight;
}

// Constructeur à l'identique d'un Circle
Ellipse::Ellipse(const Circle& c)
    : Shape(c.getColor(), c.getAnchor().getX(), c.getAnchor().getY(), c.getThickness(), c.isFilled()),
      semiWidth(c.getRadius() * 2), semiHeight(c.getRadius() * 2) {}

Ellipse::~Ellipse() {}

void Ellipse::write(ostream& os) const {
    os << semiWidth << " " << semiHeight;
}

void Ellipse::draw(EZWindow& win) const {
    win.setColor(getColor());
    win.setThickness(getThickness());

    uint x1 = getAnchor().getX();
    uint y1 = getAnchor().getY();
    
    if (isFilled()) {
        win.fillEllipse(x1, y1, x1 + semiWidth, y1 + semiHeight);
    } else {
        win.drawEllipse(x1, y1, x1 + semiWidth, y1 + semiHeight);
    }
}

void Ellipse::modifyAttributes() {
  char c; uint w, h;
  do {
    std::cout << "Current attributes values are:" << std::endl
    << "s - sub-menu Shape" << std::endl
    << "w - semiWidth  = " << getSemiWidth() << std::endl
    << "h - semiHeight = " << getSemiHeight() << std::endl
    << "q - quit" << std::endl
    << "Choice?>"; std::cin >> c;
    
    switch(c) {
      case 's': Shape::modifyAttributes(); break;
      case 'w': std::cout << "New semiWidth>"; std::cin >> w; setSemiWidth(w); break;
      case 'h': std::cout << "New semiHeight>"; std::cin >> h; setSemiHeight(h); break;
      case 'q': break;
      default: std::cout << "Error." << std::endl;
    }
  } while(c!='q');
}