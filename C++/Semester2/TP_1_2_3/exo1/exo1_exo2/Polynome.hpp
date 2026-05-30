#ifndef __POLYNOME_HPP__
#define __POLYNOME_HPP__

#include <iostream>

class Polynome {
private:
    unsigned int degre;
    double* coef;
public:
    Polynome(unsigned int _degre, const double _coef[]);
    ~Polynome();
    Polynome() = delete;
    Polynome(const Polynome& p);
    inline unsigned int getDegre() const { return degre; }
    Polynome& operator+=(const Polynome& p);
    Polynome& operator-=(const Polynome& p);
    Polynome& operator*=(double scalaire);
    Polynome& operator*=(const Polynome& p);
    Polynome deriver() const;
    Polynome& operator=(const Polynome& p);
    friend bool operator==(const Polynome& p1, const Polynome& p2);
    friend Polynome operator+(const Polynome& p1, const Polynome& p2);
    friend Polynome operator-(const Polynome& p1, const Polynome& p2);
    friend Polynome operator*(const Polynome& p, double scalaire);
    friend Polynome operator*(double scalaire, const Polynome& p);
    friend Polynome operator*(const Polynome& p1, const Polynome& p2);
    friend std::ostream& operator<<(std::ostream& os, const Polynome& p);
    inline double& operator[](const int i) {
        if (i >= 0 && (unsigned int)i <= degre) // ici je fais un cast pour que i unsigned car il etait int et que degre est unsigned
            return coef[i];
        else {
            throw std::out_of_range("Index out of range");
        }
    }
    double operator()(double x);
};

void afficher_etat(Polynome* emp[], int taille);
int demander_emplacement(const std::string& message);

#endif 
