#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H
#include <QtCore>
#include <QtGui>
#include <QDockWidget>
#include "Graph.h"
#include <QDebug>

namespace Ui {
class DockWidget;
}

class DockWidget : public QDockWidget
{
    Q_OBJECT
private:
    Ui::DockWidget* ui;
    QStringListModel* model;
    Graph& Graphmodel;


public:
    explicit DockWidget(Graph& Graphmodel, QWidget *parent = nullptr);
    ~DockWidget();

void fillKnotenListe();

public slots:
    void updateKnotenListe()
    {
        fillKnotenListe();
    }

};

#endif // DOCKWIDGET_H
