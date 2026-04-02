#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QChartView>
#include <QChart>
#include <QLineSeries>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void ajouterPoint();
    void supprimerPoint();
    void modifieTable(int row, int col);

private:
    QTableWidget *table = new QTableWidget(0, 2, this);
    QChartView *graphique;
    QChart *graphe;
    QLineSeries *courbe;
};
#endif // MAINWINDOW_H
