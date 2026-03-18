// Buttons.hpp
// Patrons de classes pour créer des boutons afin d'avoir une IHM simpliste dans une fenêtre EZ-Draw++
#ifndef BUTTONS_TEMPLATE_HPP
#define BUTTONS_TEMPLATE_HPP

#include <vector>
#include <string>

#include "ez-draw++.hpp"

namespace UI {

template<typename WinT>
class Button {
protected:
    int x,y,w,h;
    EZColor bgColor;
    std::string text;
public:
    Button(int _x,int _y,int _w,int _h,std::string _text="",EZColor _bgColor=EZColor(240) ) : x(_x),y(_y),w(_w),h(_h),bgColor(_bgColor),text(_text) {}
    virtual ~Button() {}
    inline bool isOver(int mx,int my) { return (x<=mx && mx<=x+w && y<=my && my<=y+h); }
    inline const EZColor& getColor() const { return bgColor; }
    inline const std::string& getText() const { return text; }
    virtual void draw(WinT& win) const
    {
        win.setColor(bgColor);
        win.fillRectangle(x,y,x+w,y+h);
        win.setColor(EZColor::black);
        win.drawRectangle(x,y,x+w,y+h);
        win.drawText(EZAlign::MC,x+w/2,y+h/2,text);
    }
    virtual void pressAction(WinT&   /*win*/) {}
    virtual void motionAction(WinT&  /*win*/) {}
    virtual void releaseAction(WinT& /*win*/) {}
};

template<typename WinT>
class Label : public Button<WinT> {
public:
    inline Label(int _x,int _y,int _w,int _h,std::string _text)
        : Button<WinT>(_x,_y,_w,_h,_text)
    {}
    void draw(WinT& win) const override
    {
        win.setColor(EZColor::black);
        win.drawText(EZAlign::MC,this->x+this->w/2,this->y+this->h/2,this->text);
    }
};

template<typename WinT>
class LambdaButton : public Button<WinT> {
    void (*pressActionCallback) (WinT&);
    void (*motionActionCallback) (WinT&);
    void (*releaseActionCallback)(WinT&);
public:
    LambdaButton(int _x,int _y,int _w,int _h,std::string _text,
     void (*_pressActionCallback)  (WinT&)=nullptr,
     void (*_motionActionCallback) (WinT&)=nullptr,
     void (*_releaseActionCallback)(WinT&)=nullptr
    )
    : Button<WinT>(_x,_y,_w,_h,_text),
      pressActionCallback(_pressActionCallback),
      motionActionCallback(_motionActionCallback),
      releaseActionCallback(_releaseActionCallback)
    {}
    void pressAction(WinT& win)
    {
        if(pressActionCallback!=nullptr)
            pressActionCallback(win);
    }
    void motionAction(WinT& win)
    {
        if(motionActionCallback!=nullptr)
            motionActionCallback(win);
    }
    void releaseAction(WinT& win)
    {
        if(releaseActionCallback!=nullptr)
            releaseActionCallback(win);
    }
};

template<typename WinT>
class ButtonSet {
    std::vector<Button<WinT>*> buttons;
public:
    ButtonSet() {}
    ~ButtonSet() {  for(Button<WinT>* b:buttons) delete b; }
    Button<WinT>* isOverAButton(int mouse_x,int mouse_y) const
    {
        for(Button<WinT> *b:buttons)
            if(b->isOver(mouse_x,mouse_y))
                return b;
        return nullptr;
    }
    bool buttonPress(WinT& win,int mouse_x,int mouse_y,int button)
    {
        if(button!=1) return false;

        Button<WinT>* b = isOverAButton(mouse_x,mouse_y);
        if(b!=nullptr)
        {
            b->pressAction(win);
            return true;
        }
        else
            return false;
    }
    bool motionNotify(WinT& win,int mouse_x,int mouse_y,int button)
    {
        if(button!=1) return false;

        Button<WinT>* b = isOverAButton(mouse_x,mouse_y);
        if(b!=nullptr)
        {
            b->motionAction(win);
            return true;
        }
        else
            return false;
    }
    bool buttonRelease(WinT& win,int mouse_x,int mouse_y,int button)
    {
        if(button!=1) return nullptr;

        Button<WinT>* b = isOverAButton(mouse_x,mouse_y);
        if(b!=nullptr)
        {
            b->releaseAction(win);
            return true;
        }
        else
            return false;
    }
    inline void add(Button<WinT>* b) { buttons.push_back(b); }
    inline void draw(WinT& win) { for(Button<WinT>* b:buttons) b->draw(win); }
};

} // namespace UI

#endif