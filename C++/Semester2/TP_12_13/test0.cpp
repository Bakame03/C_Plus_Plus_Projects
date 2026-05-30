#include <iostream>
#include <string>    // Ajout important
#include "List.hpp"  // On inclut le nouveau fichier

using namespace std;

void premiere_partie(List<string>& liste)
{
    liste.push_front("Avion");
    liste.push_back("Bateau");
    liste.push_back("Camion");
    const string& f = liste.front(); 
    cout << "Tête  : " << f << endl;
    const string& b = liste.back();
    cout << "Queue : " << b << endl;
    cout << "Liste : " << liste << " (" << liste.size() << " éléments)" << endl;
}

void deuxieme_partie(List<string> liste)
{
    liste.pop_front();
    liste.pop_back();
    cout << "Tête  : " << liste.front() << endl;
    cout << "Queue : " << liste.back() << endl;
    cout << "Liste : " << liste << endl;
    liste.clear();
    cout << "Liste : " << liste << endl;
}

void troisieme_partie(List<string>& liste, List<string>& liste2)
{
    liste.splice(liste2);
    cout << "Liste  : " << liste << endl;
    cout << "Liste2 : " << liste2 << endl;
    liste.reverse();
    cout << "Liste  : " << liste << endl;
}

void quatrieme_partie(List<string>& liste)
{
    const List<string>& cliste(liste);
    cout << "Tête  : " << cliste.front() << endl;
    cout << "Queue : " << cliste.back() << endl;
    cout << "Liste : " << cliste << endl;

    string values[]={"Un","Deux","Trois","Quatre","Cinq","Six","Sept","Huit","Neuf","Dix"};

    List<string> liste2;
    for(const string& v : values)
        liste2.insert_sorted(v);
    cout << "Liste2 : " << liste2 << endl;

    List<string> liste3;
    for(const string& v : values)
        liste3.push_back(v);
    liste3.sort();
    cout << "Liste3 : " << liste3 << endl;
}

int main()
{
    List<string> liste;
    premiere_partie(liste);

    deuxieme_partie(liste);

    List<string> liste2;
    liste2.push_back("Deltaplane");
    liste2.push_back("Engin de chantier");
    liste2.push_back("Fusée");
    troisieme_partie(liste, liste2);

    quatrieme_partie(liste);

    return EXIT_SUCCESS;
}