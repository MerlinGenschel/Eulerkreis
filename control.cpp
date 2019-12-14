#include "control.h"
#include "Graph.h"
#include "paint.h"

#include <QDebug>

#include<QEvent>
#include<QMouseEvent>
#include<QKeyEvent>
#include <QApplication>

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
            return false;
            break;
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
            qDebug() << "Verbinden";
            toConnect[NullOderEins] = model.clickedOnNode(_x,_y);
            control::NullOderEins = (NullOderEins+1)%2;
            qDebug() << toConnect[0];
            qDebug() << toConnect[1];
            if((toConnect[0]!=-1  && toConnect[1]!=-1))
            {
                model.addEdge(toConnect[0],toConnect[1]);
            }

        }
   else if(event->button() == Qt::LeftButton)  //ZeichnenModus
    {

        model.addNode(_x,_y);
    }


   else if (event->button() == Qt::RightButton && QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))
    {
           //verschieben--> Alexej
    }
   else if(event->button() == Qt::RightButton)
    {
           //Löschen
    }


}
