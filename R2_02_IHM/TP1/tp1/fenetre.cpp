#include "fenetre.h"
#include <QApplication>  // needed for qApp->quit()

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

    // signal/slot pour quitter l'application
    connect(bQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));

    setLayout(mainLayout);
}

Fenetre::~Fenetre() {}
