#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dockwidget.h"
#include "animationwidget.h"
#include "animation.h"
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
class animation;
class animationWidget;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QUndoStack *undoStack = new QUndoStack(this);
    model                 = new Graph(this);
    paint *view           = new paint(*model);
    controller            = new control(*model, *view, undoStack, this);

    vector<Edge>eulerPath = model->getPath();
    emit(model->graphChanged());

    animationController = new animation(*model,undoStack,this);
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

//Funktion speichern
void MainWindow::save()
{
    if (nameAkt.isEmpty())
    {
        nameAkt = QFileDialog::getSaveFileName(this, "Datei speichern", "/home");

        model->writeToFile(nameAkt.toUtf8().constData());
        controller->deleteUndoStack();
    }
    else
    {
        if (!nameAkt.isEmpty())
        {
            model->writeToFile(nameAkt.toUtf8().constData());
            controller->deleteUndoStack();
        }
    }
}

//Funktion speichern unter
void MainWindow::saveAs()
{
    nameAkt = QFileDialog::getSaveFileName(this, "Datei speichern", "/home");
    if(!nameAkt.isEmpty())
     {
        qDebug() << nameAkt;
        qDebug() << nameAkt.toUtf8();

        model->writeToFile(nameAkt.toUtf8().constData());
        controller->deleteUndoStack();
    }

}

//Funktion laden
void MainWindow::load()
{
    nameAkt = QFileDialog::getOpenFileName(this,"Datei öffnen","/Home");
    if(!nameAkt.isEmpty())
        model->readFromFile(nameAkt.toUtf8().constData());
}

//Dialog bei Schließen des Fensters
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (controller->cleanUndoStack())
    {
        QMessageBox::StandardButton endButton = QMessageBox::question(this, "Eulerkreis verlassen", tr("Wollen Sie wirklich ohne Speichern verlassen?"), QMessageBox::Cancel| QMessageBox::Yes| QMessageBox::Save);
        if(endButton == QMessageBox::Yes)
            event->accept();
        else if (endButton == QMessageBox::Save)
            save();
        else
            event->ignore();
    }
}

void MainWindow::on_actionBeenden_triggered()
{
    QCloseEvent *event = new QCloseEvent;
    if (controller->cleanUndoStack())
    {
        QMessageBox::StandardButton endButton = QMessageBox::question(this, "Eulerkreis verlassen", tr("Wollen Sie wirklich ohne Speichern verlassen?"), QMessageBox::Cancel| QMessageBox::Yes| QMessageBox::Save);
        if(endButton == QMessageBox::Yes)
            event->accept();
        else if (endButton == QMessageBox::Save)
            save();
        else
            event->ignore();
    }
}

//Erstelle neues DockWidget zur Anzeige der KnotenListe / Adjazenzliste
void MainWindow::on_actionKnotenliste_triggered()
{
    DockWidget* dock = new DockWidget(*model, this);
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    //Verbinde den "graphChanged" mit "updateKnotenListe"
    connect(model, &Graph::graphChanged,dock,&DockWidget::updateKnotenListe);
}

void MainWindow::on_actionBedienungsanleitung_triggered()
{
    DialogHelp hilfe;
    hilfe.exec();
}

//Lade neue Datei
void MainWindow::on_action_ffnen_triggered()
{
    load();
}

//Knoten zeichnen
void MainWindow::on_actionKnoten_zeichnen_triggered()
{
    controller->setMode(1);
}

//Knoten verbinden
void MainWindow::on_actionVerbinden_triggered()
{
    controller->setMode(2);
}

//Verschieben
void MainWindow::on_actionVerschieben_triggered()
{
    controller->setMode(3);
}

//Knoten löschen
void MainWindow::on_actionL_schen_triggered()
{
    controller->setMode(4);
}

//Speichern unter
void MainWindow::on_actionSpeichern_unter_triggered()
{
    saveAs();
}

//Speichern
void MainWindow::on_actionSpeichern_triggered()
{
    save();
}

//Animation und Eulerkreis Prüfung
void MainWindow::on_actionEulerkreis_triggered()
{
    if (model->printEulerWeg())
    {
        vector<Edge>eulerPath = model->getPath();
        emit(model->graphChanged());
        animationWidget *ani = new animationWidget(eulerPath, this);
        animationController->addAnimationswidget(*ani);
        addDockWidget(Qt::TopDockWidgetArea, ani);
    }
}

void MainWindow::on_actionNeu_triggered()
{
    QCloseEvent *event = new QCloseEvent;
    if (controller->cleanUndoStack())
    {
        QMessageBox::StandardButton endButton = QMessageBox::question(this, "Eulerkreis verlassen", tr("Wollen Sie das Dokument verwerfen?"), QMessageBox::No| QMessageBox::Yes| QMessageBox::Save);
        if(endButton == QMessageBox::Yes)
        {
            event->accept();
            if (model->getSize()!=0)
                model->clear();
        }
        else if (endButton == QMessageBox::Save)
            save();
        else
            event->ignore();
    }
}
