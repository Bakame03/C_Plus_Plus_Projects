#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QFontDialog>
#include <QColorDialog>
#include <QStatusBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void ouvrir();
    void enregistrer();
    void choixFonte();
    void choixCouleur();
    void modeSaut();

private:
    QTextEdit   *textEdit;
    QStatusBar  *barreStatut;

    // Actions menu Fichier
    QAction *actionNouveau;
    QAction *actionOuvrir;
    QAction *actionEnregistrer;
    QAction *actionQuitter;

    // Actions menu Texte
    QAction *actionFonte;
    QAction *actionCouleur;
    QAction *actionSaut;
};
#endif // MAINWINDOW_H
