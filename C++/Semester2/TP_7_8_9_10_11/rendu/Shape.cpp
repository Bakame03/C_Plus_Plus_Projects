#include "Shape.hpp"
#include "Rectangle.hpp"
#include "Square.hpp"
#include "Ellipse.hpp"
#include "Circle.hpp"
#include "Label.hpp"

// Constructeur principal
Shape::Shape(EZColor col, uint x, uint y, uint thick, bool fill)
    : color(col), anchor(x, y), filled(fill), thickness(thick) {}


Shape::Shape(istream& is) : anchor(0, 0) {
    uint ax, ay;
    is >> color >> ax >> ay >> filled >> thickness;
    anchor.setXY(ax, ay);
}

// Destructeur virtuel
Shape::~Shape() {}

// Implémentation : on délègue la vérification à l'ancre (Point)
bool Shape::isOver(uint mouseX, uint mouseY) const {
    return anchor.isOver(mouseX, mouseY);
}


EZColor ask_color() 
{
  EZColor color;
  std::cout << "Please use the following values:" << std::endl
    << EZColor::black   << " for black" << std::endl
    << EZColor::white   << " for white" << std::endl
    << EZColor::grey    << " for grey" << std::endl
    << EZColor::red     << " for red" << std::endl
    << EZColor::green   << " for green" << std::endl
    << EZColor::blue    << " for blue" << std::endl
    << EZColor::yellow  << " for yellow" << std::endl
    << EZColor::cyan    << " for cyan" << std::endl
    << EZColor::magenta << " for magenta" << std::endl
    << "or type any other color using the HTML RGB two digits hexadecimal notation ('#RRGGBB')" << std::endl
    << "Choice ?>"; std::cin >> color;
    return color;
}

// Menu interactif pour modifier les attributs
void Shape::modifyAttributes()
{
  char c; uint x, y;
  do
  {
    std::cout << "Current attributes values are:" << std::endl
    << "c - color     = " << getColor() << std::endl
    << "a - anchor    = " << getAnchor() << std::endl
    << "f - filled    = " << (isFilled()?"true":"false") << std::endl
    << "t - thickness = " << getThickness() << std::endl
    << "q - quit or go back one level" << std::endl
    << "Choice?>"; std::cin >> c;
    
    switch(c)
    {
      case 'c': setColor(ask_color()); break;
      case 'a': std::cout << "New x y>"; std::cin >> x >> y; setAnchor(x,y); break;
      case 'f':
      {
        char res;
        std::cout << "Filled (y/n)?>"; std::cin >> res;
        setFilled(res == 'y' || res == 'Y');
        break;
      }
      case 't': 
      {
          uint t; 
          std::cout << "New thickness>"; std::cin >> t; 
          setThickness(t); 
          break;
      }
      case 'q': break;
      default:
        std::cout << "Error." << std::endl;
    }
  } while(c!='q');
}

// Opérateur d'affichage global
ostream& operator<<(ostream& os, const Shape& s) {
    os << s.getTypeName() << " " << s.getColor() << " "
       << s.getAnchor() << " "
       << s.isFilled() << " " << s.getThickness() << " ";
    s.write(os); 
    return os;
}

Shape* Shape::load(istream& is) {
    string type;
    is >> type;
    if (type == "Rectangle") return new Rectangle(is);
    if (type == "Ellipse")   return new Ellipse(is);
    if (type == "Label")     return new Label(is);
    if (type == "Square")    return new Square(is);
    if (type == "Circle")    return new Circle(is);

    return nullptr;
}