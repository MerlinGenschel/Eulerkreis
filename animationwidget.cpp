#include "animationwidget.h"
#include "ui_animationwidget.h"

#include <QSignalBlocker>

animationWidget::animationWidget(vector<Edge>eulerPath, QWidget *parent) :
    QDockWidget(parent),_eulerPath(eulerPath),
    ui(new Ui::AnimationWidget)
{
    ui->setupUi(this);
}

animationWidget::~animationWidget()
{
    delete ui;
}

void animationWidget::eulerAnimation()
{
    qDebug()<< "bin in Euleranimation";
    if(!_eulerPath.empty())
    {
    if(_eulerPath[0].src == _eulerPath[_eulerPath.size()-1].dest)
            qDebug()<<"Kreis";
        else
            qDebug()<<"Eulerweg";
    
        //for(int i = 0;i<_eulerPath.size();i++)
        //    qDebug() <<_eulerPath[i].src << " "<<_eulerPath[i].dest;
  
    }
}

void animationWidget::setAnimationStatus(bool)
{
    QSignalBlocker block(this);
    ui->pushButton -> setChecked(true);
}

void animationWidget::setAnimationSpeed(int v)
{
    QSignalBlocker block(this);
    ui->horizontalSlider->setValue(v);
}
