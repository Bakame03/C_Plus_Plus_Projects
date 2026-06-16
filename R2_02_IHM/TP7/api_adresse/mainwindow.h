#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void chargeJSON(QString url);

private slots:
    void onSearchClicked();

private:
    QNetworkAccessManager manager;
    QLineEdit    *searchInput;
    QPushButton  *searchButton;
    QLabel       *statusLabel;
    QTableWidget *resultTable;
};

#endif // MAINWINDOW_H
