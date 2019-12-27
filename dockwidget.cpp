#include "dockwidget.h"
#include "ui_dockwidget.h"
#include <sstream>

DockWidget::DockWidget(Graph& Graphmodel,QWidget *parent) :
    QDockWidget(parent),Graphmodel(Graphmodel),
    ui(new Ui::DockWidget)
{
    ui->setupUi(this);

    fillKnotenListe();



    /*
    KnotenListe = new QStringListModel(this);
    QStringList knotenListe;
    knotenListe << "Knoten1" <<"Knoten2";
    KnotenListe->setStringList(knotenListe);
    ui->knotenListe->setModel(KnotenListe);
    */
}

DockWidget::~DockWidget()
{
    delete ui;
}

void DockWidget::fillKnotenListe()
{
    string test;
for(int i = 0; i< Graphmodel.getSize();i++)
{
vector<int> edgesI = Graphmodel.getEdges(i);
test.append(std::to_string(i));
test.append(": \t\t");
for(int j = 0; j< edgesI.size();j++)
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
