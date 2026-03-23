#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QScrollArea>
#include <QImage>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void ouvrirImage();
    void zoomPlus();
    void zoomMoins();
    void tailleNormale();

private:
    QLabel imageLabel;
    QScrollArea scrollArea;
    QImage image;

    double zoom = 1.0;
    void changeZoom();

    QAction *actionOuvrir;
    QAction *actionQuitter;
    QAction *actionZoomPlus;
    QAction *actionZoomMoins;
    QAction *actionTailleNormale;
};
#endif // MAINWINDOW_H
