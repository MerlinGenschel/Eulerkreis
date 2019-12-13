#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include<QPolygonF>
#include<QPen>

class QMouseEvent;
class QKeyEvent;


class paint;    //View
class Graph;    //Modell

class control : public QObject
{
    Q_OBJECT

    paint& view;
    Graph& model;


    // Methoden um die Events zu handhaben, sie werden durch eventFilter und nicht automatisch aufgerufen
    // Da die Basisklase QObjekt und nicht QWidget ist, ist es auch keine Überschreibung aus der Basisklasse,
    // sie könnten auch einen anderen Namen haben
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);

    std::size_t activeNode = std::numeric_limits<std::size_t>::max(); // Index des angeklickten/ausgewählten Quadrats

   //bool linienDickeSkalieren = false;
public:
//*** Konstruktoren ***//
    control(Graph& model, paint& view,QObject *parent=nullptr);

    bool eventFilter(QObject* watched, QEvent* event) override;



};

#endif // CONTROL_H
