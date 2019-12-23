#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dockwidget.h"
#include "dialoghelp.h"
#include "Graph.h"
#include "paint.h"
#include "control.h"

#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QCloseEvent>
#include <QUndoStack>
#include <string>

//class Graph;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QUndoStack *undoStack = new QUndoStack(this);
    // ui->actionBeenden();
    model                      = new Graph(this);
    paint *view          = new paint(*model);
    /*control *controller =*/ new control(*model,*view, undoStack, this);

    //control::modus = 1;
    setCentralWidget(view);

    undo = undoStack->createUndoAction(this);
    redo = undoStack->createRedoAction(this);
    ui->toolBar->addAction(undo);
    ui->toolBar->addAction(redo);
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

//Erstelle neues DockWidget zur Anzeige der KnotenListe / Adjazenzliste
void MainWindow::on_actionKnotenliste_triggered()
{
    DockWidget* dock = new DockWidget(*model,this);
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    //Verbinde den "graphChanged" mit "updateKnotenListe"
    connect(model, &Graph::graphChanged,dock,&DockWidget::updateKnotenListe);

}

void MainWindow::on_actionBedienungsanleitung_triggered()
{

    DialogHelp hilfe;
    hilfe.exec();
    //hilfe.setModal(false);
}

void MainWindow::on_action_ffnen_triggered()
{
 /*   QString nameAkt = QFileDialog::getOpenFileName(this,"Datei öffnen","/Home");
    if(!nameAkt.isEmpty())
        model->readFromFile(nameAkt.fromUtf8().constData());
*/
    QString nameAkt = QFileDialog::getOpenFileName(this, tr("Datei laden"),"*.txt");
    if(!nameAkt.isEmpty())
    {
        QFile file;
        file.open(QIODevice::ReadOnly);
        QDataStream instream(&file);
        file.close();
     }
}

void MainWindow::on_actionKnoten_zeichnen_triggered()
{
   //control::setMode(1);

}

void MainWindow::on_actionVerbinden_triggered()
{
    //control::setMode(2);
}

void MainWindow::on_actionSpeichern_unter_triggered()
{
    QString nameAkt = QFileDialog::getSaveFileName(this, "Datei speichern", "/home");
    if(!nameAkt.isEmpty())
     {
        qDebug() << nameAkt;
        qDebug() << nameAkt.toUtf8();

        model->writeToFile(nameAkt.toUtf8().constData());

    }
}

void MainWindow::on_actionSpeichern_triggered()
{
    QString nameAkt;
    if (nameAkt.isEmpty())
    {
        QString nameAkt = QFileDialog::getSaveFileName(this, "Datei speichern", "/home");
        model->writeToFile(nameAkt.toUtf8().constData());
    }
    else
        if (!nameAkt.isEmpty())
        model->writeToFile(nameAkt.toUtf8().constData());

}

void MainWindow::on_actionEulerkreis_triggered()
{
    //bei klick: check, ob Eulerkreis
}


