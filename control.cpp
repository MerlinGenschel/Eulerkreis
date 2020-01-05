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
            if(true)
            {
                const double width   = view.width();
                const double height  = view.height();
                _selectedNode = model.clickedOnNode(dynamic_cast<QMouseEvent*>(event)->x()/width
                                                  , dynamic_cast<QMouseEvent*>(event)->y()/height);
            }
            // verbinden: Modus verbinden + Linksklick
            if (dynamic_cast<QMouseEvent*>(event)->button() == Qt::LeftButton && mod == Mode::verbinden)
                connect(dynamic_cast<QMouseEvent*>(event));
            // Knoten hinzufügen: Mous Knoten hinzufügen + LinksKnick
            else if(dynamic_cast<QMouseEvent*>(event)->button() == Qt::LeftButton && mod == Mode::zeichnen)
                add(dynamic_cast<QMouseEvent*>(event));
            // löschen: Modus löschen + Linksklick ODER Modus Knoten hinzufügen + Rechtsklick
            else if ((dynamic_cast<QMouseEvent*>(event)->button() == Qt::RightButton && mod == Mode::zeichnen)
                     || (dynamic_cast<QMouseEvent*>(event)->button() == Qt::LeftButton && mod == Mode::loeschen))
                remove(dynamic_cast<QMouseEvent*>(event));
            break;
        case QEvent::MouseMove:
            if (dynamic_cast<QMouseEvent*>(event)->buttons() & Qt::LeftButton && mod == Mode::verschieben)
                move(dynamic_cast<QMouseEvent*>(event));
            break;
        default:
            return false;
    }
    return event->isAccepted();
}

// Knoten hinzufügen
void control::add(QMouseEvent* event)
{
    const double width   = view.width();
    const double height  = view.height();

    QPointF pos(event->x()/width
              , event->y()/height);

    undoStack->push(new addNodeCommand(&model, pos));
}

// Knoten löschen
void control::remove(QMouseEvent* event)
{
    const double width   = view.width();
    const double height  = view.height();

    int index = model.clickedOnNode(event->x()/width
                                  , event->y()/height);
    if (activeNodeValid(event))
        undoStack->push(new removeNodeCommand(&model, index));
}

// Knoten verbinden
void control::connect(QMouseEvent* event)
{
    const double width   = view.width();
    const double height  = view.height();

    if(activeNodeValid(event))
    {
        model.toConnect[NullOderEins] = model.clickedOnNode(event->x()/width
                                                          , event->y()/height);
        control::NullOderEins = (NullOderEins+1)%2;
    }
    if(model.toConnect[0] != -1  && model.toConnect[1] != -1)
    {
        undoStack->push(new connectCommand(&model, model.toConnect[0], model.toConnect[1]));
        model.toConnect[0] = -1;
        model.toConnect[1] = -1;
    }
    emit(model.graphChanged());
}

// Knoten verschieben
void control::move(QMouseEvent* event)
{
    if (activeNodeValid(event))
    {
        QPointF newPos(event->x()/static_cast<double>(view.width())
                     , event->y()/static_cast<double>(view.height()));

        undoStack->push(new moveCommand(&model, _selectedNode, newPos));
    }
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

//Clean-Status für UndoStack setzen
void control::deleteUndoStack()
{
    undoStack->setClean();
}

//Prüfe den Clean-Status des UndoStack
bool control::cleanUndoStack() const
{
    if (undoStack->isClean() == false)
        return true;
    else
        return false;
}

// Mous setzten
void control::setMode(int m)
{
    if(m == 1)
        mod = Mode::zeichnen;
    else if(m == 2)
        mod = Mode::verbinden;
    else if(m == 3)
        mod = Mode::verschieben;
    else if(m == 4)
        mod = Mode::loeschen;
}
