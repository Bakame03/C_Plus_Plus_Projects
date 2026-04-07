#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <QModelIndex>
#include <QSplitter>
#include <QFormLayout>
#include <QFileInfo>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void selectionFichier(const QModelIndex &index);

private:
    QFileSystemModel *modeleFichiers;
    QTreeView *vueArbre;
    QWidget *panneauInfos;
    QSplitter *splitter;
    
    // Labels d'informations sur les fichiers
    QLabel *labelDateCreation;
    QLabel *labelSuffixe;
    QLabel *labelRepertoire;
    QLabel *labelExecutable;
    QLabel *labelCache;
    QLabel *labelLectureSeule;
    QLabel *labelDateModification;
    QLabel *labelTaille;
};
#endif // MAINWINDOW_H
