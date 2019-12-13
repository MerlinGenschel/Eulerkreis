#include "control.h"
#include "Graph.h"
#include "paint.h"

#include<QEvent>
#include<QMouseEvent>
#include<QKeyEvent>



// Eventfilter um die Ereignise von der Ansicht abzufangen : MVC: die Ereignise werden von der Steuerung verarbeitet
control::control(Graph &model, paint& view, QObject *parent)
    :QObject(parent), model(model),view(view)
{
    view.installEventFilter(this);
}

bool control::eventFilter(QObject* /*watched*/, QEvent* event)
{
    switch(event->type()) // Bestimmen des Ereignistyps
    {
        // relevante Ereignistypen behandeln:
        // cast auf speziellen Typ durchführen und die speziellen Event-Methoden aufrufen
        case QEvent::MouseButtonPress:
            mousePressEvent(dynamic_cast<QMouseEvent*>(event));
            break;
        case QEvent::MouseMove:
            break;
        default:
            return false;
    }
    return event->isAccepted();
}


// Methoden analog zu dem alten QudarateWidget.
void control::mousePressEvent(QMouseEvent* event)
{
    cout << "maus geklickt" <<endl;
    const double breite = view.width();
    const double hoehe  = view.height();

    if(event->button() == Qt::LeftButton) // Rechte Maustaste: Ein Quadrat einfügen;
    {
        //wenn "k" gedrückt ist...
        double _x =event->x()/breite;
        double _y =event->y()/hoehe;
        model.addNode(_x,_y);

     //Es muss noch geupdated werden.
        //undoStack->push(new HinzufuegenBefehl(&modell, pos));
        //aktivesQuadrat = modell.anzahlQuadrate() - 1; // neues Quadrat auswählen = letzte Quadrat
    }
    else
    {
        // Ein Qudrat finden ist in das Modell ausgelagert, deswegen nur die Modell-Methode aufrufen
        //aktivesQuadrat = modell.findeQuadrat(event->pos(), ansicht.size());
    }
}
