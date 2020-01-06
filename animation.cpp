#include "animation.h"
#include "animationwidget.h"
#include "Graph.h"


#include<QPushButton>


animation::animation(Graph &modell, QUndoStack *undoStack, QObject *parent)
    :QObject(parent)
    ,modell(modell)
    ,undoStack(undoStack)
{

}

void animation::setzeAnimationsstatus(bool aktiv)
{
    if(aktiv && animationstimer == 0) // timer soll gesetzt werden und er ist nicht aktiv
        animationstimer = startTimer(500);
    if(!aktiv && animationstimer != 0) // timer soll gelöscht werden und er ist aktiv
    {
        killTimer(animationstimer);
        animationstimer = 0;
    }

    neuerAnimationsstatus(animationstimer != 0);
}

void animation::setzeGeschwindigkeit(int wert)
{
    geschwindigkeit = static_cast<double>(wert)/maxSlider*maxGeschwindigkeit;
    neueAnimationsgeschwindigkeit(wert);
}
void animation::timerEvent(QTimerEvent *event)
{

        modell.newEdgeToColor();
}
void animation::addAnimationswidget(animationWidget& ansicht)
{
    // Initalwerte setzen
    ansicht.setzeAnimationsgeschwindigkeit(static_cast<int>(geschwindigkeit*maxSlider/maxGeschwindigkeit));
    ansicht.setzeAnimationsstatus(animationstimer != 0);

    // eingehende Verbindungen
    connect(&ansicht, &animationWidget::neuerAnimationstatus         , this, &animation::setzeAnimationsstatus);
    connect(&ansicht, &animationWidget::neueAnimationsgeschwindigkeit, this, &animation::setzeGeschwindigkeit );

    // ausgehende Verbindungen
    connect(this, &animation::setzeAnimationsstatus, &ansicht, &animationWidget::neuerAnimationstatus         );
    connect(this, &animation::setzeGeschwindigkeit , &ansicht, &animationWidget::neueAnimationsgeschwindigkeit);
}
