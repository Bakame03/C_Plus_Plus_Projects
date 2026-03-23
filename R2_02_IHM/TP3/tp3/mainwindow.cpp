#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QString::fromUtf8("Horloge"));
    resize(300, 300);
    setStyleSheet("QMainWindow {background: rgb(150,200,250);}");
}

MainWindow::~MainWindow() {}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    
    // On fait ici les affichages graphiques :
    afficheFond(painter);
    afficheGraduations(painter);
    afficheChiffres(painter);
    afficheAiguilles(painter);
}

void MainWindow::afficheFond(QPainter &painter)
{
    painter.setPen(QPen(Qt::black, 2));
    painter.drawEllipse(10, 10, 280, 280);
}

void MainWindow::afficheGraduations(QPainter &painter)
{
}

void MainWindow::afficheChiffres(QPainter &painter)
{
}

void MainWindow::afficheAiguilles(QPainter &painter)
{
}
