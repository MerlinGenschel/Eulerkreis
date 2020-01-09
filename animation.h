#ifndef ANIMATION_H
#define ANIMATION_H

#include <QObject>
#include <QUndoStack>

class Graph;
class animationWidget;
class animation:public QObject
{
    Q_OBJECT

    Graph &modell;
    QUndoStack *undoStack =nullptr;

    double geschwindigkeit = 0.01;
    const int maxSlider = 100;
    const double maxGeschwindigkeit = 1./50.;
    void timerEvent(QTimerEvent* /*event*/) override;
    int animationstimer =0;

public:
   animation(Graph &modell, QUndoStack *undoStack, QObject *parent = nullptr);
   void addAnimationswidget(animationWidget& ansicht);
private slots:

   void setzeAnimationsstatus(bool aktiv);
   void setzeGeschwindigkeit(int wert);
signals:
    void neuerAnimationsstatus(bool aktiv);
    void neueAnimationsgeschwindigkeit(int val);
};

#endif // ANIMATION_H
