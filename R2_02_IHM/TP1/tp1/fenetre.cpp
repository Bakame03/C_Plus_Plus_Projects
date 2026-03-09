#include "fenetre.h"
#include <QApplication>  

Fenetre::Fenetre(QWidget *parent)
    : QWidget(parent)
{   
    setWindowTitle("ConvertDist");
    setWindowFlags(Qt::WindowStaysOnTopHint);
    resize(250,150);

    valeurMetre = new QDoubleSpinBox(this);
    valeurFoot = new QDoubleSpinBox(this);
    valeurInch = new QDoubleSpinBox(this);
    bQuitter = new QPushButton("Quitter", this);

    connect(valeurMetre, SIGNAL(valueChanged(double)), this, SLOT(convertirMetre(double)));
    connect(valeurFoot,  SIGNAL(valueChanged(double)), this, SLOT(convertirFoot(double)));
    connect(valeurInch,  SIGNAL(valueChanged(double)), this, SLOT(convertirInch(double)));

    valeurMetre->setMaximum(1000000);
    valeurFoot->setMaximum(1000000);
    valeurInch->setMaximum(1000000);

    valeurMetre->setDecimals(5);
    valeurFoot->setDecimals(5);
    valeurInch->setDecimals(5);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("mètre", valeurMetre);
    formLayout->addRow("foot",  valeurFoot);
    formLayout->addRow("inch",  valeurInch);

    mainLayout->addLayout(formLayout);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(bQuitter);
    mainLayout->addLayout(buttonLayout);

    connect(bQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));

    setLayout(mainLayout);
}


void Fenetre::convertirMetre(double val)
{
    valeurFoot->blockSignals(true);
    valeurInch->blockSignals(true);
    valeurFoot->setValue(val * 3.28084);
    valeurInch->setValue(val * 39.3701);
    valeurFoot->blockSignals(false);
    valeurInch->blockSignals(false);
}

void Fenetre::convertirFoot(double val)
{
    double m = val / 3.28084;
    valeurMetre->blockSignals(true);
    valeurInch->blockSignals(true);
    valeurMetre->setValue(m);
    valeurInch->setValue(m * 39.3701);
    valeurMetre->blockSignals(false);
    valeurInch->blockSignals(false);
}

void Fenetre::convertirInch(double val)
{
    double m = val / 39.3701;
    valeurMetre->blockSignals(true);
    valeurFoot->blockSignals(true);
    valeurMetre->setValue(m);
    valeurFoot->setValue(m * 3.28084);
    valeurMetre->blockSignals(false);
    valeurFoot->blockSignals(false);
}

Fenetre::~Fenetre() {}
