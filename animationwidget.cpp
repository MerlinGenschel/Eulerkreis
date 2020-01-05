#include "animationwidget.h"

#include<QSlider>
#include<QHBoxLayout>
#include<QPushButton>
#include<QSignalBlocker>

Animationswidget::Animationswidget(QWidget *parent) : QWidget(parent)
{
    geschwindigkeitSlider = new QSlider(Qt::Horizontal);
    startStopAnimation    = new QPushButton("Animiere");

    startStopAnimation->setCheckable(true);

    QHBoxLayout* layout = new QHBoxLayout(this);

    layout->addWidget(geschwindigkeitSlider);
    layout->addWidget(startStopAnimation);

    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    connect(geschwindigkeitSlider, &QSlider::valueChanged   , this, &Animationswidget::neueAnimationsgeschwindigkeit);
    connect(startStopAnimation   , &QAbstractButton::toggled, this, &Animationswidget::neuerAnimationstatus         );
}

void Animationswidget::setzeAnimationsstatus(bool v)
{
    QSignalBlocker blocker(this); // kein Signal bei Änderungen aus dem Programm heraus
    startStopAnimation->setChecked(v);
}

void Animationswidget::setzeAnimationsgeschwindigkeit(int v)
{
    QSignalBlocker blocker(this); // kein Signal bei Änderungen aus dem Programm heraus
    geschwindigkeitSlider->setValue(v);
}



//#include "animationwidget.h"
//#include "ui_animationwidget.h"
//
//#include <QSignalBlocker>
//
//
//
//
//animationWidget::animationWidget(QWidget *parent):
//QDockWidget(parent),
//ui(new Ui::AnimationWidget)
//{
//ui->setupUi(this);
//}
//
//animationWidget::~animationWidget()
//{
//    delete ui;
//}
//
//void animationWidget::eulerAnimation()
//{
//
//    qDebug()<< "bin in Euleranimation";
//
//
//    //Idee ein Timer der alle 1000 millisekunden ein signal an den slot Graph::aniChanged aufruft
//   //QTimer *timer = new QTimer(this);
//   //    connect(timer, SIGNAL(timeout()), &_Graphmodel, SLOT(&Graph::aniChanged));
//   //    timer->start(1000);
//
//
//
//
//
//    //if(!_eulerPath.empty())
//    //    if(_eulerPath[0].src == _eulerPath[_eulerPath.size()-1].dest)
//    //        qDebug()<<"Kreis";
//    //        else
//    //        qDebug()<<"Eulerweg";
//
//
//
//        //Andere Idee :
//        //Führe in einer Schleife solange _Graphmodel.newEdgeToColor aus bis alle Kanten im Eulerweg durchsind
//
//        //Leider unelegant und funktioniert auch nicht richtig
//   //Debug()<<_Graphmodel.getPath().size();
//   //
//   //while(_Graphmodel.newEdgeToColor())
//   //{
//   //    //qDebug()<<"edgetoColor="<<_Graphmodel.edgeToColor;
//   //    //qDebug()<<"edgetoColor="<<_Graphmodel.edgeToColor<<" now sleep";
//   //    QThread::msleep(500);
//   //}
//   //qDebug()<<"fertig";
//        //for(int i = 0;i<_eulerPath.size();i++)
//        //    qDebug() <<_eulerPath[i].src << " "<<_eulerPath[i].dest;
//
//
//}
//
//void animationWidget::setAnimationStatus(bool)
//{
//    QSignalBlocker block(this);
//    ui->pushButton -> setChecked(true);
//}
//
//void animationWidget::setAnimationSpeed(int v)
//{
//    QSignalBlocker block(this);
//    ui->horizontalSlider->setValue(v);
//}
//
