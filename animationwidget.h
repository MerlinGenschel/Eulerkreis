#ifndef ANIMATIONWIDGET_H
#define ANIMATIONWIDGET_H
#include <QtGui>
#include <QtCore>
#include <QDockWidget>
#include <QStringListModel>

#include "Graph.h"

namespace Ui {
class AnimationWidget;
}

class animationWidget : public QDockWidget
{
    Q_OBJECT
private:
    Ui::AnimationWidget *ui;
    QStringListModel* model;
    vector<Edge>_eulerPath;

public:
    explicit animationWidget(vector<Edge> eulerPath, QWidget *parent = nullptr);
    ~animationWidget();

    void fillAnimationWidget();
public slots:
    void setzeAnimationsstatus(bool);
    void setzeAnimationsgeschwindigkeit(int);
signals:
    void neuerAnimationstatus(bool);
    void neueAnimationsgeschwindigkeit(int);
//private slots:
   // void on_horizontalSlider_valueChanged(int value);
private slots:
    void on_pushButton_clicked(bool checked);
};

#endif // ANIMATIONWIDGET_H
