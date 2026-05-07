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

    // Initialize the labels and add them to the layout
    cityLabel = new QLabel("Ville : En attente...", this);
    tempLabel = new QLabel("Température : ", this);
    descLabel = new QLabel("Description : ", this);
    humidityLabel = new QLabel("Humidité : ", this);

    // Make the text a little bigger and nicer
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

    QString apiKey = "b844741cda192238ffb70b102b8200b7"; 

    connect(cityComboBox, &QComboBox::currentTextChanged, [=](const QString &city) {
        QString url = "https://api.openweathermap.org/data/2.5/weather?q=" + city + "&appid=" + apiKey;
        chargeJSON(url);
    });

    emit cityComboBox->currentTextChanged(cityComboBox->currentText());
}

MainWindow::~MainWindow() {}

void MainWindow::chargeJSON(QString url)
{
    QNetworkRequest request = QNetworkRequest(QUrl(url));
    QNetworkReply* reply = manager.get(request);
    
    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        QString ReplyText = reply->readAll();

        // --- QUESTIONS 6, 7, and 8: Parsing the JSON ---
        
        // 1. Convert the raw text into a JSON Document
        QJsonDocument doc = QJsonDocument::fromJson(ReplyText.toUtf8());
        QJsonObject objetJSON = doc.object();

        // 2. Extract specific values
        QString cityName = objetJSON["name"].toString();
        
        QJsonValue weather_main = objetJSON["main"];
        // The API returns temp in Kelvin by default, so we subtract 273.15 for Celsius
        double temp = weather_main["temp"].toDouble() - 273.15; 
        double humidity = weather_main["humidity"].toDouble();

        QJsonValue weather = objetJSON["weather"];
        QString description = weather[0]["description"].toString();

        // 3. Update the UI Labels with the extracted data
        cityLabel->setText("Ville : " + cityName);
        tempLabel->setText("Température : " + QString::number(temp, 'f', 1) + " °C");
        descLabel->setText("Description : " + description);
        humidityLabel->setText("Humidité : " + QString::number(humidity) + " %");
        
        reply->deleteLater();
    });
}