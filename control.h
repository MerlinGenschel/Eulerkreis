#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>

class QMouseEvent;
class QKeyEvent;
class QUndoStack;

class paint;    //View
class Graph;    //Modell

enum class Mode;

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

    // Die Steuerung ist dafür zuständig, welcher Knoten ausgewählt ist. Wird für die Interaktion benötigt
    int activeNode = std::numeric_limits<int>::max(); // Index des angeklickten/ausgewählten Knotens

    // Prüfen ob aktiver Knoten gültig ist
    bool activeNodeValid(QMouseEvent* event) const;

    // index des ausgewählten Knotens
    int _selectedNode;

    //Soll zwischen NUll und Eins wechseln um festzulegen an welcher Stelle im
    //zuVerbiden Array der aktuelle Index gespeichert werden soll
    size_t NullOderEins = 0;

public:
    // für Modusauswahl
    enum class Mode {zeichnen = 1, verbinden, verschieben, loeschen};
    Mode mod = Mode::zeichnen;
    void setMode(int m);
    Mode getMode() {return mod;}

    // Konstruktor
    control(Graph& model, paint& view, QUndoStack *undoStack, QObject *parent=nullptr);

    bool eventFilter(QObject* watched, QEvent* event) override;
};

#endif // CONTROL_H
