#include "removeNodeCommand.h"

#include <QString>

#include "Graph.h"

removeNodeCommand::removeNodeCommand(Graph* model, int id)
    : model(model)
    , id(id)
{
    setText(QString("Löschen von (%1,%2)").arg(pos.x()).arg(pos.y()));
}

void removeNodeCommand::undo()
{
    if(model)
    {
        model->addNode(pos.x(), pos.y());
        //id = model->clickedOnNode(pos.x(), pos.y());
    }
}

void removeNodeCommand::redo()
{
    if(model)
    {
        model->removeNode(id);
        pos = QPointF(model->getCoord(id).first
                    , model->getCoord(id).second);
    }
}
