#ifndef ANIMATIONSWIDGET_H
#define ANIMATIONSWIDGET_H

#include <QWidget>

class QSlider;
class QPushButton;


// Passive Ansicht in MVP-Muster
class Animationswidget : public QWidget
{
    Q_OBJECT

    QSlider* geschwindigkeitSlider = nullptr;
    QPushButton* startStopAnimation = nullptr;
public:
    explicit Animationswidget(QWidget *parent = nullptr);


public slots:
    void setzeAnimationsstatus(bool);
    void setzeAnimationsgeschwindigkeit(int);

signals:
    void neuerAnimationstatus(bool);
    void neueAnimationsgeschwindigkeit(int);
};

#endif // ANIMATIONSWIDGET_H



//#ifndef ANIMATIONWIDGET_H
//#define ANIMATIONWIDGET_H
//#include <QtGui>
//#include <QtCore>
//#include <QDockWidget>
//#include <QStringListModel>
//
//#include "Graph.h"
//#include "paint.h"
//#include "QTimer"
//
//namespace Ui {
//class AnimationWidget;
//}
//
//
//class animationWidget : public QDockWidget
//{
//    Q_OBJECT
//
//
//private:
//    Ui::AnimationWidget *ui;
//    //QStringListModel* model;
//    //vector<Edge>_eulerPath;
//    //paint& _view;
//    //const Graph& _Graphmodel;
//public:
//    explicit animationWidget(QWidget *parent = nullptr);
//    ~animationWidget();
//
//    void eulerAnimation();
//
//public slots:
//    void setAnimationStatus(bool);
//    void setAnimationSpeed(int);
//signals:
//    void newAnimationStatus(bool);
//    void newAnimationSpeed(int);
//    void animationChanged();
//};
//
//#endif // ANIMATIONWIDGET_H
