#include "control.h"
#include "Graph.h"
#include "paint.h"

#include <QDebug>

#include <QEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QApplication>

#include "commands/moveCommand.h"
#include "commands/addNodeCommand.h"
#include "commands/removeNodeCommand.h"
#include "commands/connectCommand.h"

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
            if(dynamic_cast<QMouseEvent*>(event)->button() == Qt::LeftButton)
            {
                add(dynamic_cast<QMouseEvent*>(event));
                break;
            }
            else if (dynamic_cast<QMouseEvent*>(event)->button() == Qt::RightButton)
            {
                remove(dynamic_cast<QMouseEvent*>(event));
                break;
            }
            else if (dynamic_cast<QMouseEvent*>(event)->button() == Qt::LeftButton && QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))
            {
                connect(dynamic_cast<QMouseEvent*>(event));
                break;
            }
        case QEvent::MouseMove:
            mouseMoveEvent(dynamic_cast<QMouseEvent*>(event));
            break;
        case QEvent::KeyPress:
            keyPressEvent(dynamic_cast<QKeyEvent*>(event));
            break;
        default:
            return false;
    }
    return event->isAccepted();
}

//
void control::add(QMouseEvent* event)
{
    const double width = view.width();
    const double height  = view.height();

    // Knoten Hinzufügen
    //if(event->button() == Qt::RightButton) // Rechte Maustaste: Einen Knoten einfügen
    //{
        QPointF pos(event->x()/width
                  , event->y()/height);
        undoStack->push(new addNodeCommand(&model, pos));
    //}
}

void control::remove(QMouseEvent* event)
{
//*
    //else if(QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier) && event->button() == Qt::LeftButton)  //Löschen Modus
    //{
    const double width = view.width();
    const double height  = view.height();

        int index = model.clickedOnNode(event->x()/width
                                      , event->y()/height);
        if (activeNodeValid(event))
        {
            undoStack->push(new removeNodeCommand(&model, index));
            //activeNode = model.getSize() -1;
        }
    //}
//*/
}
//*
//else if(event->button() == Qt::LeftButton && QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))  //VerbindenModus
void control::connect(QMouseEvent* event)
{
    const double width = view.width();
    const double height  = view.height();
        //qDebug() << "Verbinden";
        if(activeNodeValid(event))
        {
            //an methode in Graph delegieren, dort auch signal aussenden
            model.toConnect[NullOderEins] = model.clickedOnNode(event->x()/width
                                                                , event->y()/height);
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
}
//*/
/*
    else
    {
        activeNode = model.clickedOnNode(event->pos().x()
                                         , event->pos().y());
    }
//*/


// Knoten verschieben
void control::mouseMoveEvent(QMouseEvent* event)
{
//*
    if (activeNodeValid(event))
    {
        int index = model.clickedOnNode(event->pos().x()
                                         , event->pos().y());

        QPointF newPos(event->x()/static_cast<double>(view.width())
                     , event->y()/static_cast<double>(view.height()));

        undoStack->push(new moveCommand(&model, index, newPos));
    }
//*/
}

void control::keyPressEvent(QKeyEvent* event)
{
/*
    if(!activeNodeValid(event)) // kein aktives Quadrat, Tastendrücke müssen nicht beachtet werden (Achtung: hierbei werden Tastendrücke weitergeleitet die ansonsten abgefangen worden wären)
        return event->ignore(); // Weiterleitung der Tastendrücke an QWidget und damit an die übergeordneten Widgets

    switch(event->key()) // Aktionen für die Tasten aufstellen
    {
        case Qt::Key_Delete:
            model.removeNode(activeNode); // Modell anweisen, das Qudarat zu löschen
            activeNode = std::numeric_limits<std::size_t>::max(); // aktives Quadrad auf ungültigen Wert setzen
            break;
        default: // keine Taste die bearbeitet wird -> Aufruf der Methode vom Elternobjekt
            return event->ignore();
    }
*/
}


// Prüfen um der aktueller Knoten-Index gültig ist
bool control::activeNodeValid(QMouseEvent* event) const
{
    const double width   = view.width();
    const double height  = view.height();

    int index = model.clickedOnNode(event->x()/width
                                    , event->y()/height);
    if (index != -1)
        return true;
}













 /*   //STRG Taste zum Verbinden
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
*/
