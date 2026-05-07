#include "mainwindow.h"
#include <QNetworkRequest>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{}

MainWindow::~MainWindow() {}

void MainWindow::chargeJSON(QString url)
{
    QNetworkRequest request = QNetworkRequest(QUrl(url));
    QNetworkReply* reply = manager.get(request);
    
    // connection à un signal qui indique quand le fichier est téléchargé
    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        // lecture des données
        QString ReplyText = reply->readAll();
        
        reply->deleteLater();
    });
}
