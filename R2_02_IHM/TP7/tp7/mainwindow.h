#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>            
#include <QNetworkAccessManager>    
#include <QComboBox>                
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton> // Added for Question 9
#include <QTimer>      // Added for Question 10

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
    
    QPushButton *refreshButton; // Added for Question 9
    QTimer *timer;              // Added for Question 10
    
    void refreshWeather();      // New helper function
};

#endif // MAINWINDOW_H