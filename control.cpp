#include "control.h"
#include "Graph.h"
#include "paint.h"

#include <QDebug>

#include <QEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QApplication>

#include "commands/moveCommand.h"

control::control(Graph &model, paint& view, QUndoStack *undoStack, QObject *parent)
    : QObject(parent)
    , model(model)
    , view(view)
    , undoStack(undoStack)
{
    view.installEventFilter(this);
}

// Eventfilter um die Ereignise von der Ansicht abzufangen : MVC: die Ereignise werden von der Steuerung verarbeitet
bool control::eventFilter(QObject* /*watched*/, QEvent* event)
{
    switch(event->type()) // Bestimmen des Ereignistyps
    {
        // relevante Ereignistypen behandeln:
        // cast auf speziellen Typ durchführen und die speziellen Event-Methoden aufrufen
        case QEvent::MouseButtonPress:
            mousePressEvent(dynamic_cast<QMouseEvent*>(event));
            break;
/*        case QEvent::MouseMove:
            mouseMoveEvent(dynamic_cast<QMouseEvent*>(event));
            break;*/
        default:
            return false;
    }
    return event->isAccepted();
}

// Methoden analog zu dem alten QudarateWidget.
void control::mousePressEvent(QMouseEvent* event)
{
    const double breite = view.width();
    const double hoehe  = view.height();
    double _x =event->x()/breite;
    double _y =event->y()/hoehe;



    //STRG Taste zum Verbinden
        //std::cout << "Test";

       if(event->button() == Qt::LeftButton && QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))  //VerbindenModus
        {
            //qDebug() << "Verbinden";
            if(model.clickedOnNode(_x,_y)!=-1)
            {
                //an methode in Graph delegieren, dort auch signal aussenden
                model.toConnect[NullOderEins] = model.clickedOnNode(_x,_y);
                control::NullOderEins = (NullOderEins+1)%2;
                emit(model.graphChanged());
            }
            //qDebug() << toConnect[0];
            //qDebug() << toConnect[1];
            if((model.toConnect[0]!=-1  && model.toConnect[1]!=-1))
            {
                model.addEdge(model.toConnect[0],model.toConnect[1]);
                model.toConnect[0]=-1;
                model.toConnect[1]=-1;

            }
            //undoStack mit einbinden Isi

        }
   else if(event->button() == Qt::LeftButton)  //ZeichnenModus
    {
        //undoStack einfügen Isi
        model.addNode(_x,_y);
    }


   else if (event->button() == Qt::RightButton && event->modifiers() & Qt::Key_Shift)
    {
           int index = model.clickedOnNode(_x,_y);
           if (index != -1)
           {
           QPointF newPos(event->x()/static_cast<double>(view.width())
                          , event->y()/static_cast<double>(view.height()));

           undoStack->push(new moveCommand(&model, activeNode, newPos));
           }
           //verschieben--> Alexej


    }


    else if(event->button() == Qt::RightButton)  //Löschen Modus
    {
           int index = model.clickedOnNode(_x,_y);
           if (index != -1)
                   model.removeNode(index);
           //undoStack Isi
    }


}


/*
void control::mouseMoveEvent(QMouseEvent* event)
{
    const double breite = view.width();
    const double hoehe  = view.height();
    double _x =event->x()/breite;
    double _y =event->y()/hoehe;
    if (event->button() == Qt::RightButton && QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))
    {
        int index = model.clickedOnNode(_x,_y);
        if (index != -1)
        {
            QPointF newPos(event->x()/static_cast<double>(view.width())
                         , event->y()/static_cast<double>(view.height()));

            undoStack->push(new moveCommand(&model, activeNode, newPos));
        }
    //verschieben--> Alexej
    //undoStack Isi
    }
}
*/
