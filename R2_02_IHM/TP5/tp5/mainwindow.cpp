#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QHeaderView>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QVBoxLayout *layout = new QVBoxLayout();
    
    // Instanciation des objets graphiques
    graphique = new QChartView(this);
    graphe = new QChart();
    courbe = new QLineSeries(this);
    
    graphe->addSeries(courbe);      // Initialise le graphe avec la courbe
    graphique->setChart(graphe);    // Indique au widget quel graphe afficher
    
    layout->addWidget(graphique);   // Ajout du graphique en haut du layout
    
    // Ajout et configuration de la table
    layout->addWidget(table);
    
    QStringList tableHeader = { "Abscisse", "Ordonnée"};
    table->setHorizontalHeaderLabels(tableHeader);
    
    QHeaderView* header = table->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    // Ajout des boutons en dessous (layout horizontal)
    QHBoxLayout *hLayout = new QHBoxLayout();
    QPushButton *btnAjouter = new QPushButton(QString::fromUtf8("Ajouter point"));
    QPushButton *btnSupprimer = new QPushButton(QString::fromUtf8("Supprimer point"));
    
    hLayout->addWidget(btnAjouter);
    hLayout->addWidget(btnSupprimer);
    layout->addLayout(hLayout);

    connect(btnAjouter, SIGNAL(clicked()), this, SLOT(ajouterPoint()));
    connect(btnSupprimer, SIGNAL(clicked()), this, SLOT(supprimerPoint()));

    QWidget *window = new QWidget();
    window->setLayout(layout);
    setCentralWidget(window);
}

MainWindow::~MainWindow() {}

void MainWindow::ajouterPoint()
{
    // Insère une nouvelle ligne à la fin de la table
    table->insertRow(table->rowCount());
}

void MainWindow::supprimerPoint()
{
    // Supprime les lignes sélectionnées en partant de la fin
    QModelIndexList selection = table->selectionModel()->selectedRows();
    for (int i = selection.count() - 1; i >= 0; i--) {
        QModelIndex index = selection.at(i);
        table->removeRow(index.row());
    }
}
