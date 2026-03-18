/* demo++04.cpp : demonstration de EZ-Draw
 *
 * eric.remy@univ-amu.fr - 28/10/2008 - version 0.1
 *
 * Compilation sous Unix :
 *     g++ -Wall demo++04.cpp ez-draw++.o -o demo++04 -L/usr/X11R6/lib -lX11 -lXext
 * Compilation sous Windows :
 *     g++ -Wall demo++04.cpp ez-draw++.o -o demo++04 -lgdi32
 *
 * This program is free software under the terms of the
 * GNU Lesser General Public License (LGPL) version 2.1.
*/

#include <sstream>

using namespace std;

#include "ez-draw++.hpp"

class MyWindow : public EZWindow
{
public:
 MyWindow(int w,int h,const char *name)
  : EZWindow(w,h,name)
 {}

 void expose()
  {
    setColor (EZColor::black);
    for(int i = 0; i <= 3; i++)
     {
      setFont(i); // Choix d'une des 4 polices de caractères différente a chaque tour de boucle.
      ostringstream oss; // On crée un std::ostringstream.
      oss << "Fonte numero " << i ; // On écrit dedans.
      drawText(
        EZAlign::TC, // Texte aligne en haut et centre horizontalement.
        getWidth()/2, getHeight()/2 + 25 * (i-2), // Position de l'écriture.
        oss.str() // On récupère le contenu de oss sous forme d'une std::string qu'on
      );          // transmet a drawText().
     }

    setFont(0); // Choix de la police de caractères par défaut (0).
    setColor(EZColor::red);
    drawText(EZAlign::TL,            2,             1, "Top\nLeft");
    drawText(EZAlign::TC, getWidth()/2,             1, "Top\nCenter");
    drawText(EZAlign::TR, getWidth()-2,             1, "Top\nRight");
    drawText(EZAlign::ML,            2, getHeight()/2, "Middle\nLeft");
    drawText(EZAlign::MR, getWidth()-2, getHeight()/2, "Middle\nRight");
    drawText(EZAlign::BL,            2, getHeight()-2, "Bottom\nLeft");
    drawText(EZAlign::BC, getWidth()/2, getHeight()-2, "Bottom\nCenter");
    drawText(EZAlign::BR, getWidth()-2, getHeight()-2, "Bottom\nRight");
    // Les fonctions membres getWidth() et getHeight() permettent d'obtenir la largeur
    // et hauteur actuelle de la fenêtre courante.
  }

 void keyPress(EZKeySym keysym)
  {
    switch (keysym)
     {
        case EZKeySym::Escape:
        case EZKeySym::q  :
          EZDraw::quit();
          break;
        default: // Dans tous les autres cas on ne fait rien (nécessaire
          break; // pour éviter un warning a la compilation).
     }
  }
};


int main (int /*argc*/, char */*argv*/[])
{
 EZDraw ezDraw;

 MyWindow win1(400, 300, "Demo++04 : affichage de texte");

 ezDraw.mainLoop();

 return 0;
}
