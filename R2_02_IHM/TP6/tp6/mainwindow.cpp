#include "mainwindow.h"
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    modeleFichiers = new QFileSystemModel;
    modeleFichiers->setRootPath("/");

    vueArbre = new QTreeView();
    vueArbre->setModel(modeleFichiers);

    // Instructions 9-10 : panneauInfos + splitter
    panneauInfos = new QWidget();
    QFormLayout *infosLayout = new QFormLayout();
    
    // Instruction 12 : création des labels et ajout dans infosLayout
    labelDateCreation     = new QLabel();
    labelSuffixe          = new QLabel();
    labelRepertoire       = new QLabel();
    labelExecutable       = new QLabel();
    labelCache            = new QLabel();
    labelLectureSeule     = new QLabel();
    labelDateModification = new QLabel();
    labelTaille           = new QLabel();
    
    infosLayout->addRow(QString::fromUtf8("Date de création :"),      labelDateCreation);
    infosLayout->addRow(QString::fromUtf8("Suffixe :"),               labelSuffixe);
    infosLayout->addRow(QString::fromUtf8("Répertoire :"),            labelRepertoire);
    infosLayout->addRow(QString::fromUtf8("Exécutable :"),            labelExecutable);
    infosLayout->addRow(QString::fromUtf8("Caché :"),                 labelCache);
    infosLayout->addRow(QString::fromUtf8("Lecture seule :"),         labelLectureSeule);
    infosLayout->addRow(QString::fromUtf8("Dernière modification :"), labelDateModification);
    infosLayout->addRow(QString::fromUtf8("Taille (octets) :"),       labelTaille);
    
    panneauInfos->setLayout(infosLayout);

    splitter = new QSplitter();
    splitter->addWidget(vueArbre);
    splitter->addWidget(panneauInfos);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(splitter);

    QWidget *window = new QWidget();
    window->setLayout(mainLayout);
    setCentralWidget(window);

    // Instruction 6 : connexion clic -> selectionFichier
    connect(vueArbre, SIGNAL(clicked(QModelIndex)),
            this, SLOT(selectionFichier(QModelIndex)));
}

MainWindow::~MainWindow() {}

// Instructions 8-13 : slot selectionFichier
void MainWindow::selectionFichier(const QModelIndex &index)
{
    // Instruction 8 : obtenir les infos du fichier/dossier cliqué
    QFileInfo fileInfo = modeleFichiers->fileInfo(index);

    // Instruction 13 : remplir les labels avec les informations
    labelDateCreation->setText(fileInfo.birthTime().toString());
    labelSuffixe->setText(fileInfo.completeSuffix());
    labelRepertoire->setText(fileInfo.isDir() ? "Oui" : "Non");
    labelExecutable->setText(fileInfo.isExecutable() ? "Oui" : "Non");
    labelCache->setText(fileInfo.isHidden() ? "Oui" : "Non");
    labelLectureSeule->setText(fileInfo.isWritable() ? "Non" : "Oui"); // isWritable() = false → lecture seule
    labelDateModification->setText(fileInfo.lastModified().toString());
    labelTaille->setText(QString::number(fileInfo.size()));
}
