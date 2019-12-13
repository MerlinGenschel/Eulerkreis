#include "paint.h"
#include "Graph.h"

#include<cmath>

#include<QPaintEvent>
#include<QPainter>

#include<QRectF>
#include<QMouseEvent>

paint::paint(const Graph& model,QWidget *parent)
    : QWidget(parent),model(model)
{
    setFocusPolicy(Qt::StrongFocus);

    // wenn sich beim Modell was geändert hat, soll neu gezeichnet werden (Analog zu MVC, die Ansicht beobachtet das Modell auf Änderungen)
    connect(&model, &Graph::graphChanged, this, QOverload<>::of(&paint::update));
}



// Bekante Zeichenfunktion
void paint::paintEvent(QPaintEvent* /*event*/)
{
    const double breite = width();
    const double hoehe  = height();

    QPainter p(this);

    //hier werden bisher NUR die Knoten gezeichnet
    //20 cm Radius bisher Hardkodiert
    for(int i=0; i< model.getSize();i++) // statt des direkten Zugriffs erfolgt hier jetzt eine Nachfrage beim Modell, dieses liefert die aktuelle Quadrateliste
    {
        p.setBrush(QBrush(Qt::black));
        p.drawEllipse(static_cast<int>(model.getCoord(i).first * breite)
                 , static_cast<int> (model.getCoord(i).second * hoehe)
                 , 20
                 , 20);
    }
}
