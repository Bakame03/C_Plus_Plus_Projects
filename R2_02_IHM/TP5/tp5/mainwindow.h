#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void ajouterPoint();
    void supprimerPoint();

private:
    QTableWidget *table = new QTableWidget(0, 2, this);
};
#endif // MAINWINDOW_H
