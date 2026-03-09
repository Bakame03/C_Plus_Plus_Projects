#ifndef FENETRE_H
#define FENETRE_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>

class Fenetre : public QWidget
{
    Q_OBJECT

public:
    Fenetre(QWidget *parent = nullptr);
    ~Fenetre();
private:
    QDoubleSpinBox* valeurMetre;
    QDoubleSpinBox* valeurFoot;
    QDoubleSpinBox* valeurInch;
    QPushButton *bQuitter;
};
#endif // FENETRE_H

