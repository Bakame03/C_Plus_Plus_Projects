void Rectangle::modifyAttributes() 
{
  char c; int w,h;
  do
  {
    std::cout << "Current attributes values are:" << std::endl
    << "s : go to the sub-menu for the attributes of the Shape " << std::endl
    << "w - width  = " << getWidth() << std::endl
    << "h - height = " << getHeight() << std::endl
    << "q - quit or go back one level" << std::endl
    << "To modify an attribute, enter the designated letter." << std::endl
    << "Choice?>"; std::cin >> c;
    switch(c)
    {
      case 's': Shape::modifyAttributes(); break;
      case 'w': std::cout << "Give the new width value>"; std::cin >> w; setWidth(w); break;
      case 'h': std::cout << "Give the new height value>"; std::cin >> h; setHeight(h); break;
      case 'q': break;
      default:
        std::cout << "Error this choice does not exist. Try again." << std::endl;
    }
  } while(c!='q');
} 
