#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
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
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void nouveau();
    void ouvrir();
    void enregistrer();
    void choixFonte();
    void choixCouleur();
    void modeSaut();
    void afficheInformations();

private:
    // Helper : retourne le QTextEdit de la sous-fenêtre active (nullptr si aucune)
    QTextEdit *activeTextEdit() const;

    QMdiArea   *mdiArea;
    QStatusBar *barreStatut;
    QLabel     *labelLignes;
    QLabel     *labelCaracteres;

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
