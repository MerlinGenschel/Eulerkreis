#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dockwidget.h"
#include "animationwidget.h"
#include "animation.h"
#include "dialoghelp.h"
#include "Graph.h"
#include "paint.h"
#include "control.h"

#include<QVBoxLayout>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QCloseEvent>
#include <QUndoStack>
#include <string>
#include "animation.h"
#include "animationwidget.h"

//class Graph;

class Animation;
class animationWidget;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);


    QUndoStack *undoStack = new QUndoStack(this);
    // ui->actionBeenden();
    
    Animationswidget* animationswidget  = new Animationswidget;

    model                      = new Graph(this);
    view          = new paint(*model);
    /*control *controller = new control(*model,*view, undoStack, this);*/

    controller = new control(*model,*view, undoStack, this);

    Animationspresenter* animationscontroller = new Animationspresenter(*model, this);

    animationscontroller->addAnimationswidget(*animationswidget);
    //animation* animationspresenter = new animation(*model,*view,undoStack,parent);
    //animationWidget* animationswidget  = new animationWidget(*model,*view,parent);
    //animationspresenter->addAnimationswidget(*animationswidget);
    //control::modus = 1;


    QWidget* widget = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(widget);
    layout->addWidget(view);
    layout->addWidget(animationswidget);
    setCentralWidget(widget);

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
    nameAkt = QFileDialog::getOpenFileName(this,"Datei öffnen","/Home");
    if(!nameAkt.isEmpty())
        model->readFromFile(nameAkt.toUtf8().constData());

/*    QString nameAkt = QFileDialog::getOpenFileName(this, tr("Datei laden"),"*.txt");
    if(!nameAkt.isEmpty())
    {
        QFile file;
        file.open(QIODevice::ReadOnly);
        QDataStream instream(&file);
        file.close();
     }*/
}

void MainWindow::on_actionKnoten_zeichnen_triggered()
{
    controller->setMode(1);
}

void MainWindow::on_actionVerbinden_triggered()
{
    controller->setMode(2);
}

void MainWindow::on_actionVerschieben_triggered()
{
    controller->setMode(3);
}

void MainWindow::on_actionL_schen_triggered()
{
    controller->setMode(4);
}

void MainWindow::on_actionSpeichern_unter_triggered()
{
    nameAkt = QFileDialog::getSaveFileName(this, "Datei speichern", "/home");
    if(!nameAkt.isEmpty())
     {
        qDebug() << nameAkt;
        qDebug() << nameAkt.toUtf8();

        model->writeToFile(nameAkt.toUtf8().constData());

    }
}

void MainWindow::on_actionSpeichern_triggered()
{
    if (nameAkt.isEmpty())
    {
        nameAkt = QFileDialog::getSaveFileName(this, "Datei speichern", "/home");
        model->writeToFile(nameAkt.toUtf8().constData());
    }
    else
        if (!nameAkt.isEmpty())
        model->writeToFile(nameAkt.toUtf8().constData());

}

void MainWindow::on_actionEulerkreis_triggered()
{
    if (model->printEulerWeg())
        qDebug()<<"Es gibt einen EulerWeg/Eulerkreis: Klicke auf Animation um die Animation zu starten";
    //qDebug()<<model->getPath().size();
    //if (model->printEulerWeg())
    //{
    ////vector<Edge>eulerPath = model->getPath();
    ////emit(model->graphChanged());
    //Animationswidget *ani = new Animationswidget(this);
    ////addDockWidget(Qt::TopDockWidgetArea, ani);
    ////ani->eulerAnimation(  );
    //
   ///* if(model->printEulerWeg())
    //{
    //    vector<Edge>eulerPath = model->getPath();
    //    if(eulerPath[0].src == eulerPath[eulerPath.size()-1].dest)
    //        qDebug()<<"Kreis";
    //    else
    //        qDebug()<<"Eulerweg";
    //    for(int i = 0;i<eulerPath.size();i++)
    //        qDebug() <<eulerPath[i].src << " "<<eulerPath[i].dest;
    //
    //}
    //else
    //{
    //     qDebug()<< "Graph hat keinen Eulerkreis/Eulerweg";
    //}*/

}




void MainWindow::on_actionNeu_triggered()
{
       if (!model->getSize()==0)
       model->clear();
}
