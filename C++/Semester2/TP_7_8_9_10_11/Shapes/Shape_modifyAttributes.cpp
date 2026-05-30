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
    << "or type any other color using the HTML RGB two digits hexadecimal notation ('#RRGGBB')"
    << "Choice ?>"; std::cin >> color;
    return color;
}

void Shape::modifyAttributes()
{
  char c; int x,y;
  do
  {
    std::cout << "Current attributes values are:" << std::endl
    << "c - color     = " << getColor() << std::endl
    << "a - anchor    = " << getAnchor() << std::endl
    << "f - filled    = " << (isFilled()?"true":"false") << std::endl
    << "t - thickness = " << getThickness() << std::endl
    << "q - quit or go back one level" << std::endl
    << "To modify an attribute, enter the designated letter." << std::endl
    << "Choice?>"; std::cin >> c;
    switch(c)
    {
      case 'c': setColor(ask_color()); break;
      case 'a': std::cout << "Give the new x and y values separated by a space>"; std::cin >> x >> y; setAnchor(x,y); break;
      case 'f':
      {
        char res;
        std::cout << "Should the shape be filled (y/n)?>"; std::cin >> res; setFilled(res=='y');
      }
      break;
      case 't': std::cout << "Give the new thickness value>"; std::cin >> x; setThickness(x); break;
      case 'q': break;
      default:
        std::cout << "Error this choice does not exist. Try again." << std::endl;
    }
  } while(c!='q');
} 
