#include "animationwidget.h"
#include "ui_animationwidget.h"

#include <QSignalBlocker>

animationWidget::animationWidget(/*Graph &Graphmodel, */QWidget *parent) :
    QDockWidget(parent),/*Graphmodel(Graphmodel),*/
    ui(new Ui::AnimationWidget)
{
    ui->setupUi(this);
}

animationWidget::~animationWidget()
{
    delete ui;
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
