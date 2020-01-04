#ifndef ANIMATION_H
#define ANIMATION_H

#include <QObject>
#include <QUndoStack>
#include<QColor>

class Graph;
class animation:public QObject
{
    Q_OBJECT

    Graph &model;
    QUndoStack *undoStack =nullptr;

    double speed = 0.01;
    const int maxSlider = 100;
    const double maxSpeed = 1./50.;
    void timerEvent(QTimerEvent* event) override;
    int animationtimer =0;
    std::vector<QColor>color;

public:
   animation(Graph &model, QUndoStack *undoStack, QObject *parent = nullptr);

private slots:

    void setAnimationStatus(bool active);
    void setSpeed(int val);
signals:
    void newAnimationStatus(bool active);
    void newAnimationSpeed(int val);
};

#endif // ANIMATION_H
