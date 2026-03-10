#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);
    textEdit->setPlaceholderText("Commencez à taper votre texte ici...");
}

MainWindow::~MainWindow() {}
