#include "mainwindow.h"
#include <QNetworkRequest>
#include <QUrl>
#include <QDebug>
#include <QJsonDocument>  
#include <QJsonObject>    
#include <QJsonArray>     

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    cityComboBox = new QComboBox(this);
    QStringList listItems = {"arles,france", "paris,france", "london,uk", "tokyo,japan"};
    cityComboBox->addItems(listItems);
    layout->addWidget(cityComboBox);

    cityLabel = new QLabel("Ville : En attente...", this);
    tempLabel = new QLabel("Température : ", this);
    descLabel = new QLabel("Description : ", this);
    humidityLabel = new QLabel("Humidité : ", this);

    QFont font = cityLabel->font();
    font.setPointSize(12);
    cityLabel->setFont(font);
    tempLabel->setFont(font);
    descLabel->setFont(font);
    humidityLabel->setFont(font);

    layout->addWidget(cityLabel);
    layout->addWidget(tempLabel);
    layout->addWidget(descLabel);
    layout->addWidget(humidityLabel);

    // --- QUESTION 9: The Refresh Button ---
    refreshButton = new QPushButton("Rafraîchir", this);
    layout->addWidget(refreshButton);

    // --- QUESTION 10: The Timer ---
    timer = new QTimer(this);

    // Connect all three elements to our helper function!
    connect(cityComboBox, &QComboBox::currentTextChanged, this, &MainWindow::refreshWeather);
    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::refreshWeather);
    connect(timer, &QTimer::timeout, this, &MainWindow::refreshWeather);

    // Start the timer to tick every 60,000 milliseconds (1 minute)
    timer->start(60000); 

    // Trigger it once so the first city loads immediately on startup
    refreshWeather();
}

MainWindow::~MainWindow() {}

// --- Our new helper method ---
void MainWindow::refreshWeather() 
{
    QString apiKey = "b844741cda192238ffb70b102b8200b7"; 
    QString city = cityComboBox->currentText();
    QString url = "https://api.openweathermap.org/data/2.5/weather?q=" + city + "&appid=" + apiKey;
    
    chargeJSON(url);
}

void MainWindow::chargeJSON(QString url)
{
    QNetworkRequest request = QNetworkRequest(QUrl(url));
    QNetworkReply* reply = manager.get(request);
    
    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        QString ReplyText = reply->readAll();

        QJsonDocument doc = QJsonDocument::fromJson(ReplyText.toUtf8());
        QJsonObject objetJSON = doc.object();

        QString cityName = objetJSON["name"].toString();
        
        QJsonValue weather_main = objetJSON["main"];
        double temp = weather_main["temp"].toDouble() - 273.15; 
        double humidity = weather_main["humidity"].toDouble();

        QJsonValue weather = objetJSON["weather"];
        QString description = weather[0]["description"].toString();

        cityLabel->setText("Ville : " + cityName);
        tempLabel->setText("Température : " + QString::number(temp, 'f', 1) + " °C");
        descLabel->setText("Description : " + description);
        humidityLabel->setText("Humidité : " + QString::number(humidity) + " %");
        
        reply->deleteLater();
    });
}