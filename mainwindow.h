#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionBeenden_triggered();

    void on_actionKnotenliste_triggered();

    void on_actionBedienungsanleitung_triggered();

    void on_action_ffnen_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
