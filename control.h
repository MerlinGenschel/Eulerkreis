#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include<QPolygonF>
#include<QPen>
#include <iostream>;

class QMouseEvent;
class QKeyEvent;


class paint;    //View
class Graph;    //Modell
//enum class MODE {zeichnen=1 ,verbinden,verschieben,loeschen};

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

    //Hier sollen 2 Indizes gespeichert werden von zu verbindenden KNoten
    int toConnect[2] = {-1,-1} ;



    //Soll zwischen NUll und Eins wechseln um festzulegen an welcher Stelle im
    //zuVerbiden Array der aktuelle Index gespeichert werden soll
    size_t NullOderEins = 0;
   //bool linienDickeSkalieren = false;
public:

    //static int modus;
//*** Konstruktoren ***//
    control(Graph& model, paint& view,QObject *parent=nullptr);

    bool eventFilter(QObject* watched, QEvent* event) override;

    /*
    static void setMode(size_t i)
    {

        if (i == 1)
        {
            std::cout << "modus auf Zeichnen" << std::endl;
            modus= 1;
        }
        else if (i ==2)
        {
            std::cout << "modus auf verbinden" << std::endl;
            modus = 2;
        }
        else if (i ==3)
        {
            modus = 2;
        }
        else if (i==4)
        {
            modus = 4;
        }


    }
    */


};

#endif // CONTROL_H
