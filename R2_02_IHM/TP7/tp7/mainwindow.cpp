#include "mainwindow.h"
#include <QNetworkRequest>
#include <QUrl>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set up a central widget and a layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    // Question 4: Create the ComboBox and add cities 
    cityComboBox = new QComboBox(this);
    
    // Using the required format for OpenWeatherMap (city,country)
    QStringList listItems = {"arles,france", "paris,france", "london,uk", "tokyo,japan"};
    cityComboBox->addItems(listItems);
    
    layout->addWidget(cityComboBox);

    // Question 5: Connect the selection to the API call
    // We use the API key you generated in Question 1
    QString apiKey = "b844741cda192238ffb70b102b8200b7"; 

    connect(cityComboBox, &QComboBox::currentTextChanged, [=](const QString &city) {
        // Construct the URL using the selected city and your API key
        QString url = "https://api.openweathermap.org/data/2.5/weather?q=" + city + "&appid=" + apiKey;
        
        // Call the method to fetch the JSON data
        chargeJSON(url);
    });

    // Optional: Manually trigger it once at startup so the first city loads immediately
    emit cityComboBox->currentTextChanged(cityComboBox->currentText());
}

MainWindow::~MainWindow() {}

void MainWindow::chargeJSON(QString url)
{
    QNetworkRequest request = QNetworkRequest(QUrl(url));
    QNetworkReply* reply = manager.get(request);
    
    // connection à un signal qui indique quand le fichier est téléchargé
    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        // lecture des données
        QString ReplyText = reply->readAll();

        qDebug() << ReplyText;
        
        reply->deleteLater();
    });
}
