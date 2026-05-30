#include <iostream>

#include "ListOfStrings.hpp"

using namespace std;

void premiere_partie(ListOfStrings& liste)
{
    liste.push_front("Avion");
    liste.push_back("Bateau");
    liste.push_back("Camion");
    const string& f = liste.front(); // Référence constante à la chaîne du premier maillon
    cout << "Tête  : " << f << endl;
    const string& b = liste.back();
    cout << "Queue : " << b << endl;
    cout << "Liste : " << liste << " (" << liste.size() << " éléments)" << endl;
}

// Cette fois, la liste est passée par valeur, ce qui déclenche une copie.
void deuxieme_partie(ListOfStrings liste)
{
    liste.pop_front();
    liste.pop_back();
    cout << "Tête  : " << liste.front() << endl;
    cout << "Queue : " << liste.back() << endl;
    cout << "Liste : " << liste << endl;
    liste.clear();
    cout << "Liste : " << liste << endl;
}

void troisieme_partie(ListOfStrings& liste,ListOfStrings& liste2)
{
    liste.splice(liste2);
    cout << "Liste  : " << liste << endl;
    cout << "Liste2 : " << liste2 << endl;
    liste.reverse();
    cout << "Liste  : " << liste << endl;
}

void quatrieme_partie(ListOfStrings& liste)
{
    const ListOfStrings& cliste(liste);
    cout << "Tête  : " << cliste.front() << endl;
    cout << "Queue : " << cliste.back() << endl;
    cout << "Liste : " << cliste << endl;

    string values[]={"Un","Deux","Trois","Quatre","Cinq","Six","Sept","Huit","Neuf","Dix"};

    ListOfStrings liste2;
    for(const string& v : values)
        liste2.insert_sorted(v);
    cout << "Liste2 : " << liste2 << endl;

    ListOfStrings liste3;
    for(const string& v : values)
        liste3.push_back(v);
    liste3.sort();
    cout << "Liste3 : " << liste3 << endl;
}

int main()
{
    // ListOfStrings::StringNode sn("Hello"); // Impossible si la inner-class est déclarée en private: dans ListOfStrings

    // Partie minimale devant être réalisée par tout le monde.
    ListOfStrings liste;
    premiere_partie(liste);

    // Deuxième partie, devrait être faite par tous les étudiants qui veulent avoir la moyenne.
    deuxieme_partie(liste);

    // Troisième partie, ça devient un peu plus délicat.
    ListOfStrings liste2;
    liste2.push_back("Deltaplane");
    liste2.push_back("Engin de chantier");
    liste2.push_back("Fusée");
    troisieme_partie(liste,liste2);

    // Quatrième partie, pour ceux qui visent les meilleures notes.
    quatrieme_partie(liste);

    return EXIT_SUCCESS;
}
