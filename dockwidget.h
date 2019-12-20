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

public:
    explicit DockWidget(Graph& Graphmodel,QWidget *parent = nullptr);
    ~DockWidget();

private:
    Ui::DockWidget *ui;
    QStringListModel* model;
};

#endif // DOCKWIDGET_H
