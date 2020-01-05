#ifndef ANIMATIONSCONTROLLER_H
#define ANIMATIONSCONTROLLER_H


#include <QObject>

class Graph;
class Animationswidget;

class Animationspresenter: public QObject
{
    Q_OBJECT

    Graph& modell;

    double geschwindigkeit = 0.01;
    const int maxSlider = 100;
    const double maxGeschwindigkeit = 1./50.;

    // Event für die Animation, analog zu der alten Implementierung
    void timerEvent(QTimerEvent* event) override;

    int animationstimer = 0; // TimerID für die Animation

public:
    Animationspresenter(Graph& modell, QObject *parent = nullptr);

    void addAnimationswidget(Animationswidget& ansicht);

private slots:
    void setzeAnimationsstatus(bool aktiv);
    void setzeGeschwindigkeit(int wert);

signals:
    void neuerAnimationsstatus(bool aktiv);
    void neueAnimationsgeschwindigkeit(int val);
};

#endif // ANIMATIONSCONTROLLER_H


//#ifndef ANIMATION_H
//#define ANIMATION_H
//
//#include <QObject>
//#include <QUndoStack>
//#include<QColor>
//#include"animationwidget.h"
//class Edge;
//class paint;
//class Graph;
//class animation:public QObject
//{
//    Q_OBJECT
//
//    Graph &model;
//    paint &view;
//    QUndoStack *undoStack =nullptr;
//
//    int aniEdge=0;
//
//    double speed = 0.01;
//    const int maxSlider = 100;
//    const double maxSpeed = 1./50.;
//    void timerEvent(QTimerEvent* event) override;
//    int animationtimer =0;
//    std::vector<QColor>color;
//
//public:
//   animation(Graph &model, paint &view,QUndoStack *undoStack, QObject *parent);
//
//   void addAnimationswidget(animationWidget &ansicht);
//
//private slots:
//
//    void setAnimationStatus(bool active);
//    void setSpeed(int val);
//public:
//signals:
//    void newAnimationStatus(bool active);
//    void newAnimationSpeed(int val);
//    void animationChanged();
//};
//
//#endif // ANIMATION_H
