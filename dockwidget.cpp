#include "dockwidget.h"
#include "ui_dockwidget.h"
#include <sstream>

DockWidget::DockWidget(Graph& Graphmodel,QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::DockWidget)
{
    ui->setupUi(this);

            string test;
    for(int i = 0; i< Graphmodel.getSize();i++)
    {

        vector<int> edgesI = Graphmodel.getEdges(i);
        for(int j = 0; j< edgesI.size();j++)
        {
            std::stringstream ss;
            ss << edgesI[j];
            string out_string = ss.str();
            test.append(out_string);
            test.append(", ");
        }
        test.append("\n");
    }

    qDebug() << "test" << test.c_str();

     model = new QStringListModel(this);
    QStringList knotenListe;
    knotenListe << QString::fromStdString(test);
    model->setStringList(knotenListe);
    ui->knotenListe->setModel(model);



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
