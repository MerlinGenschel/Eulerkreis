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

            vector<int> edges = model.getEdges(i);
            size_t numEdges = edges.size();

            vector<Edge> path = model.getPath();
            for(size_t k = 0; k< numEdges;k++)
            {

                //Grüne Kanten
                int edg = model.edgeToColor;
                if (!path.empty()
                        &&  edg !=-1 && edg < path.size()
                        &&  path.at(edg).src==i
                        &&  path.at(edg).dest==edges[k]                    )
                {
                    //qDebug()<<"Rot";
                    p.setPen(QPen(Qt::red) );
                    p.drawLine(static_cast<int>(model.getCoord(i).first * breite)
                                , static_cast<int> (model.getCoord(i).second * hoehe)
                                , static_cast<int>(model.getCoord(edges[k]).first * breite)
                                , static_cast<int> (model.getCoord(edges[k]).second * hoehe));
                }
                else if(!path.empty()
                        &&  edg !=-1 && edg < path.size()
                        &&  path.at(edg).dest==i
                        &&  path.at(edg).src==edges[k]                    )
                {
                    //qDebug()<<"Rot";
                    p.setPen(QPen(Qt::red) );
                    p.drawLine(static_cast<int>(model.getCoord(i).first * breite)
                                , static_cast<int> (model.getCoord(i).second * hoehe)
                                , static_cast<int>(model.getCoord(edges[k]).first * breite)
                                , static_cast<int> (model.getCoord(edges[k]).second * hoehe));
                }


                else
                {
                  //qDebug()<<"Schwarz";
                  p.setPen(QPen(Qt::black) );
                  p.drawLine(static_cast<int>(model.getCoord(i).first * breite)
                              , static_cast<int> (model.getCoord(i).second * hoehe)
                              , static_cast<int>(model.getCoord(edges[k]).first * breite)
                              , static_cast<int> (model.getCoord(edges[k]).second * hoehe));
                }




            }//end for

        }


    //Zeige die Nummer der Animierten Kante (falls vorhanden) an
    p.setPen(QPen(Qt::black));
    QPoint pos;
    pos.setX(0.8*breite);
    pos.setY(0.85*hoehe);
    QFont font=p.font() ;
     font.setPointSize ( 24 );
     //font.setWeight(QFont::DemiBold);
     p.setFont(font);
     QString s = QString::number(model.edgeToColor);
     if(model.edgeToColor!=-1)
        p.drawText(pos,s);
}

void paint::animationEvent( )
{

}


