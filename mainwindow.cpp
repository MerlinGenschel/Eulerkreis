#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include "dockwidget.h"
#include "dialoghelp.h"
#include <QFileDialog>
#include <QCloseEvent>
#include "Graph.h"
#include "paint.h"
#include "control.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // ui->actionBeenden();
    Graph *model                      = new Graph();
    paint *view          = new paint(*model);
    control *controller = new control(*model,*view);

    setCentralWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionBeenden_triggered()
{

    QMessageBox::StandardButton beenden = QMessageBox::question(this, "Achtung!", "Wollen Sie ohne speichern beenden?"
                                        , QMessageBox::Cancel | QMessageBox::Save | QMessageBox::Close);

    if (beenden == QMessageBox::Close)
    {
        QApplication::quit();
    }


}

void MainWindow::on_actionKnotenliste_triggered()
{
    DockWidget* dock = new DockWidget(this);

    addDockWidget(Qt::LeftDockWidgetArea, dock);
   // DockWidget liste;
    //liste.show();
    //ui->setupUi(QDockWidget::DockWidget);
    //setCentralWidget(widget);
}

void MainWindow::on_actionBedienungsanleitung_triggered()
{

    DialogHelp hilfe;
    hilfe.exec();
    //hilfe.setModal(false);
}

void MainWindow::on_action_ffnen_triggered()
{
    QString name = QFileDialog::getOpenFileName(this,"Datei öffnen","/Home");
   /* if(!name.isEmpty())
    {
        QFile datei(name);
        if ( datei . open ( QIODevice :: ReadOnly | QIODevice :: Text ) )
            ui->setPlainText ( QString::fromUtf8(datei.readAll())) ;
}*/
}
