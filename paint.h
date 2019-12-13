#ifndef PAINT_H
#define PAINT_H

#include <QWidget>
#include<vector>
#include<limits>

class Graph;

class paint : public QWidget
{
    Q_OBJECT
    // Für die Zeichenfunktion wird das Modell benötigt (Zugriff auf die Quadrate) -> Speicherung einer Referenz auf das Modell
    const Graph& model;

public:
   paint(const Graph& model,QWidget* parent = nullptr);

protected:
   void paintEvent(QPaintEvent* event) override;



public:
};

#endif // PAINT_H
