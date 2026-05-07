#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>            
#include <QNetworkAccessManager>    

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void chargeJSON(QString url);

private:
    QNetworkAccessManager manager;
};


#endif // MAINWINDOW_H
