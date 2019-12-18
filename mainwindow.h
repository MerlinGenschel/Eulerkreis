#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Graph;
class MainWindow : public QMainWindow
{
    Q_OBJECT

    Graph* model;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionBeenden_triggered();

    void on_actionKnotenliste_triggered();

    void on_actionBedienungsanleitung_triggered();

    void on_action_ffnen_triggered();

    void on_actionKnoten_zeichnen_triggered();

    void on_actionVerbinden_triggered();

    void on_actionSpeichern_unter_triggered();

    void on_actionSpeichern_triggered();


    void on_actionEulerkreis_triggered();

private:
    Ui::MainWindow *ui;
    QAction *undo;
    QAction *redo;
};
#endif // MAINWINDOW_H
