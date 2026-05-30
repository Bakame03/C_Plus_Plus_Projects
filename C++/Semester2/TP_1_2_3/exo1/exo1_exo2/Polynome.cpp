#include <iostream>
#include <cmath>
#include "Polynome.hpp"

Polynome::Polynome(unsigned int _degre, const double _coef[])
    : degre(_degre), coef(nullptr) {
    coef = new double[degre + 1];
    for (unsigned int i = 0; i <= degre; i++) 
        coef[i] = _coef[i];
}

Polynome::~Polynome() {
    delete[] coef;
}

// Original copy constructor implementation (From scratch)
// Polynome::Polynome(const Polynome& p)
//     : degre(p.degre), coef(nullptr) {
//     coef = new double[degre + 1];
//     for (unsigned int i = 0; i <= degre; i++) 
//         coef[i] = p.coef[i];
// }

// Using delegating constructor to avoid code duplication (code vu en cours avec Mr. Remy)
Polynome::Polynome(const Polynome& p)
    : Polynome(p.degre, p.coef) {
}

Polynome& Polynome::operator+=(const Polynome& p) {
    if (p.degre > degre) {
        double* newCoef = new double[p.degre + 1];
        for (unsigned int i = 0; i <= degre; i++)
            newCoef[i] = coef[i] + p.coef[i];
        for (unsigned int i = degre + 1; i <= p.degre; i++)
            newCoef[i] = p.coef[i];
        delete[] coef;
        coef = newCoef;
        degre = p.degre;
    } else {
        for (unsigned int i = 0; i <= p.degre; i++)
            coef[i] += p.coef[i];
    }
    return *this;
}

Polynome& Polynome::operator-=(const Polynome& p) {
    if (p.degre > degre) {
        double* newCoef = new double[p.degre + 1];
        for (unsigned int i = 0; i <= degre; i++)
            newCoef[i] = coef[i] - p.coef[i];
        for (unsigned int i = degre + 1; i <= p.degre; i++)
            newCoef[i] = -p.coef[i];
        delete[] coef;
        coef = newCoef;
        degre = p.degre;
    } else {
        for (unsigned int i = 0; i <= p.degre; i++)
            coef[i] -= p.coef[i];
    }
    return *this;
}

Polynome& Polynome::operator*=(double scalaire) {
    if (scalaire == 0.0) {
        delete[] coef;
        degre = 0;
        coef = new double[1]{0.0};
        return *this;
    }
    for (unsigned int i = 0; i <= degre; i++) {
        coef[i] *= scalaire;
    }
    return *this;
}

Polynome& Polynome::operator*=(const Polynome& p) {
    if ((degre == 0 && coef[0] == 0.0) || (p.degre == 0 && p.coef[0] == 0.0)) {
        delete[] coef;
        degre = 0;
        coef = new double[1]{0.0};
        return *this;
    }

    unsigned int newDegre = degre + p.degre;
    double* newCoef = new double[newDegre + 1];
    
    for (unsigned int i = 0; i <= newDegre; i++) {
        newCoef[i] = 0.0;
    }

    for (unsigned int i = 0; i <= degre; i++) {
        for (unsigned int j = 0; j <= p.degre; j++) {
            newCoef[i + j] += coef[i] * p.coef[j];
        }
    }

    delete[] coef;
    degre = newDegre;
    coef = newCoef;
    return *this;
}

Polynome Polynome::deriver() const {
    if (degre == 0) {
        double zeroCoef[1] = {0.0};
        return Polynome(0, zeroCoef);
    }
    double* newCoef = new double[degre];
    for (unsigned int i = 1; i <= degre; i++) {
        newCoef[i - 1] = coef[i] * i;
    }
    Polynome derivedPoly(degre - 1, newCoef);
    delete[] newCoef;
    return derivedPoly;
}

Polynome& Polynome::operator=(const Polynome& p) {
    delete[] coef;
    degre = p.degre;
    coef = new double[degre + 1];
    for (unsigned int i = 0; i <= degre; i++) 
        coef[i] = p.coef[i];
    return *this;
}

bool operator==(const Polynome& p1, const Polynome& p2) {
    if (p1.degre != p2.degre) 
        return false;
    for (unsigned int i = 0; i <= p1.degre; i++) {
        if (p1.coef[i] != p2.coef[i]) 
            return false;
    }
    return true;
}

Polynome operator+(const Polynome& p1, const Polynome& p2) {
    Polynome big = (p1.degre >= p2.degre) ? p1 : p2;
    Polynome small = (p1.degre < p2.degre) ? p1 : p2;
    Polynome p3(big);
    // first way (Eric Remy style)
    // for (unsigned int i = 0; i <= small.degre; i++) {
    //     p3.coef[i] += small.coef[i];
    // }
    
    // second way (Eric Remy style)
    p3 += small;
    return p3;
}

Polynome operator-(const Polynome& p1, const Polynome& p2) {
    Polynome p3(p1);
    p3 -= p2;
    return p3;
}

Polynome operator*(const Polynome& p, double scalaire) {
    Polynome p3(p);
    p3 *= scalaire;
    return p3;
}

Polynome operator*(double scalaire, const Polynome& p) {
    return p * scalaire;
}

Polynome operator*(const Polynome& p1, const Polynome& p2) {
    Polynome p3(p1);
    p3 *= p2;
    return p3;
}

std::ostream& operator<<(std::ostream& os, const Polynome& p) {
    bool polynomeEstVide = true; 

    for(int i = p.degre; i >= 0; i--) {
        double coefficientCourant = p.coef[i];

        if (coefficientCourant == 0.0) 
            continue;
        
        polynomeEstVide = false; 
        
        if ((coefficientCourant > 0) && (i != (int)p.degre)) // ici je fais un cast pour que p.degre soit un int car il est unsigned et que i est int
            os << "+";
        else if (coefficientCourant < 0) {
            os << "-";
            coefficientCourant = -coefficientCourant; 
        }
        
        if (i == 0) {
            os << coefficientCourant;
        } 
        else {
            // Si le chiffre n'est pas 1, on l'affiche. (ex: on n'ecrit pas 1x, on ecrit juste x)
            if (coefficientCourant != 1.0) {
                os << coefficientCourant;
            }
            
            // Affichage de la puissance de x
            if (i == 1) {
                os << "x ";      // x a la puissance 1 est juste x
            } else {
                os << "x^" << i << " "; // x a une puissance superieure
            }
        }
    }
    
    // Si on a fait toute la boucle et qu'on a rien affiche du tout, on affiche 0
    if (polynomeEstVide == true) {
        os << "0";
    }
    
    return os;
}

double Polynome::operator()(double x) {
    double result = 0.0;
    for (unsigned int i = 0; i <= degre; i++) {
        result += coef[i] * pow(x, i);
    }
    return result;
}

void afficher_etat(Polynome* emp[], int taille) {
    std::cout << "\n================= ETAT DES EMPLACEMENTS =================" << std::endl;
    for (int i = 0; i < taille; i++) {
        std::cout << "[" << i << "] : ";
        if (emp[i] == nullptr) {
            std::cout << "vide" << std::endl;
        } else {
            std::cout << "P(x) = " << *(emp[i]) << std::endl;
        }
    }
    std::cout << "=========================================================\n" << std::endl;
}

int demander_emplacement(const std::string& message) {
    int index;
    std::cout << message << " (0 a 9) : ";
    std::cin >> index;
    while (index < 0 || index > 9) {
        std::cout << "Invalide. Veuillez entrer un entier entre 0 et 9 : ";
        std::cin >> index;
    }
    return index;
}
