/* tracer.cpp : demonstration de EZ-Draw
 *
 * eric.remy@univ-provence.fr - 28/10/2008 - version 0.2
 *
 * Compilation sous Unix :
 *     g++ -Wall tracer.cpp ez-draw++.o -o tracer -L/usr/X11R6/lib -lX11 -lXext
 * Compilation sous Windows :
 *     g++ -Wall tracer.cpp ez-draw++.o -o tracer.exe -lgdi32
 *
 * This program is free software under the terms of the
 * GNU Lesser General Public License (LGPL) version 2.1.
*/

#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

#include "ez-draw++.hpp"
#include "Polynome.hpp" // Alex

class Traceur : public EZWindow {
 Polynome p;                 // Alex
 double xmin,xmax,ymin,ymax; // Les valeurs minimum et maximum de la fenetre de visibilite.
 unsigned short pixel_step;  // On tracera la fonction avec un point tous les pixel_step pixels.
 int curi,curj; // Les coordonnees du curseur d'exploration

 void trace_axes()
 {
  setColor(EZColor::black);
  int x0 = int ( (0.-xmin)/(xmax-xmin)*double(getWidth() -0) );
  int y0 = getHeight() - int ( (0.-ymin)/(ymax-ymin)*double(getHeight()-0) );
  if(y0 <= getHeight()-1) drawLine(0,y0,getWidth()-1,y0);  // Axe des X
  if(x0 <= getWidth() -1) drawLine(x0,0,x0,getHeight()-1); // Axe des Y
 }

 void trace_fonction()
 {
  setColor(EZColor::blue);
  int ipred,jpred; // Les coordonnees du point du tour de boucle precedant.
  for(int i=0;i<getWidth();i+=pixel_step)
   {
    double       x = double(i-0)*(xmax-xmin)/double(getWidth()-0)         + xmin; // On calcule le x reel correspondant a la colonne de pixel i.
    double       y = p(x); // Alex, appele de l'operator() de Polynome pour calculer f(x)

    int j;
    if     (y < ymin) j = getWidth(); // Si y est trop petit, on force j a la ligne du bas.
    else if(y > ymax) j = -1;         // Si y est trop grand, on force j a la ligne du haut.
    else              j = getHeight() - (unsigned int)( (y-ymin)*(getHeight()-0)/(ymax-ymin) - 0 );  // On calcule le j entier correspondant a la valeur de y.

    if(i==0) drawPoint(i,j);            // Si c'est le premier point, on met juste un point
    else     drawLine(ipred,jpred,i,j); // sinon on trace une ligne reliant le point precedant au point courant.
    ipred = i; jpred = j; // Memorisation de i et j pour le tour suivant.
   }
 }

 void trace_curseur()
 {
  setColor(EZColor::red);
  ostringstream oss;
  if(curi>=0 && curi<int(getWidth()) && curj>=0 && curj<int(getHeight()) ) // Si le curseur est dans la fenetre,
   {
    double x = double(       curi-0   )*(xmax-xmin)/double(getWidth()-0)  + xmin;
    double y = double(getHeight()-curj)*(ymax-ymin)/double(getHeight()-0) + ymin;
    const int cursor_size = 3;
    drawRectangle(curi-cursor_size,curj-cursor_size,curi+cursor_size,curj+cursor_size);
    oss << "x=" << x << " y=" << y;
   }
  else
   oss << "Cliquez pour mesurer une position.";
  drawText(EZAlign::BL,3,getHeight()-10,oss.str());
 }
public:
 Traceur(int w,int h,const char *name,const Polynome& _p,double _xmin,double _xmax,double _ymin,double _ymax,unsigned short _pixel_step) // Alex
  : EZWindow(w,h,name),
    p(_p),xmin(_xmin),xmax(_xmax),ymin(_ymin),ymax(_ymax),pixel_step(_pixel_step), // Alex
    curi(-1),curj(-1)
 { setDoubleBuffer(true); } // On active le double buffer pour limiter le scintillement de l'affichage.

 void expose()
 {
  trace_axes();
  trace_curseur();
  trace_fonction();
 }

 void keyPress(EZKeySym keysym) // Une touche du clavier a ete enfoncee ou relachee
  {
   double xstep = (xmax-xmin)/10.;
   double ystep = (ymax-ymin)/10.;
    switch (keysym)
     {
        case EZKeySym::Escape:
        case EZKeySym::q :
          EZDraw::quit();
          break;
        case EZKeySym::Left:  xmin -= xstep; xmax-=xstep; sendExpose(); break;
        case EZKeySym::Right: xmin += xstep; xmax+=xstep; sendExpose(); break;
        case EZKeySym::Down:  ymin -= ystep; ymax-=ystep; sendExpose(); break;
        case EZKeySym::Up:    ymin += ystep; ymax+=ystep; sendExpose(); break;
        case EZKeySym::minus:
        case EZKeySym::KP_Subtract:
          xmin -= xstep; xmax+=xstep;
          ymin -= ystep; ymax+=ystep;
          sendExpose();
          break;
        case EZKeySym::plus:
        case EZKeySym::KP_Add:
          xmin += xstep; xmax-=xstep;
          ymin += ystep; ymax-=ystep;
          sendExpose();
          break;
        default: // Dans tous les autres cas on ne fait rien (nécessaire
          break; // pour éviter un warning à la compilation).
     }
  }

 void buttonPress(int i,int j,int /*button*/)
  { curi = i;  curj = j;  sendExpose(); }
 void motionNotify(int i,int j,int button)
  {
   if(button == 1) // Si le bouton gauche est enfonce seulement,
    { curi = i;  curj = j; sendExpose(); } // on met a jour l'affichage.
  }
 void buttonRelease(int /*i*/,int /*j*/,int /*button*/)
  { curi = -1; curj = -1; sendExpose(); }
};

//= La classe MyApplication dérivée de EZDraw =================================
class MyApplication : public EZDraw {
  Traceur wpoly1; // Alex
 public:
  MyApplication()
   : wpoly1(640,480,"Polynome 1 : y=-x^3+4x^2-5x+2", Polynome(3, new double[4]{2, -5, 4, -1}), -1. ,+3. , -0.3,+0.5, 3) // Alex
  {}
};

//= Main ======================================================================
int main (int /*argc*/, char */*argv*/[])
{
 cout << "Traceur de fonctions - E. Remy - 04/2010" << endl
      << "Vous pouvez vous deplacer avec les fleches et zoomer/dezoomer avec + et -." << endl
      << "Vous pouvez egalement cliquer dans la fenetre pour observer les coordonnees."
      << endl;

 MyApplication myapp;

 myapp.mainLoop();
 return 0;
}

