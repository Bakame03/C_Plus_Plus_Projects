#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);
    textEdit->setPlaceholderText("Commencez à taper votre texte ici...");

    // === Menu Fichier ===
    QMenu *fichierMenu = new QMenu(QString::fromUtf8("&Fichier"), this);
    menuBar()->addMenu(fichierMenu);

    actionNouveau = new QAction(QString::fromUtf8("Nouveau"), this);
    actionNouveau->setShortcut(QKeySequence::New);
    fichierMenu->addAction(actionNouveau);

    actionOuvrir = new QAction(QString::fromUtf8("Ouvrir"), this);
    actionOuvrir->setShortcut(QKeySequence::Open);
    fichierMenu->addAction(actionOuvrir);

    actionEnregistrer = new QAction(QString::fromUtf8("Enregistrer"), this);
    actionEnregistrer->setShortcut(QKeySequence::Save);
    fichierMenu->addAction(actionEnregistrer);

    fichierMenu->addSeparator();

    actionQuitter = new QAction(QString::fromUtf8("Quitter"), this);
    actionQuitter->setShortcut(QKeySequence::Quit);
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    fichierMenu->addAction(actionQuitter);

    // === Menu Texte ===
    QMenu *texteMenu = new QMenu(QString::fromUtf8("&Texte"), this);
    menuBar()->addMenu(texteMenu);

    actionCouleur = new QAction(QString::fromUtf8("Couleur"), this);
    texteMenu->addAction(actionCouleur);

    texteMenu->addSeparator();

    actionSautLigne = new QAction(QString::fromUtf8("Saut à la ligne automatique"), this);
    actionSautLigne->setCheckable(true);
    actionSautLigne->setChecked(true);
    texteMenu->addAction(actionSautLigne);
}

MainWindow::~MainWindow() {}
