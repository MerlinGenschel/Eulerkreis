#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class control;
class Graph;
class animation;
class MainWindow : public QMainWindow
{
    Q_OBJECT

    Graph* model;
    animation* animationController;
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

    void on_actionVerschieben_triggered();

    void on_actionL_schen_triggered();

    void on_actionSpeichern_unter_triggered();

    void on_actionSpeichern_triggered();

    void on_actionEulerkreis_triggered();

    void on_actionNeu_triggered();

    void closeEvent(QCloseEvent*event);
    void save();
    void saveAs();
    void load();
private:
    Ui::MainWindow *ui;
    control *controller =nullptr;
    QAction *undo;
    QAction *redo;
    QString nameAkt;

};
#endif // MAINWINDOW_H
