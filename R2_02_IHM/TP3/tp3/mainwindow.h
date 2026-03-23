#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void afficheFond(QPainter &painter);
    void afficheGraduations(QPainter &painter);
    void afficheChiffres(QPainter &painter);
    void afficheAiguilles(QPainter &painter);
};
#endif // MAINWINDOW_H
