#include "paint.h"
#include "Graph.h"

#include<cmath>

#include<QPaintEvent>
#include<QPainter>

#include<QRectF>
#include<QMouseEvent>
#include <vector>
#include <QDebug>
#include <QTime>
#include <QThread>

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

        p.drawEllipse(static_cast<int>(model.getCoord(i).first * breite-10)
                 , static_cast<int> (model.getCoord(i).second * hoehe-10)
                 , 20
                 , 20);

    }

    //markierte Knoten in Rot
    for (int j = 0;j< 2;j++)
    {
        p.setBrush(QBrush(Qt::red));
        if (model.toConnect[j] != -1)
            p.drawEllipse(static_cast<int>(model.getCoord(model.toConnect[j]).first * breite-10)
                 , static_cast<int> (model.getCoord(model.toConnect[j]).second * hoehe-10)
                 , 20
                 , 20);

    }
    //Kanten
    for(size_t i=0; i < model.getSize();i++)
        {
            p.setPen(QPen(Qt::black) );
            vector<int> edges = model.getEdges(i);
            size_t numEdges = edges.size();

            for(size_t k = 0; k< numEdges;k++)
            {
            //qDebug() << "kante zwischen " << i << " und " << k;
            p.drawLine(static_cast<int>(model.getCoord(i).first * breite)
                        , static_cast<int> (model.getCoord(i).second * hoehe)
                        , static_cast<int>(model.getCoord(edges[k]).first * breite)
                        , static_cast<int> (model.getCoord(edges[k]).second * hoehe));
            }

        }
    /*

    if(!model.getPath().empty())
    {
        p.setPen(QPen(Qt::green));
        vector<Edge> path =model.getPath();
        qDebug()<<"jka";
        for(int i = 0;i<path.size();i++)
        {
            p.drawLine(static_cast<int>(model.getCoord(path[i].src).first * breite)
                        , static_cast<int> (model.getCoord(path[i].src).second * hoehe)
                        , static_cast<int>(model.getCoord(path[i].dest).first * breite)
                        , static_cast<int> (model.getCoord(path[i].dest).second * hoehe));
    qDebug()<<i;

            QThread::msleep(500);       //"Schlafe" 500msec - sehr unelegant, nur vom prizip her
        }
        }
        */
}

void paint::animationEvent(QPaintEvent *event,int i)
{
    const double breite = width();
    const double hoehe  = height();

    vector<Edge> path = model.getPath();
    QPainter p(this);
    p.setPen(QPen(Qt::green));
    p.drawLine(static_cast<int>(model.getCoord(path[i].src).first * breite)
                , static_cast<int> (model.getCoord(path[i].src).second * hoehe)
                , static_cast<int>(model.getCoord(path[i].dest).first * breite)
                , static_cast<int> (model.getCoord(path[i].dest).second * hoehe));

}
