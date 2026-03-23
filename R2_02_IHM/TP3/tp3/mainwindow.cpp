#include "mainwindow.h"
#include <cmath>
#include <QTime>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QString::fromUtf8("Horloge"));
    resize(300, 300);
    setStyleSheet("QMainWindow {background: rgb(150,200,250);}");
    
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);
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
    painter.setPen(QPen(Qt::black, 2));
    for (int i = 0; i < 12; ++i) {
        double angle = i * (M_PI / 6.0); // 2 * PI / 12 = PI / 6
        // Point sur le bord du grand cercle (rayon 140, centre 150,150)
        int x1 = 150 + 140 * cos(angle);
        int y1 = 150 + 140 * sin(angle);
        // Point vers l'intérieur pour la longueur de la graduation (rayon 130)
        int x2 = 150 + 130 * cos(angle);
        int y2 = 150 + 130 * sin(angle);
        painter.drawLine(x1, y1, x2, y2);
    }
}

void MainWindow::afficheChiffres(QPainter &painter)
{
    painter.setPen(QPen(Qt::black, 1));
    for (int i = 1; i <= 12; ++i) {
        // L'angle 0 est à l'Est (3h). On décale pour que 12 soit en haut (-PI/2)
        double angle = (i - 3) * (M_PI / 6.0);
        
        // Rayon intérieur pour placer le texte (115 pour être sous les graduations)
        int r = 115;
        int cx = 150 + r * cos(angle);
        int cy = 150 + r * sin(angle);
        
        // On dessine le texte centré dans un carré de 30x30 autour du point (cx, cy)
        painter.drawText(cx - 15, cy - 15, 30, 30, Qt::AlignCenter, QString::number(i));
    }
}

void MainWindow::afficheAiguilles(QPainter &painter)
{
    QTime t = QTime::currentTime();
    int h = t.hour();
    int m = t.minute();
    int s = t.second();
    
    // Calcul des angles en radians (-PI/2 pour être à 12h)
    // On ajoute les fractions pour un mouvement fluide
    double angleS = (s / 60.0) * 2 * M_PI - M_PI / 2.0;
    double angleM = ((m + s / 60.0) / 60.0) * 2 * M_PI - M_PI / 2.0;
    double angleH = (((h % 12) + m / 60.0) / 12.0) * 2 * M_PI - M_PI / 2.0;
    
    // Aiguille des heures (rouge, épaisseur 6, longueur 70)
    painter.setPen(QPen(Qt::red, 6));
    painter.drawLine(150, 150, 150 + 70 * cos(angleH), 150 + 70 * sin(angleH));
    
    // Aiguille des minutes (bleue, épaisseur 3, longueur 100)
    painter.setPen(QPen(Qt::blue, 3));
    painter.drawLine(150, 150, 150 + 100 * cos(angleM), 150 + 100 * sin(angleM));
    
    // Aiguille des secondes (noire, épaisseur 1, longueur 100)
    painter.setPen(QPen(Qt::black, 1));
    painter.drawLine(150, 150, 150 + 100 * cos(angleS), 150 + 100 * sin(angleS));
}
