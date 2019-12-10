#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H
#include <QtCore>
#include <QtGui>
#include <QDockWidget>

namespace Ui {
class DockWidget;
}

class DockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit DockWidget(QWidget *parent = nullptr);
    ~DockWidget();

private:
    Ui::DockWidget *ui;
    QStringListModel* model;
};

#endif // DOCKWIDGET_H
