#include "dockwidget.h"
#include "ui_dockwidget.h"
#include <sstream>

DockWidget::DockWidget(Graph& Graphmodel,QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::DockWidget)
    , Graphmodel(Graphmodel)
{
    ui->setupUi(this);

    fillKnotenListe();
}

DockWidget::~DockWidget()
{
    delete ui;
}

void DockWidget::fillKnotenListe()
{
    string test;
    for(size_t i = 0; i < Graphmodel.getSize(); i++)
    {
        vector<int> edgesI = Graphmodel.getEdges(i);
        test.append(std::to_string(i));
        test.append(": \t\t");
        for(std::size_t j = 0; j < edgesI.size(); j++)
        {
            string out_string = std::to_string(edgesI[j]);
            test.append(out_string);
            test.append(", ");
            qDebug()<<edgesI[j];
        }
        test.append("\n");

    }
    test.append("Nodes: ");
    test.append(std::to_string(Graphmodel.getSize()));
    test.append("  Edges: ");
    test.append(std::to_string(Graphmodel.getNumEdges()));

    model = new QStringListModel(this);
    QStringList knotenListe;
    knotenListe << QString::fromStdString(test);
    model->setStringList(knotenListe);
    ui->knotenListe->setModel(model);
}
