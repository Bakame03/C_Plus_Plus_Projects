#include "mainwindow.h"
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QHeaderView>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Recherche d'Adresses — API Adresse (data.gouv.fr)");
    resize(900, 520);

    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->setSpacing(10);
    layout->setContentsMargins(15, 15, 15, 15);
    setCentralWidget(central);

    // ── Titre ──────────────────────────────────────────────────────────────
    QLabel *titleLabel = new QLabel("🔍 Recherche d'Adresses Françaises", this);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    QLabel *sourceLabel = new QLabel("Source : <a href='https://api-adresse.data.gouv.fr'>api-adresse.data.gouv.fr</a> — Base Adresse Nationale (BAN)", this);
    sourceLabel->setOpenExternalLinks(true);
    sourceLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(sourceLabel);

    // ── Barre de recherche ─────────────────────────────────────────────────
    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchInput = new QLineEdit(this);
    searchInput->setPlaceholderText("Entrez une adresse (ex : 8 rue de la Paix Paris)");
    searchInput->setMinimumHeight(32);
    searchButton = new QPushButton("Rechercher", this);
    searchButton->setMinimumHeight(32);
    searchLayout->addWidget(searchInput);
    searchLayout->addWidget(searchButton);
    layout->addLayout(searchLayout);

    // ── Statut ─────────────────────────────────────────────────────────────
    statusLabel = new QLabel("Entrez une adresse pour commencer.", this);
    layout->addWidget(statusLabel);

    // ── Tableau de résultats ───────────────────────────────────────────────
    resultTable = new QTableWidget(0, 5, this);
    resultTable->setHorizontalHeaderLabels({
        "Adresse complète", "Ville", "Code Postal", "Département / Région", "Score"
    });
    resultTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    resultTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    resultTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    resultTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    resultTable->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    resultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    resultTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    resultTable->setAlternatingRowColors(true);
    layout->addWidget(resultTable);

    connect(searchButton, &QPushButton::clicked, this, &MainWindow::onSearchClicked);
    connect(searchInput,  &QLineEdit::returnPressed, this, &MainWindow::onSearchClicked);
}

MainWindow::~MainWindow() {}

void MainWindow::onSearchClicked()
{
    QString query = searchInput->text().trimmed();
    if (query.isEmpty()) {
        statusLabel->setText("Veuillez entrer une adresse.");
        return;
    }

    statusLabel->setText("Recherche en cours…");
    resultTable->setRowCount(0);

    QUrl url("https://api-adresse.data.gouv.fr/search/");
    QUrlQuery params;
    params.addQueryItem("q", query);
    params.addQueryItem("limit", "10");
    url.setQuery(params);

    chargeJSON(url.toString());
}

void MainWindow::chargeJSON(QString url)
{
    QNetworkRequest request(QUrl(url));
    QNetworkReply *reply = manager.get(request);

    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() != QNetworkReply::NoError) {
            statusLabel->setText("Erreur réseau : " + reply->errorString());
            reply->deleteLater();
            return;
        }

        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonArray features = doc.object()["features"].toArray();

        resultTable->setRowCount(features.size());
        for (int i = 0; i < features.size(); ++i) {
            QJsonObject props = features[i].toObject()["properties"].toObject();

            double score = props["score"].toDouble();
            QString scoreStr = QString::number(score * 100, 'f', 1) + " %";

            resultTable->setItem(i, 0, new QTableWidgetItem(props["label"].toString()));
            resultTable->setItem(i, 1, new QTableWidgetItem(props["city"].toString()));
            resultTable->setItem(i, 2, new QTableWidgetItem(props["postcode"].toString()));
            resultTable->setItem(i, 3, new QTableWidgetItem(props["context"].toString()));
            resultTable->setItem(i, 4, new QTableWidgetItem(scoreStr));

            // Colorer le score : vert si > 80 %, orange sinon
            QColor color = (score >= 0.8) ? QColor(200, 255, 200) : QColor(255, 220, 160);
            for (int col = 0; col < 5; ++col) {
                if (resultTable->item(i, col))
                    resultTable->item(i, col)->setBackground(color);
            }
        }

        statusLabel->setText(
            features.isEmpty()
                ? "Aucun résultat trouvé."
                : QString("%1 résultat(s) trouvé(s).").arg(features.size())
        );
        reply->deleteLater();
    });
}
