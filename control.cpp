#include "control.h"
#include "graph_net.h"

#include<QEvent>
#include<QMouseEvent>
#include<QKeyEvent>

control::control()
{

}

// Eventfilter um die Ereignise von der Ansicht abzufangen : MVC: die Ereignise werden von der Steuerung verarbeitet
bool control::eventFilter(QObject* /*watched*/, QEvent* event)
{
    switch(event->type()) // Bestimmen des Ereignistyps
    {
        // relevante Ereignistypen behandeln:
        // cast auf speziellen Typ durchführen und die speziellen Event-Methoden aufrufen
        case QEvent::MouseButtonPress:
            zeichnen(dynamic_cast<QMouseEvent*>(event));
            break;
        case QEvent::MouseMove:
            verschieben(dynamic_cast<QMouseEvent*>(event));
            break;
        default:
            return false;
    }
    return event->isAccepted();
}

void control::zeichnen(QMouseEvent *event)
{

}

void control::verschieben(QMouseEvent *event)
{

}
