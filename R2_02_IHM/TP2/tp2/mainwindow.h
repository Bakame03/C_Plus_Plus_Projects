#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QTextEdit *textEdit;

    // Actions menu Fichier
    QAction *actionNouveau;
    QAction *actionOuvrir;
    QAction *actionEnregistrer;
    QAction *actionQuitter;

    // Actions menu Texte
    QAction *actionCouleur;
    QAction *actionSautLigne;
};
#endif // MAINWINDOW_H
