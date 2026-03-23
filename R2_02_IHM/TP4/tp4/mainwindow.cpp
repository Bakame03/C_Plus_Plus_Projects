#include "mainwindow.h"
#include <QApplication>
#include <QFileDialog>
#include <QDockWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scrollArea.setWidget(&imageLabel);
    setCentralWidget(&scrollArea);

    // === Menu Fichier ===
    QMenu *fichierMenu = new QMenu(QString::fromUtf8("&Fichier"), this);
    menuBar()->addMenu(fichierMenu);

    actionOuvrir = new QAction(QString::fromUtf8("Ouvrir image"), this);
    actionOuvrir->setShortcut(QKeySequence::Open);
    connect(actionOuvrir, SIGNAL(triggered()), this, SLOT(ouvrirImage()));
    fichierMenu->addAction(actionOuvrir);

    fichierMenu->addSeparator();

    actionQuitter = new QAction(QString::fromUtf8("Quitter"), this);
    actionQuitter->setShortcut(QKeySequence::Quit);
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    fichierMenu->addAction(actionQuitter);

    // === Menu Affichage ===
    QMenu *affichageMenu = new QMenu(QString::fromUtf8("&Affichage"), this);
    menuBar()->addMenu(affichageMenu);

    actionZoomMoins = new QAction(QString::fromUtf8("Zoom -"), this);
    connect(actionZoomMoins, SIGNAL(triggered()), this, SLOT(zoomMoins()));
    affichageMenu->addAction(actionZoomMoins);

    actionZoomPlus = new QAction(QString::fromUtf8("Zoom +"), this);
    connect(actionZoomPlus, SIGNAL(triggered()), this, SLOT(zoomPlus()));
    affichageMenu->addAction(actionZoomPlus);

    actionTailleNormale = new QAction(QString::fromUtf8("Taille normale"), this);
    connect(actionTailleNormale, SIGNAL(triggered()), this, SLOT(tailleNormale()));
    affichageMenu->addAction(actionTailleNormale);

    // === DockWidget pour les outils ===
    QDockWidget *dock = new QDockWidget(QString::fromUtf8("Outils"), this);
    QWidget *dockWidget = new QWidget(dock);
    QVBoxLayout *dockLayout = new QVBoxLayout(dockWidget);

    QPushButton *btnZoomMoins = new QPushButton(QString::fromUtf8("Zoom -"));
    QPushButton *btnZoomPlus = new QPushButton(QString::fromUtf8("Zoom +"));
    QPushButton *btnTailleNormale = new QPushButton(QString::fromUtf8("Taille normale"));

    dockLayout->addWidget(btnZoomMoins);
    dockLayout->addWidget(btnZoomPlus);
    dockLayout->addWidget(btnTailleNormale);
    dockLayout->addStretch(); // Pousse les boutons vers le haut

    dockWidget->setLayout(dockLayout);
    dock->setWidget(dockWidget);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    // Connexion des boutons aux mêmes slots
    connect(btnZoomMoins, SIGNAL(clicked()), this, SLOT(zoomMoins()));
    connect(btnZoomPlus, SIGNAL(clicked()), this, SLOT(zoomPlus()));
    connect(btnTailleNormale, SIGNAL(clicked()), this, SLOT(tailleNormale()));
}

MainWindow::~MainWindow() {}

#include <QMessageBox>

void MainWindow::ouvrirImage()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        QString::fromUtf8("Ouvrir une image"),
        "",
        QString::fromUtf8("Fichiers Images (*.png *.jpg *.jpeg);;Tous les fichiers (*)"));

    if (fileName != "") {
        if (!image.load(fileName)) {
            QMessageBox::warning(this, "Erreur", "Impossible de charger l'image. Le format JPEG n'est peut-être pas supporté par votre installation Qt.");
            return;
        }
        imageLabel.setPixmap(QPixmap::fromImage(image));
        imageLabel.setScaledContents(true);
        imageLabel.resize(image.size());
        setWindowTitle(fileName);
    }
}
void MainWindow::zoomPlus()
{
    zoom *= 1.25;
    changeZoom();
}

void MainWindow::zoomMoins()
{
    zoom *= 0.8;
    changeZoom();
}

void MainWindow::tailleNormale()
{
    zoom = 1.0;
    changeZoom();
}

void MainWindow::changeZoom()
{
    imageLabel.resize(zoom * image.size());
}
