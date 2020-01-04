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

    void eulerAnimation();

public slots:
    void setAnimationStatus(bool);
    void setAnimationSpeed(int);
signals:
    void newAnimationStatus(bool);
    void newAnimationSpeed(int);
};

#endif // ANIMATIONWIDGET_H
