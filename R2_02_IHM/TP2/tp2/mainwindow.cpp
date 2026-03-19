#include "mainwindow.h"
#include <QApplication>

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
    connect(actionNouveau, SIGNAL(triggered()), textEdit, SLOT(clear()));
    fichierMenu->addAction(actionNouveau);

    actionOuvrir = new QAction(QString::fromUtf8("Ouvrir"), this);
    actionOuvrir->setShortcut(QKeySequence::Open);
    connect(actionOuvrir, SIGNAL(triggered()), this, SLOT(ouvrir()));
    fichierMenu->addAction(actionOuvrir);

    actionEnregistrer = new QAction(QString::fromUtf8("Enregistrer"), this);
    actionEnregistrer->setShortcut(QKeySequence::Save);
    connect(actionEnregistrer, SIGNAL(triggered()), this, SLOT(enregistrer()));
    fichierMenu->addAction(actionEnregistrer);

    fichierMenu->addSeparator();

    actionQuitter = new QAction(QString::fromUtf8("Quitter"), this);
    actionQuitter->setShortcut(QKeySequence::Quit);
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    fichierMenu->addAction(actionQuitter);

    // === Menu Texte ===
    QMenu *texteMenu = new QMenu(QString::fromUtf8("&Texte"), this);
    menuBar()->addMenu(texteMenu);

    actionFonte = new QAction(QString::fromUtf8("Fonte"), this);
    connect(actionFonte, SIGNAL(triggered()), this, SLOT(choixFonte()));
    texteMenu->addAction(actionFonte);

    actionCouleur = new QAction(QString::fromUtf8("Couleur"), this);
    connect(actionCouleur, SIGNAL(triggered()), this, SLOT(choixCouleur()));
    texteMenu->addAction(actionCouleur);

    texteMenu->addSeparator();

    actionSautLigne = new QAction(QString::fromUtf8("Saut à la ligne automatique"), this);
    actionSautLigne->setCheckable(true);
    actionSautLigne->setChecked(true);
    connect(actionSautLigne, SIGNAL(triggered()), this, SLOT(modeSaut()));
    texteMenu->addAction(actionSautLigne);
}

MainWindow::~MainWindow() {}

void MainWindow::choixFonte()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, textEdit->currentFont(), this);
    if (ok)
    {
        textEdit->setCurrentFont(font);
    }
}

void MainWindow::ouvrir()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        QString::fromUtf8("Ouvrir un fichier"),
        "",
        QString::fromUtf8("Fichiers textes (*.txt);;Tous les fichiers (*)"));

    if (fileName != "")
    {
        QFile file(fileName);
        if (file.open(QIODevice::Text | QIODevice::ReadOnly))
        {
            QTextStream stream(&file);
            textEdit->setText(stream.readAll());
            file.close();
        }
        setWindowTitle(fileName);
    }
}

void MainWindow::enregistrer()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        QString::fromUtf8("Enregistrer un fichier"),
        "",
        QString::fromUtf8("Fichiers textes (*.txt);;Tous les fichiers (*)"));

    if (fileName != "")
    {
        QFile file(fileName);
        if (file.open(QIODevice::ReadWrite))
        {
            QTextStream stream(&file);
            stream << textEdit->toHtml();
            file.flush();
            file.close();
        }
    }
}

void MainWindow::choixCouleur()
{
    QColor color = QColorDialog::getColor(textEdit->textColor(), this);
    if (color.isValid())
    {
        textEdit->setTextColor(color);
    }
}

void MainWindow::modeSaut()
{
    if (actionSautLigne->isChecked())
        textEdit->setLineWrapMode(QTextEdit::WidgetWidth);
    else
        textEdit->setLineWrapMode(QTextEdit::NoWrap);
}
