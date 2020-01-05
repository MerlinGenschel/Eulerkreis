#include "animation.h"

#include<QPushButton>
#include<QSlider>

#include"Graph.h"
#include"animationwidget.h"

Animationspresenter::Animationspresenter(Graph& modell, QObject *parent)
    : QObject(parent)
    , modell(modell)
{
}

void Animationspresenter::setzeAnimationsstatus(bool aktiv)
{
    if(aktiv && animationstimer == 0) // timer soll gesetzt werden und er ist nicht aktiv
        animationstimer = startTimer(1000);
    if(!aktiv && animationstimer != 0) // timer soll gelöscht werden und er ist aktiv
    {
        killTimer(animationstimer);
        animationstimer = 0;
    }

    neuerAnimationsstatus(animationstimer != 0);
}

void Animationspresenter::setzeGeschwindigkeit(int wert)
{
    geschwindigkeit = static_cast<double>(wert)/maxSlider*maxGeschwindigkeit;
    neueAnimationsgeschwindigkeit(wert);
}

void Animationspresenter::timerEvent(QTimerEvent* /*event*/)
{
    // Timerevent für die Animation der Rechtecke
    //qDebug()<< "Im TimerEvent";
    modell.newEdgeToColor();
}

void Animationspresenter::addAnimationswidget(Animationswidget& ansicht)
{
    // Initalwerte setzen
    ansicht.setzeAnimationsgeschwindigkeit(static_cast<int>(geschwindigkeit*maxSlider/maxGeschwindigkeit));
    ansicht.setzeAnimationsstatus(animationstimer != 0);

    // eingehende Verbindungen
    connect(&ansicht, &Animationswidget::neuerAnimationstatus         , this, &Animationspresenter::setzeAnimationsstatus);
    connect(&ansicht, &Animationswidget::neueAnimationsgeschwindigkeit, this, &Animationspresenter::setzeGeschwindigkeit );

    // ausgehende Verbindungen
    connect(this, &Animationspresenter::setzeAnimationsstatus, &ansicht, &Animationswidget::neuerAnimationstatus         );
    connect(this, &Animationspresenter::setzeGeschwindigkeit , &ansicht, &Animationswidget::neueAnimationsgeschwindigkeit);
}


//#include "animation.h"
//#include "Graph.h"
//#include "paint.h"
//
//#include<QPushButton>
//
//
//animation::animation(Graph &model, paint &view,QUndoStack *undoStack, QObject *parent)
//    :QObject(parent)
//    ,model(model)
//    ,view(view)
//    ,undoStack(undoStack)
//{
//
//}
//
//void animation::addAnimationswidget(animationWidget &ansicht)
//{
//        ansicht.setAnimationStatus(true);
//        ansicht.setAnimationSpeed(1);
//
//
//        connect(this, &animation::animationChanged, &view, QOverload<>::of(&paint::update));
//
//        qDebug()<<"addAnimationsWidget";
//
//
//
//        // eingehende Verbindungen
//            connect(&ansicht, &animationWidget::newAnimationStatus        , this, &animation::setAnimationStatus);
//            connect(&ansicht, &animationWidget::newAnimationSpeed, this, &animation::setSpeed );
//            //
//            //// ausgehende Verbindungen
//            connect(this, &animation::setAnimationStatus, &ansicht, &animationWidget::newAnimationStatus       );
//            connect(this, &animation::setSpeed , &ansicht, &animationWidget::newAnimationSpeed);
//
//            //emit(ansicht.animationChanged());
//        //// Initalwerte setzen
//        //ansicht.setzeAnimationsgeschwindigkeit(static_cast<int>(geschwindigkeit*maxSlider/maxGeschwindigkeit));
//        //ansicht.setzeAnimationsstatus(animationstimer != 0);
//        //
//        //// eingehende Verbindungen
//        //connect(&ansicht, &Animationswidget::neuerAnimationstatus         , this, &Animationspresenter::setzeAnimationsstatus);
//        //connect(&ansicht, &Animationswidget::neueAnimationsgeschwindigkeit, this, &Animationspresenter::setzeGeschwindigkeit );
//        //
//        //// ausgehende Verbindungen
//        //connect(this, &Animationspresenter::setzeAnimationsstatus, &ansicht, &Animationswidget::neuerAnimationstatus         );
//        //connect(this, &Animationspresenter::setzeGeschwindigkeit , &ansicht, &Animationswidget::neueAnimationsgeschwindigkeit);}
//}
//void animation::setAnimationStatus(bool active)
//{
//    //Timer soll gesetzt werden und er ist nicht aktiv
//    if (active && animationtimer ==0)
//        animationtimer = startTimer(500);
//    //Timer soll gelöscht werden und er ist aktiv
//    if(!active && animationtimer!=0)
//    {
//        killTimer(animationtimer);
//        animationtimer=0;
//    }
//    newAnimationStatus(animationtimer!=0);
//}
//
//void animation::setSpeed(int val)
//{
//    speed= static_cast<double>(val) /maxSlider*maxSpeed;
//    newAnimationSpeed(val);
//}
//void animation::timerEvent(QTimerEvent *event)
//{
//    //Edge edge = model.getPath().at(model.edgeToColor);
//
//    qDebug()<< "timerEvent";
//    //emit(animationChanged());
//    //timerevent für färben der kanten
//    //model.edgeToColor++;
//}


