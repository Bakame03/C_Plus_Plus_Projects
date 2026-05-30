#include <iostream>
#include "./exo1/Polynome.hpp"

using namespace std;

int main() {
    const double coef_p1[] = {3, -1.414, 3, 6, 0, 1};
    Polynome p1(5, coef_p1); // p1(x) = x^5 + 6x^3 + 3x^2 - sqrt(2)x + 3
    cout << "p1(x)= " << p1 << " et son degré est " << p1.getDegre() << "." << endl;

    const double coef_p2[] = {4, -2, 3, 1, -2, -1};
    Polynome p2(5, coef_p2); // p2(x) = -x^5 - 2x^4 + x^3 + 3x^2 - 2x + 4
    cout << "p2(x)= " << p2 << " et son degré est " << p2.getDegre() << "." << endl;

    cout << "Construction de p3 comme copie de p2." << endl;
    Polynome p3(p2);
    if (p3 == p2)
        cout << "p3 est égal à p2... Ce qui est rassurant pour une copie !" << endl;

    cout << "Affectation de p1 à p3." << endl;
    p3 = p1; // On affecte sans construire puisque p1 existe déjà.

    cout << "On affecte le coefficient du monôme de degré 1 de p3 à la constante de p3." << endl;
    p3[0] = p3[1]; // On affecte le coefficient du monôme de degré 1 au monôme de degré 0...
    cout << "p3 est maintenant égal à p3(x)= " << p3 << endl;
    if (p2 == p3)
        cout << "p2 est égal à p3... ce qui ne devrait pas arriver !" << endl;
    else
        cout << "p2 est maintenant différent de p3 !" << endl;

    cout << "(p1+p2)(x)= " << p1 + p2 << endl;

    // Polynome p4 ; // Vous devez rendre cette instruction impossible.

    cout << "Sachant que p1(x)= " << p1 
        << ", on peut calculer ses valeurs en fonction de x : " << endl;
    for (double x = -2; x <= 2; x += 1)
        cout << "Pour p1(" << x << ")= " << p1(x) << endl; // p1 est un foncteur !

    cout << "Le polynôme p2(x)= " << p2;
    Polynome p2prime(p2.deriver()); // Dérivation de p2
    cout << " a pour dérivée p2'(x)= " << p2prime;

return 0;
}