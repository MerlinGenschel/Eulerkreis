#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>

class QMouseEvent;
class QKeyEvent;
class QUndoStack;

class paint;    //View
class Graph;    //Modell
//enum class MODE {zeichnen=1 ,verbinden,verschieben,loeschen};

class control : public QObject
{
    Q_OBJECT

    // MVC: Die Steuerung kennt sowohl das Modell als auch die Ansicht
    // Referenzen auf die beiden Objekte (keine Kopie oder eigene Objekte!)
    Graph& model;
    paint& view;

    QUndoStack *undoStack = nullptr;

    // Methoden um die Events zu handhaben, sie werden durch eventFilter und nicht automatisch aufgerufen
    // Da die Basisklase QObjekt und nicht QWidget ist, ist es auch keine Überschreibung aus der Basisklasse,
    // sie könnten auch einen anderen Namen haben
    void add(QMouseEvent* event);
    void remove(QMouseEvent* event);
    void connect(QMouseEvent* event);
    void move(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);

    // Die Steuerung ist dafür zuständig, welcher Knoten ausgewählt ist. Wird für die Interaktion benötigt
    int activeNode = std::numeric_limits<int>::max(); // Index des angeklickten/ausgewählten Knotens

    bool activeNodeValid(QMouseEvent* event) const;

    int _selectedNode;

    //Soll zwischen NUll und Eins wechseln um festzulegen an welcher Stelle im
    //zuVerbiden Array der aktuelle Index gespeichert werden soll
    size_t NullOderEins = 0;
   //bool linienDickeSkalieren = false;
public:

    //static int modus;
//*** Konstruktoren ***//
    control(Graph& model, paint& view, QUndoStack *undoStack, QObject *parent=nullptr);

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
