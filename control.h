#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include<QPolygonF>
#include<QPen>

class QMouseEvent;

enum class Mode;

class control : public QObject
{
    Q_OBJECT

    double rand = 0.1;
    QPen   pen;
    QPolygonF knoten;

    bool linienDickeSkalieren = false;
public:
//*** Konstruktoren ***//
    control();

    enum class Mode {zeichnen, verschieben};

//*** get-Methoden ***//

    Mode getMode() {return mode;}


//*** set-Methoden ***//

    void setMode(Mode mode);

//*** Methoden ***//

    // Eventfilter um die Ereignise von der Ansicht abzufangen
    bool eventFilter(QObject* watched, QEvent* event) override;

    void zeichnen(QMouseEvent* event);
    void verschieben(QMouseEvent * event);

private:
    Mode mode = Mode::zeichnen;

};

#endif // CONTROL_H
