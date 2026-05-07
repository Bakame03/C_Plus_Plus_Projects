#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>            
#include <QNetworkAccessManager>    
#include <QComboBox>                
#include <QVBoxLayout>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void chargeJSON(QString url);

private:
    QNetworkAccessManager manager;
    QComboBox *cityComboBox;
    QLabel *cityLabel;
    QLabel *tempLabel;
    QLabel *descLabel;
    QLabel *humidityLabel;
};


#endif // MAINWINDOW_H
