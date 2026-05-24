// MyWindow.hpp

#ifndef MYWINDOW_HPP
#define MYWINDOW_HPP

#include <set>

#include "SetOfShapes.hpp"
#include "UI.hpp"

class MyWindow : public EZWindow {
  SetOfShapes shapes;
  std::vector<Shape*> selectedShapes;
  UI::ButtonSet<MyWindow> buttons;
  bool ctrlPressed;
  UI::Button<MyWindow> *isOverAButton(int mouse_x,int mouse_y) const;
 public:
  MyWindow(int w, int h,const char *name);
  ~MyWindow();
  void expose();
  void keyPress(EZKeySym keysym);
  void keyRelease(EZKeySym keysym);
  void buttonPress(int mouse_x,int mouse_y,int button);
  void motionNotify(int mouse_x,int mouse_y,int button);
  void buttonRelease(int mouse_x,int mouse_y,int button);

  class ColorButton : public UI::Button<MyWindow> {
  public:
    ColorButton(int _x,int _y,int _w,int _h,EZColor _color)
        : UI::Button<MyWindow>(_x,_y,_w,_h,"",_color) {}
    void pressAction(MyWindow& win) override
    {
      if(win.selectedShapes.size()==1)
          (*win.selectedShapes.begin())->setColor(getColor());
    }
  };
};


#endif
