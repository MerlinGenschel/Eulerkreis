#ifndef PAINT_H
#define PAINT_H

#include <QWidget>
#include<vector>
#include<limits>
//Datenstruktur für die Kanten
class  Edge;
class Graph;

class paint : public QWidget
{
    Q_OBJECT
    // Für die Zeichenfunktion wird das Modell benötigt (Zugriff auf die Quadrate) -> Speicherung einer Referenz auf das Modell
    const Graph& model;

public:
   paint(const Graph& model,QWidget* parent = nullptr);

protected:
   void paintEvent(QPaintEvent* event) ;





public slots:
   void animationEvent();



//signals:
//    void newAnimationStatus(bool active);
//    void newAnimationSpeed(int val);
};

#endif // PAINT_H
