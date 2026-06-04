// MyWindow.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

#include "ez-draw++.hpp"

#include "MyWindow.hpp"

#include "SetOfShapes.hpp"

#include "Point.hpp"
#include "Ellipse.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"
#include "Square.hpp"
#include "Label.hpp"
#include "Enveloppe.hpp"

MyWindow::MyWindow(int w, int h,const char *name)
 : EZWindow(w,h,name),shapes(200),ctrlPressed(false)
{
  setDoubleBuffer(true);

  buttons.add(new UI::LambdaButton<MyWindow>(220,1,70,15,"rectangle",[](MyWindow& win){ win.shapes.add(new Rectangle(EZColor::black,win.getWidth()/2-25,win.getHeight()/2-25,100,50)); }));
  buttons.add(new UI::LambdaButton<MyWindow>(300,1,70,15,"ellipse",  [](MyWindow& win){ win.shapes.add(new Ellipse(  EZColor::black,win.getWidth()/2-25,win.getHeight()/2-25, 50,25)); }));
  buttons.add(new UI::LambdaButton<MyWindow>(380,1,70,15,"square",   [](MyWindow& win){ win.shapes.add(new Square(   EZColor::black,win.getWidth()/2-25,win.getHeight()/2-25, 50)); }));
  buttons.add(new UI::LambdaButton<MyWindow>(460,1,70,15,"circle",   [](MyWindow& win){ win.shapes.add(new Circle(   EZColor::black,win.getWidth()/2-25,win.getHeight()/2-25, 25)); }));
  buttons.add(new UI::LambdaButton<MyWindow>(540,1,70,15,"label",    [](MyWindow& win){ win.shapes.add(new Label(    EZColor::black,win.getWidth()/2-25,win.getHeight()/2-25,0,"Change this text!")); }));

  buttons.add(new MyWindow::ColorButton( 5,25,10,10,EZColor::black));
  buttons.add(new MyWindow::ColorButton(15,25,10,10,EZColor::grey));
  buttons.add(new MyWindow::ColorButton(25,25,10,10,EZColor::white));

  buttons.add(new MyWindow::ColorButton( 5,35,10,10,EZColor::red));
  buttons.add(new MyWindow::ColorButton(15,35,10,10,EZColor::green));
  buttons.add(new MyWindow::ColorButton(25,35,10,10,EZColor::blue));

  buttons.add(new MyWindow::ColorButton( 5,45,10,10,EZColor::cyan));
  buttons.add(new MyWindow::ColorButton(15,45,10,10,EZColor::magenta));
  buttons.add(new MyWindow::ColorButton(25,45,10,10,EZColor::yellow));

  const int y_attr = 18;
  const int x_filled = 40;
  buttons.add(new UI::Label<MyWindow>(x_filled,y_attr,60,20,"Filled"));
  buttons.add(new UI::LambdaButton<MyWindow>(x_filled+10,y_attr+20,20,20,"n",
    [](MyWindow& win){ if(win.selectedShapes.size()==1) (*win.selectedShapes.begin())->setFilled(false); } ));
  buttons.add(new UI::LambdaButton<MyWindow>(x_filled+30,y_attr+20,20,20,"y",
    [](MyWindow& win){ if(win.selectedShapes.size()==1) (*win.selectedShapes.begin())->setFilled(true); } ));

  const int x_thickness = 100;
  buttons.add(new UI::Label<MyWindow>(x_thickness,y_attr,60,20,"Thickness"));
  buttons.add(new UI::LambdaButton<MyWindow>(x_thickness+10,y_attr+20,20,20,"-",
    [](MyWindow& win){
      if(win.selectedShapes.size()==1 && (*win.selectedShapes.begin())->getThickness()>1)
        (*win.selectedShapes.begin())->setThickness((*win.selectedShapes.begin())->getThickness()-1);
    } ));
  buttons.add(new UI::LambdaButton<MyWindow>(x_thickness+30,y_attr+20,20,20,"+",
    [](MyWindow& win){
      if(win.selectedShapes.size()==1)
        (*win.selectedShapes.begin())->setThickness((*win.selectedShapes.begin())->getThickness()+1);
    } ));

#if 1 // Activez cette partie après avoir fait la classe Label
  const int x_font = 160;
  buttons.add(new UI::Label<MyWindow>(x_font,y_attr,60,20,"FontNum"));
  buttons.add(new UI::LambdaButton<MyWindow>(x_font+10,y_attr+20,20,20,"-",
    [](MyWindow& win){
      if(win.selectedShapes.size()==1)
      {
        Label* s=dynamic_cast<Label*>(*win.selectedShapes.begin());
        if(s!=nullptr)
          s->setFontNum(s->getFontNum()-1);
      }
     } ));
  buttons.add(new UI::LambdaButton<MyWindow>(x_font+30,y_attr+20,20,20,"+",
    [](MyWindow& win)
    {
      if(win.selectedShapes.size()==1)
      {
        Label* s=dynamic_cast<Label*>(*win.selectedShapes.begin());
        if(s!=nullptr)
          s->setFontNum(s->getFontNum()+1);
      }
    } ));
  buttons.add(new UI::LambdaButton<MyWindow>(620,1,70,15,"envelope",[](MyWindow& win){ win.shapes.add(new Enveloppe(EZColor::black,win.getWidth()/2-50,win.getHeight()/2-25,100,false)); }));
#endif

}

MyWindow::~MyWindow()
{}

void MyWindow::expose()
{
  shapes.draw(*this);
  for(Shape* shape : selectedShapes)
    shape->getAnchor().draw(*this,true);
  setColor(EZColor::black);
  setThick(1);
  setFont(0);
  drawText(EZAlign::TL,3,3,"h : print help on the console");
  buttons.draw(*this);
  if(selectedShapes.size()>0)
  {
    ostringstream oss;
    oss << *(*selectedShapes.begin());
    if(selectedShapes.size()>1)
      oss << std::endl << " + " << selectedShapes.size()-1 << " other shape" << (selectedShapes.size()>2?"s":"");
    drawText(EZAlign::BL,3,getHeight()-3,oss.str());
  }
}

void MyWindow::buttonPress(int mouse_x,int mouse_y,int button)
{
  if(button==1)
  {
    if(!buttons.buttonPress(*this,mouse_x,mouse_y,button))
    {
      if(!ctrlPressed && selectedShapes.size()!=0)
      {
        selectedShapes.clear();
      }
      Shape *s = shapes.isOver(mouse_x,mouse_y);
      if(s!=nullptr)
      {
        std::vector<Shape*>::iterator it = std::find(selectedShapes.begin(),selectedShapes.end(),s);
        if(it==selectedShapes.end()) // Si la forme n'est pas déjà sélectionnée
        {
          selectedShapes.push_back(s); // selectedShapes.push_back(s); // On l'ajoute aux sélectionnées
        }
        else // sinon, c'est-à-dire si elle est déjà sélectionnée
        {
          selectedShapes.erase(it);   // On la retire des sélectionnées
        }
      }
    }
    sendExpose();
  }
}

// Déplacement de la souris :
void MyWindow::motionNotify(int mouse_x,int mouse_y,int button)
{
  if(!buttons.motionNotify(*this,mouse_x,mouse_y,button) && button == 1 && !ctrlPressed && selectedShapes.size()==1) // Si on clique sur l'anchor d'une shape
    (*(selectedShapes.begin()))->setAnchor(mouse_x,mouse_y); // on la bouge.
  sendExpose();
}

void MyWindow::buttonRelease(int mouse_x,int mouse_y,int button)
{
  if(!buttons.motionNotify(*this,mouse_x,mouse_y,button) && button == 1 && !ctrlPressed && selectedShapes.size()==1) // Si on clique sur l'anchor d'une shape
    (*selectedShapes.begin())->setAnchor(mouse_x,mouse_y);
  sendExpose();
}

void MyWindow::keyPress(EZKeySym keysym) // Une touche du clavier a ete enfoncée ou relâchée
{
  switch (keysym)
    {
     case EZKeySym::Escape:
     case EZKeySym::q :       EZDraw::quit (); break;
     case EZKeySym::p:
      cout << shapes;
      break;
     case EZKeySym::S:
      {
       ofstream f("shapes.txt");
       shapes.save(f);
      }
      break;
     case EZKeySym::L:
      try {
       ifstream f("shapes.txt");
       shapes.load(f);
      }
      catch(exception& e)
      {
        cout << "Exception:" << e.what() << endl;
      }
      break;
     case EZKeySym::m:  if(selectedShapes.size()==1) (*selectedShapes.begin())->modifyAttributes(); break;
     case EZKeySym::_0: if(selectedShapes.size()==1) (*selectedShapes.begin())->setColor(EZColor::black);   break;
     case EZKeySym::_1: if(selectedShapes.size()==1) (*selectedShapes.begin())->setColor(EZColor::grey);    break;
     case EZKeySym::_2: if(selectedShapes.size()==1) (*selectedShapes.begin())->setColor(EZColor::red);     break;
     case EZKeySym::_3: if(selectedShapes.size()==1) (*selectedShapes.begin())->setColor(EZColor::green);   break;
     case EZKeySym::_4: if(selectedShapes.size()==1) (*selectedShapes.begin())->setColor(EZColor::blue);    break;
     case EZKeySym::_5: if(selectedShapes.size()==1) (*selectedShapes.begin())->setColor(EZColor::yellow);  break;
     case EZKeySym::_6: if(selectedShapes.size()==1) (*selectedShapes.begin())->setColor(EZColor::cyan);    break;
     case EZKeySym::_7: if(selectedShapes.size()==1) (*selectedShapes.begin())->setColor(EZColor::magenta); break;
     case EZKeySym::h:
      cout << "q : quit" << endl
           << "h : this help" << endl
           << "p : print the list of shapes on the console" << endl
           << "S : saves all the shapes in \"shapes.txt\"" << endl
           << "L : loads shapes from \"shapes.txt\"" << endl
           << "m : modify the attributes of the (single) selected shape" << endl
           /*
           << "+ : increase thickness"    << endl
           << "- : decrease thickness"    << endl
           */
           << "0 : set the color of the selected shape to black"   << endl
           << "1 : set the color of the selected shape to gray"    << endl
           << "2 : set the color of the selected shape to red"     << endl
           << "3 : set the color of the selected shape to green"   << endl
           << "4 : set the color of the selected shape to blue"    << endl
           << "5 : set the color of the selected shape to yellow"  << endl
           << "6 : set the color of the selected shape to cyan"    << endl
           << "7 : set the color of the selected shape to magenta" << endl
           << "r : create a rectangle" << endl
           << "e : create a ellipse" << endl
           << "s : create a square" << endl
           << "c : create a circle" << endl
           << "l : create a label" << endl
           ;
      break;
     case EZKeySym::plus:     cout << "plus" << endl; break;
     case EZKeySym::minus:    cout << "minus" << endl; break;
     case EZKeySym::asterisk: cout << "asterisk" << endl; break;
     case EZKeySym::slash:    cout << "slash" << endl; break;
     case EZKeySym::r: shapes.add(new Rectangle(EZColor::black,getWidth()/2-25,getHeight()/2-25,100,50)); break;
     case EZKeySym::e: shapes.add(new Ellipse  (EZColor::black,getWidth()/2-25,getHeight()/2-15,50,30)); break;
     case EZKeySym::s: shapes.add(new Square   (EZColor::black,getWidth()/2-25,getHeight()/2-25,50)); break;
     case EZKeySym::c: shapes.add(new Circle   (EZColor::black,getWidth()/2-25,getHeight()/2-25,25)); break;
     case EZKeySym::l:
     {
      string str;
      cout << "Message?>"; getline(cin,str);
      shapes.add(new Label(EZColor::black,getWidth()/2-25,getHeight()/2-25,0,str));
     }
     break;
//     case EZKeySym::t: shapes.add(new Triangle(EZColor::black,getWidth()/2,getHeight()/2-50,getWidth()/2-25,getHeight()/2-30,getWidth()/2+25,getHeight()/2-30)); break;
     case EZKeySym::Control_L:
       ctrlPressed = true;
       break;
     case EZKeySym::v: shapes.add(new Enveloppe(EZColor::black,getWidth()/2-50,getHeight()/2-25,100,false)); break;
     default:
      break;
    }
 sendExpose();
}

void MyWindow::keyRelease(EZKeySym keysym) // Une touche du clavier a ete enfoncée ou relâchée
{
  switch (keysym)
    {
     case EZKeySym::Control_L:
       ctrlPressed = false;
       break;
     default:
      break;
    }
 sendExpose();
}
