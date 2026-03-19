#include "mainwindow.h"
#include <QApplication>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // === Zone MDI comme widget central ===
    mdiArea = new QMdiArea(this);
    setCentralWidget(mdiArea);

    // === Barre de statut ===
    barreStatut     = statusBar();
    labelLignes     = new QLabel("nb lignes : 0");
    labelCaracteres = new QLabel("nb caractères : 0");
    barreStatut->addWidget(labelLignes);
    barreStatut->addWidget(labelCaracteres);

    // === Menu Fichier ===
    QMenu *fichierMenu = new QMenu(QString::fromUtf8("&Fichier"), this);
    menuBar()->addMenu(fichierMenu);

    actionNouveau = new QAction(QString::fromUtf8("Nouveau"), this);
    actionNouveau->setShortcut(QKeySequence::New);
    connect(actionNouveau, SIGNAL(triggered()), this, SLOT(nouveau()));
    fichierMenu->addAction(actionNouveau);

    actionOuvrir = new QAction(QString::fromUtf8("Ouvrir"), this);
    actionOuvrir->setShortcut(QKeySequence::Open);
    connect(actionOuvrir, SIGNAL(triggered()), this, SLOT(ouvrir()));
    fichierMenu->addAction(actionOuvrir);

    actionEnregistrer = new QAction(QString::fromUtf8("Enregistrer"), this);
    actionEnregistrer->setShortcut(QKeySequence::Save);
    connect(actionEnregistrer, SIGNAL(triggered()), this, SLOT(enregistrer()));
    fichierMenu->addAction(actionEnregistrer);

    fichierMenu->addSeparator();

    actionQuitter = new QAction(QString::fromUtf8("Quitter"), this);
    actionQuitter->setShortcut(QKeySequence::Quit);
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    fichierMenu->addAction(actionQuitter);

    // === Menu Texte ===
    QMenu *texteMenu = new QMenu(QString::fromUtf8("&Texte"), this);
    menuBar()->addMenu(texteMenu);

    actionFonte = new QAction(QString::fromUtf8("Fonte"), this);
    connect(actionFonte, SIGNAL(triggered()), this, SLOT(choixFonte()));
    texteMenu->addAction(actionFonte);

    actionCouleur = new QAction(QString::fromUtf8("Couleur"), this);
    connect(actionCouleur, SIGNAL(triggered()), this, SLOT(choixCouleur()));
    texteMenu->addAction(actionCouleur);

    texteMenu->addSeparator();

    actionSaut = new QAction(QString::fromUtf8("Saut à la ligne automatique"), this);
    actionSaut->setCheckable(true);
    actionSaut->setChecked(true);
    connect(actionSaut, SIGNAL(triggered()), this, SLOT(modeSaut()));
    texteMenu->addAction(actionSaut);

    // === Barres d'outils ===
    QToolBar *fichierToolBar = addToolBar(QString::fromUtf8("Fichier"));
    fichierToolBar->addAction(actionNouveau);
    fichierToolBar->addAction(actionOuvrir);
    fichierToolBar->addAction(actionEnregistrer);
    fichierToolBar->addSeparator();
    fichierToolBar->addAction(actionQuitter);

    QToolBar *texteToolBar = addToolBar(QString::fromUtf8("Texte"));
    texteToolBar->addAction(actionFonte);
    texteToolBar->addAction(actionCouleur);
    texteToolBar->addSeparator();
    texteToolBar->addAction(actionSaut);

    // Mettre à jour la barre de statut quand la sous-fenêtre active change
    connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)),
            this, SLOT(afficheInformations()));
}

MainWindow::~MainWindow() {}

// Retourne le QTextEdit de la sous-fenêtre active, ou nullptr
QTextEdit *MainWindow::activeTextEdit() const
{
    QMdiSubWindow *sub = mdiArea->activeSubWindow();
    if (sub)
        return qobject_cast<QTextEdit *>(sub->widget());
    return nullptr;
}

void MainWindow::nouveau()
{
    QTextEdit *edit = new QTextEdit();
    edit->setPlaceholderText(QString::fromUtf8("Commencez à taper votre texte ici..."));
    QMdiSubWindow *sub = mdiArea->addSubWindow(edit);
    sub->setWindowTitle(QString::fromUtf8("Sans titre"));
    sub->show();
    connect(edit, SIGNAL(textChanged()), this, SLOT(afficheInformations()));
}

void MainWindow::ouvrir()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        QString::fromUtf8("Ouvrir un fichier"),
        "",
        QString::fromUtf8("Fichiers textes (*.txt);;Tous les fichiers (*)"));

    if (fileName != "")
    {
        QFile file(fileName);
        if (file.open(QIODevice::Text | QIODevice::ReadOnly))
        {
            QTextStream stream(&file);
            QTextEdit *edit = new QTextEdit();
            edit->setText(stream.readAll());
            file.close();

            QMdiSubWindow *sub = mdiArea->addSubWindow(edit);
            sub->setWindowTitle(fileName);
            sub->show();
            connect(edit, SIGNAL(textChanged()), this, SLOT(afficheInformations()));
        }
    }
}

void MainWindow::enregistrer()
{
    QTextEdit *edit = activeTextEdit();
    if (!edit) return;

    QString fileName = QFileDialog::getSaveFileName(
        this,
        QString::fromUtf8("Enregistrer un fichier"),
        "",
        QString::fromUtf8("Fichiers textes (*.txt);;Tous les fichiers (*)"));

    if (fileName != "")
    {
        QFile file(fileName);
        if (file.open(QIODevice::ReadWrite))
        {
            QTextStream stream(&file);
            stream << edit->toHtml();
            file.flush();
            file.close();
        }
    }
}

void MainWindow::choixFonte()
{
    QTextEdit *edit = activeTextEdit();
    if (!edit) return;

    bool ok;
    QFont font = QFontDialog::getFont(&ok, edit->currentFont(), this);
    if (ok)
        edit->setCurrentFont(font);
}

void MainWindow::choixCouleur()
{
    QTextEdit *edit = activeTextEdit();
    if (!edit) return;

    QColor color = QColorDialog::getColor(edit->textColor(), this);
    if (color.isValid())
        edit->setTextColor(color);
}

void MainWindow::modeSaut()
{
    QTextEdit *edit = activeTextEdit();
    if (!edit) return;

    if (actionSaut->isChecked())
        edit->setWordWrapMode(QTextOption::WordWrap);
    else
        edit->setWordWrapMode(QTextOption::NoWrap);
}

void MainWindow::afficheInformations()
{
    QTextEdit *edit = activeTextEdit();
    if (!edit)
    {
        labelLignes->setText("nb lignes : 0");
        labelCaracteres->setText("nb caractères : 0");
        return;
    }
    int nbLignes = edit->document()->lineCount();
    int nbCaract = edit->document()->characterCount();
    labelLignes->setText(QStringLiteral("nb lignes : %1").arg(nbLignes));
    labelCaracteres->setText(QStringLiteral("nb caractères : %1").arg(nbCaract));
}
