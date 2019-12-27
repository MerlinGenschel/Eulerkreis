#include "addNodeCommand.h"

#include <QString>

#include "Graph.h"

addNodeCommand::addNodeCommand(Graph* model, QPointF pos)
    : model(model)
    , pos(pos)
{
    setText(QString("Hinzufügen von (%1,%2)").arg(pos.x()).arg(pos.y()));
}

void addNodeCommand::undo()
{
    if(model)
        model->removeNode(id);
}

void addNodeCommand::redo()
{
    if(model)
        model->addNode(pos.x(), pos.y());
}
