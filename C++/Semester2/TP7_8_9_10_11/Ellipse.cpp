#include "Ellipse.hpp"
#include "Circle.hpp"

// Constructeur
Ellipse::Ellipse(EZColor col, uint x, uint y, uint w, uint h, uint thick, bool fill)
    : Shape(col, x, y, thick, fill), width(w), height(h) {}

// Chargement
Ellipse::Ellipse(istream& is) : Shape(is), width(0), height(0) {
    is >> width >> height;
}

// Constructeur à l'identique d'un Circle
Ellipse::Ellipse(const Circle& c)
    : Shape(c.getColor(), c.getAnchor().getX(), c.getAnchor().getY(), c.getThickness(), c.isFilled()),
      width(c.getRadius() * 2), height(c.getRadius() * 2) {}

Ellipse::~Ellipse() {}

void Ellipse::write(ostream& os) const {
    os << width << " " << height;
}

void Ellipse::draw(EZWindow& win) const {
    win.setColor(getColor());
    win.setThickness(getThickness());

    uint x1 = getAnchor().getX();
    uint y1 = getAnchor().getY();
    
    if (isFilled()) {
        win.fillEllipse(x1, y1, x1 + width, y1 + height);
    } else {
        win.drawEllipse(x1, y1, x1 + width, y1 + height);
    }
}

void Ellipse::modifyAttributes() {
  char c; uint w, h;
  do {
    std::cout << "Current attributes values are:" << std::endl
    << "s - sub-menu Shape" << std::endl
    << "w - width  = " << getWidth() << std::endl
    << "h - height = " << getHeight() << std::endl
    << "q - quit" << std::endl
    << "Choice?>"; std::cin >> c;
    
    switch(c) {
      case 's': Shape::modifyAttributes(); break;
      case 'w': std::cout << "New width>"; std::cin >> w; setWidth(w); break;
      case 'h': std::cout << "New height>"; std::cin >> h; setHeight(h); break;
      case 'q': break;
      default: std::cout << "Error." << std::endl;
    }
  } while(c!='q');
}