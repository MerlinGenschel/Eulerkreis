#include "animation.h"
#include "Graph.h"


#include<QPushButton>


animation::animation(Graph &model, QUndoStack *undoStack, QObject *parent)
    :QObject(parent)
    ,model(model)
    ,undoStack(undoStack)
{

}

void animation::setAnimationStatus(bool active)
{
    //Timer soll gesetzt werden und er ist nicht aktiv
    if (active && animationtimer ==0)
        animationtimer = startTimer(50);
    //Timer soll gelöscht werden und er ist aktiv
    if(!active && animationtimer!=0)
    {
        killTimer(animationtimer);
        animationtimer=0;
    }
    newAnimationStatus(animationtimer!=0);
}

void animation::setSpeed(int val)
{
    speed= static_cast<double>(val) /maxSlider*maxSpeed;
    newAnimationSpeed(val);
}
void animation::timerEvent(QTimerEvent *event)
{

    //timerevent für färben der kanten
}


